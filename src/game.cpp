#include "game.hpp"
#include "ResourcePath.hpp"
#include "math.h"

Game::Game(const ConfigData & conf)
    : m_drawableArea(conf.drawableArea), m_slept(false),
      m_window(sf::VideoMode::getDesktopMode(), EXECUTABLE_NAME,
               sf::Style::Fullscreen, sf::ContextSettings(0, 0, 6)),
      m_camera(m_drawableArea, m_window.getSize()), m_hasFocus(false),
      m_worldView(sf::Vector2f(m_drawableArea.x / 2, m_drawableArea.y / 2),
                  m_drawableArea),
      m_naturalLight(185, 185, 185) {
    sf::View windowView;
    static const float visibleArea = 0.75f;
    const sf::Vector2f vignetteMaskScale(
        (m_drawableArea.x * (visibleArea + 0.02)) / 450,
        (m_drawableArea.y * (visibleArea + 0.02)) / 450);
    m_vignetteSprite.setScale(vignetteMaskScale);
    m_vignetteShadowSpr.setScale(vignetteMaskScale);
    windowView.setSize(m_window.getSize().x, m_window.getSize().y);
    windowView.zoom(visibleArea);
    m_camera.setWindowView(windowView);
    m_gfxContext.targetRef = &m_target;
    // TODO: refactor out global pointer! (only needed for old C++ logic)
    setgResHandlerPtr(&m_resHandler);
}

void Game::init() {
    m_target.create(m_drawableArea.x, m_drawableArea.y);
    m_lightingMap.create(m_drawableArea.x, m_drawableArea.y);
    m_vignetteSprite.setTexture(
        getgResHandlerPtr()->getTexture("textures/vignetteMask.png"));
    m_vignetteShadowSpr.setTexture(
        getgResHandlerPtr()->getTexture("textures/vignetteShadow.png"));
    m_vignetteShadowSpr.setColor(sf::Color(255, 255, 255, 100));
    m_hudView.setSize(m_drawableArea.x, m_drawableArea.y);
    m_hudView.setCenter(m_drawableArea.x / 2, m_drawableArea.y / 2);
    m_vignetteSprite.setColor(sf::Color::White);
}

void Game::eventLoop() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            m_window.close();
            throw ShutdownSignal();
            break;

        case sf::Event::GainedFocus:
            m_sounds.unpause(SoundController::Sound | SoundController::Music);
            m_hasFocus = true;
            break;

        case sf::Event::LostFocus:
            m_sounds.pause(SoundController::Sound | SoundController::Music);
            m_hasFocus = false;
            break;

        // Note: Deliberate fallthrough
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
            m_input.recordEvent(event);
            break;

        default:
            std::cout << "Unhandled event: " << event.type << std::endl;
            break;
        }
    }
}

void Game::updateGraphics() {
    m_window.clear(sf::Color(128, 128, 128));
    if (!m_hasFocus) {
        this->setSleep(std::chrono::microseconds(200000));
        return;
    }
    m_target.clear(sf::Color::Transparent);
    {
        std::lock_guard<std::mutex> entitiesLock(m_entityMutex);
        m_lightingMap.setView(m_camera.getOverworldView());
        m_gfxContext.glowSprs.clear();
        m_gfxContext.shadows.clear();
        m_gfxContext.faces.clear();
        m_target.setView(m_camera.getOverworldView());
        for (auto & kvp : m_entityTable) {
            for (auto & entity : kvp.second) {
                auto fg = entity->getSheet();
                if (fg) {
                    fg->setFrame(entity->getKeyframe());
                    fg->getSprite().setPosition(entity->getPosition());
                    m_gfxContext.faces.emplace_back(
                        fg->getSprite(), entity->getZOrder(),
                        // TODO: add shading options to
                        //       lua API
                        Rendertype::shadeDefault, 0.f);
                }
            }
        }
        for (auto & light : m_lights) {
            auto sheet = light.getSheet();
            sheet->getSprite().setPosition(light.getPosition());
            sheet->getSprite().setOrigin(light.getOrigin());
            m_gfxContext.glowSprs.push_back(sheet->getSprite());
        }
        m_sounds.update();
    }
    const auto drawLayer = [this](auto it) {
        Layer & l = it->second;
        switch (l.source) {
        case Layer::Source::sprite: {
            m_target.setView(m_camera.getOverworldView());
            sf::Sprite & spr = l.data.spriteLayer.sheet->getSprite();
            if (l.absorptivity > 0.f) {
                spr.setPosition(0.f, 0.f);
                if (l.canvas == nullptr) {
                    l.canvas = std::make_unique<sf::RenderTexture>();
                    sf::Vector2u textureSize = spr.getTexture()->getSize();
                    l.canvas->create(textureSize.x, textureSize.y);
                }
                l.canvas->clear(sf::Color::Transparent);
                l.canvas->draw(spr);
                for (auto & lightSpr : m_gfxContext.glowSprs) {
                    const sf::Vector2f lightAbsPos = lightSpr.getPosition();
                    const sf::Vector2f lightRelativePos{
                        lightAbsPos.x - l.data.spriteLayer.x,
                        lightAbsPos.y - l.data.spriteLayer.y};
                    const uint8_t brightness = l.absorptivity * 255;
                    lightSpr.setColor({brightness, brightness, brightness});
                    lightSpr.setPosition(lightRelativePos);
                    l.canvas->draw(
                        lightSpr,
                        sf::BlendMode(sf::BlendMode(
                            sf::BlendMode::SrcAlpha, sf::BlendMode::One,
                            sf::BlendMode::Add, sf::BlendMode::DstAlpha,
                            sf::BlendMode::Zero, sf::BlendMode::Add)));
                    lightSpr.setPosition(lightAbsPos);
                    lightSpr.setColor(sf::Color::White);
                }
                l.canvas->display();
                sf::Sprite canvasSpr(l.canvas->getTexture());
                canvasSpr.setPosition(l.data.spriteLayer.x,
                                      l.data.spriteLayer.y);
                canvasSpr.setColor(m_naturalLight);
                m_target.draw(canvasSpr, l.blending);
            } else {
                if (l.canvas)
                    l.canvas = nullptr;
                spr.setPosition(l.data.spriteLayer.x, l.data.spriteLayer.y);
                m_target.draw(spr, l.blending);
            }
        } break;

        case Layer::Source::color: {
            throw std::runtime_error("Error: color layers unimplemented");
        } break;
        }
    };
    {
        LockedRef<LayerMap> bkgLayers = m_background.getBkgLayers();
        for (auto it = bkgLayers.resource.get().rbegin();
             it != bkgLayers.resource.get().rend(); ++it) {
            drawLayer(it);
        }
    }
    m_target.setView(m_worldView);
    m_lightingMap.clear(sf::Color::Transparent);
    static const size_t zOrderIdx = 1;
    std::sort(m_gfxContext.faces.begin(), m_gfxContext.faces.end(),
              [](const drawableMetadata & arg1, const drawableMetadata & arg2) {
                  return (std::get<zOrderIdx>(arg1) <
                          std::get<zOrderIdx>(arg2));
              });
    static const size_t sprIdx = 0;
    static const size_t shaderIdx = 3;
    sf::Shader & colorShader =
        getgResHandlerPtr()->getShader("shaders/color.frag");
    for (auto & element : m_gfxContext.faces) {
        switch (std::get<2>(element)) {
        case Rendertype::shadeDefault:
            std::get<0>(element).setColor(
                sf::Color(m_naturalLight.r, m_naturalLight.g, m_naturalLight.b,
                          std::get<sprIdx>(element).getColor().a));
            m_lightingMap.draw(std::get<sprIdx>(element));
            break;

        default:
            throw std::runtime_error("Error: bad rendertype");
            break;
        }
    }
    static const sf::Color entityLightBlending(185, 185, 185);
    for (auto & element : m_gfxContext.glowSprs) {
        element.setColor(entityLightBlending);
        m_lightingMap.draw(element,
                           sf::BlendMode(sf::BlendMode(
                               sf::BlendMode::SrcAlpha, sf::BlendMode::One,
                               sf::BlendMode::Add, sf::BlendMode::DstAlpha,
                               sf::BlendMode::Zero, sf::BlendMode::Add)));
    }
    m_lightingMap.display();
    sf::Sprite lightingMapSpr(m_lightingMap.getTexture());
    m_target.draw(lightingMapSpr);
    m_target.setView(m_camera.getOverworldView());
    {
        LockedRef<LayerMap> fgLayers = m_background.getFgLayers();
        for (auto it = fgLayers.resource.get().rbegin();
             it != fgLayers.resource.get().rend(); ++it) {
            drawLayer(it);
        }
    }
    m_target.setView(m_worldView);
    sf::Vector2f fgMaskPos(
        m_drawableArea.x * 0.115f + m_camera.getOffsetFromTarget().x * 0.75f,
        m_drawableArea.y * 0.115f + m_camera.getOffsetFromTarget().y * 0.75f);
    m_vignetteSprite.setPosition(fgMaskPos);
    m_vignetteShadowSpr.setPosition(fgMaskPos);
    m_target.draw(m_vignetteSprite, sf::BlendMultiply);
    m_target.draw(m_vignetteShadowSpr);
    m_target.display();
    const sf::Vector2u windowSize = m_window.getSize();
    const sf::Vector2f upscaleVec(windowSize.x / m_drawableArea.x,
                                  windowSize.y / m_drawableArea.y);
    sf::Sprite targetSprite(m_target.getTexture());
    m_window.setView(m_camera.getWindowView());
    targetSprite.setScale(upscaleVec);
    m_window.draw(targetSprite);
    m_window.setView(m_worldView);
    m_window.display();
}

// clang-format off
const char * heartBeatFn =
    "__heartBeat__ = function(dt)                       \
         for k, _ in pairs(classes) do                  \
             local updateFn = classes[k].onUpdate       \
             if updateFn then                           \
                 local handles = entity.listAll(k)      \
                 for i = 1, #handles do                 \
                     updateFn(handles[i], dt)           \
                 end                                    \
             else                                       \
                 entity.__sweep__(k)                    \
             end                                        \
         end                                            \
     end";
// clang-format on

void Game::updateLogic(LuaProvider & luaProv) {
    if (!m_hasFocus) {
        this->setSleep(std::chrono::microseconds(200));
        return;
    }
    std::lock_guard<std::mutex> entitiesLock(m_entityMutex);
    luaProv.applyHook([this](lua_State * state) {
        lua_getglobal(state, "__heartBeat__");
        if (lua_isnil(state, -1)) {
            throw std::runtime_error("Error: missing heartBeat function");
        }
        lua_pushinteger(state, m_elapsedTime.asMicroseconds());
        if (lua_pcall(state, 1, 0, 0)) {
            throw std::runtime_error(lua_tostring(state, -1));
        }
    });
    std::vector<sf::Vector2f> cameraTargets;
    m_camera.update(m_elapsedTime, cameraTargets);
}

bool Game::hasSlept() const { return m_slept; }

void Game::clearSleptFlag() { m_slept = false; }

void Game::setSleep(const std::chrono::microseconds & time) {
    m_slept = true;
    std::this_thread::sleep_for(time);
}

Camera & Game::getCamera() { return m_camera; }

InputController & Game::getInputController() { return m_input; }

SoundController & Game::getSounds() { return m_sounds; }

BackgroundController & Game::getBackground() { return m_background; }

sf::RenderWindow & Game::getWindow() { return m_window; }

ResHandler & Game::getResHandler() { return m_resHandler; }

const sf::Time & Game::getElapsedTime() { return m_elapsedTime; }

void Game::setElapsedTime(const sf::Time & elapsedTime) {
    m_elapsedTime = elapsedTime;
}

static Game * pGame;

void setgGamePtr(Game * pGame) { ::pGame = pGame; }

Game * getgGamePtr() { return ::pGame; }

EntityTable & Game::getEntityTable() { return m_entityTable; }

std::vector<Light> & Game::getLights() { return m_lights; }

void Game::setNaturalLight(const sf::Color & naturalLight) {
    m_naturalLight = naturalLight;
}

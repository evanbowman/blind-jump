#include "Engine.hpp"
#include "ResourcePath.hpp"
#include "math.h"

Engine::Engine(const ConfigData & conf)
    : m_drawableArea(conf.drawableArea), m_slept(false),
      m_window(sf::VideoMode::getDesktopMode(), EXECUTABLE_NAME,
               sf::Style::Fullscreen, sf::ContextSettings(0, 0, 6)),
      m_camera(m_drawableArea, m_window.getSize()), m_hasFocus(false),
      m_worldView(sf::Vector2f(m_drawableArea.x / 2, m_drawableArea.y / 2),
                  m_drawableArea),
      m_naturalLight(0, 0, 0), m_zoomFactor(conf.fractionVisible) {
    sf::View windowView;
    windowView.setSize(m_window.getSize().x, m_window.getSize().y);
    windowView.zoom(m_zoomFactor);
    m_camera.setWindowView(windowView);
    m_gfxContext.targetRef = &m_target;
}

void Engine::init() {
    m_target.create(m_drawableArea.x, m_drawableArea.y);
    m_overlayRect.setSize(m_drawableArea);
    m_lightingMap.create(m_drawableArea.x, m_drawableArea.y);
    m_hudView.setSize(m_drawableArea.x, m_drawableArea.y);
    m_hudView.setCenter(m_drawableArea.x / 2, m_drawableArea.y / 2);
}

void Engine::eventLoop() {
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

void Engine::updateGraphics() {
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
    // The layer rendering code is a bit messy, mostly because layers have
    // a lot of properties that don't seamlessly interact.
    const auto drawLayer = [this](auto it) {
        Layer & l = it->second;
        m_target.setView(m_camera.getOverworldView());
        sf::Sprite & spr = l.sheet->getSprite();
        if (l.lightingFactor > 0.f) {
            spr.setPosition(0.f, 0.f);
            if (l.canvas == nullptr) {
                l.canvas = std::make_unique<sf::RenderTexture>();
                sf::Vector2u textureSize = spr.getTexture()->getSize();
                l.canvas->create(textureSize.x, textureSize.y);
            }
            l.canvas->clear(sf::Color::Transparent);
            spr.setColor(m_naturalLight);
            l.canvas->draw(spr);
            spr.setColor(sf::Color::White);
            for (auto & lightSpr : m_gfxContext.glowSprs) {
                const sf::Vector2f lightAbsPos = lightSpr.getPosition();
                const sf::Vector2f lightRelativePos{lightAbsPos.x - l.x,
                                                    lightAbsPos.y - l.y};
                const uint8_t brightness = l.lightingFactor * 255;
                lightSpr.setColor({brightness, brightness, brightness});
                lightSpr.setPosition(lightRelativePos);
                l.canvas->draw(lightSpr,
                               sf::BlendMode(sf::BlendMode(
                                   sf::BlendMode::SrcAlpha, sf::BlendMode::One,
                                   sf::BlendMode::Add, sf::BlendMode::DstAlpha,
                                   sf::BlendMode::Zero, sf::BlendMode::Add)));
                lightSpr.setPosition(lightAbsPos);
                lightSpr.setColor(sf::Color::White);
            }
            l.canvas->display();
            sf::Sprite canvasSpr(l.canvas->getTexture());
	    canvasSpr.setScale(l.xScale, l.yScale);
            canvasSpr.setPosition(l.x, l.y);
            m_target.draw(canvasSpr, l.blending);
        } else {
            if (l.canvas) {
                l.canvas = nullptr;
            }
            spr.setColor(sf::Color::White);
            float offX = 0;
            float offY = 0;
            if (l.fixed) {
                m_target.setView(m_worldView);
                offX = m_drawableArea.x * 0.115f +
                       m_camera.getOffsetFromTarget().x * m_zoomFactor;
                offY = m_drawableArea.y * 0.115f +
                       m_camera.getOffsetFromTarget().y * m_zoomFactor;
            }
	    spr.setScale(l.xScale, l.yScale);
            spr.setPosition(offX + l.x, offY + l.y);
            m_target.draw(spr, l.blending);
            if (l.fixed) {
                m_target.setView(m_camera.getOverworldView());
            }
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
    sf::Shader & colorShader = m_resHandler.getShader("shaders/color.frag");
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

void Engine::updateLogic(LuaProvider & luaProv) {
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

bool Engine::hasSlept() const { return m_slept; }

void Engine::clearSleptFlag() { m_slept = false; }

void Engine::setSleep(const std::chrono::microseconds & time) {
    m_slept = true;
    std::this_thread::sleep_for(time);
}

Camera & Engine::getCamera() { return m_camera; }

InputController & Engine::getInputController() { return m_input; }

SoundController & Engine::getSounds() { return m_sounds; }

BackgroundController & Engine::getBackground() { return m_background; }

sf::RenderWindow & Engine::getWindow() { return m_window; }

ResHandler & Engine::getResHandler() { return m_resHandler; }

const sf::Time & Engine::getElapsedTime() { return m_elapsedTime; }

void Engine::setElapsedTime(const sf::Time & elapsedTime) {
    m_elapsedTime = elapsedTime;
}

static Engine * pEngine;

void setgEnginePtr(Engine * pEngine) { ::pEngine = pEngine; }

Engine * getgEnginePtr() { return ::pEngine; }

EntityTable & Engine::getEntityTable() { return m_entityTable; }

std::vector<Light> & Engine::getLights() { return m_lights; }

void Engine::setNaturalLight(const sf::Color & naturalLight) {
    m_naturalLight = naturalLight;
}

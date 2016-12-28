#include "game.hpp"
#include "ResourcePath.hpp"
#include "math.h"

Game::Game(const ConfigData & conf)
    : m_viewPort(conf.drawableArea), m_slept(false),
      m_window(sf::VideoMode::getDesktopMode(), EXECUTABLE_NAME,
               sf::Style::Fullscreen, sf::ContextSettings(0, 0, 6)),
      m_camera(m_viewPort, m_window.getSize()), m_hasFocus(false),
      m_worldView(sf::Vector2f(m_viewPort.x / 2, m_viewPort.y / 2), m_viewPort),
      m_timer(0) {
    sf::View windowView;
    static const float visibleArea = 0.75f;
    const sf::Vector2f vignetteMaskScale(
        (m_viewPort.x * (visibleArea + 0.02)) / 450,
        (m_viewPort.y * (visibleArea + 0.02)) / 450);
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
    m_target.create(m_viewPort.x, m_viewPort.y);
    m_secondPass.create(m_viewPort.x, m_viewPort.y);
    m_secondPass.setSmooth(true);
    m_thirdPass.create(m_viewPort.x, m_viewPort.y);
    m_thirdPass.setSmooth(true);
    m_stash.create(m_viewPort.x, m_viewPort.y);
    m_stash.setSmooth(true);
    m_lightingMap.create(m_viewPort.x, m_viewPort.y);
    m_vignetteSprite.setTexture(
        getgResHandlerPtr()->getTexture("textures/vignetteMask.png"));
    m_vignetteShadowSpr.setTexture(
        getgResHandlerPtr()->getTexture("textures/vignetteShadow.png"));
    m_vignetteShadowSpr.setColor(sf::Color(255, 255, 255, 100));
    m_hudView.setSize(m_viewPort.x, m_viewPort.y);
    m_hudView.setCenter(m_viewPort.x / 2, m_viewPort.y / 2);
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
    m_window.clear();
    if (!m_hasFocus) {
        this->setSleep(std::chrono::microseconds(200000));
        return;
    }
    m_target.clear(sf::Color::Transparent);
    {
        std::lock_guard<std::mutex> overworldLock(m_overworldMutex);
        m_lightingMap.setView(m_camera.getOverworldView());
        m_gfxContext.glowSprs2.clear();
        m_gfxContext.glowSprs1.clear();
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
            m_gfxContext.glowSprs1.push_back(sheet->getSprite());
            m_gfxContext.glowSprs2.push_back(sheet->getSprite());
        }
        m_sounds.update();
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
            std::get<0>(element).setColor(sf::Color(
                190, 190, 210, std::get<sprIdx>(element).getColor().a));
            m_lightingMap.draw(std::get<sprIdx>(element));
            break;

        case Rendertype::shadeNone:
            m_lightingMap.draw(std::get<sprIdx>(element));
            break;

        case Rendertype::shadeWhite: {
            DEF_GLSL_COLOR(colors::White, White);
            colorShader.setUniform("amount", std::get<shaderIdx>(element));
            colorShader.setUniform("targetColor", White);
            m_lightingMap.draw(std::get<sprIdx>(element), &colorShader);
        } break;

        case Rendertype::shadeGldnGt: {
            DEF_GLSL_COLOR(colors::GldnGt, GldnGt);
            colorShader.setUniform("amount", std::get<shaderIdx>(element));
            colorShader.setUniform("targetColor", GldnGt);
            m_lightingMap.draw(std::get<sprIdx>(element), &colorShader);
        } break;

        case Rendertype::shadeRuby: {
            DEF_GLSL_COLOR(colors::Ruby, Ruby);
            colorShader.setUniform("amount", std::get<shaderIdx>(element));
            colorShader.setUniform("targetColor", Ruby);
            m_lightingMap.draw(std::get<sprIdx>(element), &colorShader);
        } break;

        case Rendertype::shadeElectric: {
            DEF_GLSL_COLOR(colors::Electric, Electric);
            colorShader.setUniform("amount", std::get<shaderIdx>(element));
            colorShader.setUniform("targetColor", Electric);
            m_lightingMap.draw(std::get<sprIdx>(element), &colorShader);
        } break;
        }
    }
    static const sf::Color entityLightBlending(185, 185, 185);
    for (auto & element : m_gfxContext.glowSprs2) {
        element.setColor(entityLightBlending);
        m_lightingMap.draw(element,
                           sf::BlendMode(sf::BlendMode(
                               sf::BlendMode::SrcAlpha, sf::BlendMode::One,
                               sf::BlendMode::Add, sf::BlendMode::DstAlpha,
                               sf::BlendMode::Zero, sf::BlendMode::Add)));
    }
    m_lightingMap.display();
    m_target.draw(sf::Sprite(m_lightingMap.getTexture()));
    m_target.setView(m_camera.getOverworldView());
    m_target.setView(m_worldView);
    sf::Vector2f fgMaskPos(
        m_viewPort.x * 0.115f + m_camera.getOffsetFromTarget().x * 0.75f,
        m_viewPort.y * 0.115f + m_camera.getOffsetFromTarget().y * 0.75f);
    m_vignetteSprite.setPosition(fgMaskPos);
    m_vignetteShadowSpr.setPosition(fgMaskPos);
    m_target.draw(m_vignetteSprite, sf::BlendMultiply);
    m_target.draw(m_vignetteShadowSpr);
    m_target.display();
    const sf::Vector2u windowSize = m_window.getSize();
    const sf::Vector2f upscaleVec(windowSize.x / m_viewPort.x,
                                  windowSize.y / m_viewPort.y);
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
    std::lock_guard<std::mutex> overworldLock(m_overworldMutex);
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

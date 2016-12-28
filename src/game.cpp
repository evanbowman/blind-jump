#include "game.hpp"
#include "ResourcePath.hpp"
#include "math.h"

Game::Game(const ConfigData & conf)
    : viewPort(conf.drawableArea), slept(false),
      window(sf::VideoMode::getDesktopMode(), EXECUTABLE_NAME,
             sf::Style::Fullscreen, sf::ContextSettings(0, 0, 6)),
      camera(viewPort, window.getSize()),
      hasFocus(false), stashed(false), preload(false),
      worldView(sf::Vector2f(viewPort.x / 2, viewPort.y / 2), viewPort),
      timer(0) {
    sf::View windowView;
    static const float visibleArea = 0.75f;
    const sf::Vector2f vignetteMaskScale(
        (viewPort.x * (visibleArea + 0.02)) / 450,
        (viewPort.y * (visibleArea + 0.02)) / 450);
    vignetteSprite.setScale(vignetteMaskScale);
    vignetteShadowSpr.setScale(vignetteMaskScale);
    windowView.setSize(window.getSize().x, window.getSize().y);
    windowView.zoom(visibleArea);
    camera.setWindowView(windowView);
    gfxContext.targetRef = &target;
    window.setMouseCursorVisible(conf.showMouse);
    // TODO: refactor out global pointer! (only needed for old C++ logic)
    setgResHandlerPtr(&resHandler);
}

void Game::init() {
    target.create(viewPort.x, viewPort.y);
    secondPass.create(viewPort.x, viewPort.y);
    secondPass.setSmooth(true);
    thirdPass.create(viewPort.x, viewPort.y);
    thirdPass.setSmooth(true);
    stash.create(viewPort.x, viewPort.y);
    stash.setSmooth(true);
    lightingMap.create(viewPort.x, viewPort.y);
    vignetteSprite.setTexture(
        getgResHandlerPtr()->getTexture("textures/vignetteMask.png"));
    vignetteShadowSpr.setTexture(
        getgResHandlerPtr()->getTexture("textures/vignetteShadow.png"));
    vignetteShadowSpr.setColor(sf::Color(255, 255, 255, 100));
    hudView.setSize(viewPort.x, viewPort.y);
    hudView.setCenter(viewPort.x / 2, viewPort.y / 2);
    vignetteSprite.setColor(sf::Color::White);
}

void Game::eventLoop() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            throw ShutdownSignal();
            break;

        case sf::Event::GainedFocus:
            sounds.unpause(SoundController::Sound | SoundController::Music);
            this->hasFocus = true;
            break;

        case sf::Event::LostFocus:
            sounds.pause(SoundController::Sound | SoundController::Music);
            this->hasFocus = false;
            break;

	    // Note: Deliberate fallthrough
	case sf::Event::KeyPressed:
	case sf::Event::KeyReleased:
	    input.recordEvent(event);
	    break;

        default:
	    std::cout << "Unhandled event: " << event.type << std::endl;
            break;
        }
    }
}

void Game::updateGraphics() {
    window.clear();
    if (!hasFocus) {
        this->setSleep(std::chrono::microseconds(200000));
        return;
    }
    target.clear(sf::Color::Transparent);
    if (!stashed || preload) {
        {
            std::lock_guard<std::mutex> overworldLock(overworldMutex);
            lightingMap.setView(camera.getOverworldView());
            gfxContext.glowSprs2.clear();
            gfxContext.glowSprs1.clear();
            gfxContext.shadows.clear();
            gfxContext.faces.clear();
            target.setView(camera.getOverworldView());
            for (auto & kvp : entityTable) {
                for (auto & entity : kvp.second) {
                    auto fg = entity->getSheet();
                    if (fg) {
                        fg->setFrame(entity->getKeyframe());
                        fg->getSprite().setPosition(entity->getPosition());
                        gfxContext.faces.emplace_back(
                            fg->getSprite(), entity->getZOrder(),
                            // TODO: add shading options to
                            //       lua API
                            Rendertype::shadeDefault, 0.f);
                    }
                }
            }
	    for (auto & light : lights) {
	        auto sheet = light.getSheet();
		sheet->getSprite().setPosition(light.getPosition());
		sheet->getSprite().setOrigin(light.getOrigin());
		gfxContext.glowSprs1.push_back(sheet->getSprite());
		gfxContext.glowSprs2.push_back(sheet->getSprite());
	    }
            sounds.update();
        }
        target.setView(worldView);
        lightingMap.clear(sf::Color::Transparent);
        static const size_t zOrderIdx = 1;
        std::sort(
            gfxContext.faces.begin(), gfxContext.faces.end(),
            [](const drawableMetadata & arg1, const drawableMetadata & arg2) {
                return (std::get<zOrderIdx>(arg1) < std::get<zOrderIdx>(arg2));
            });
        static const size_t sprIdx = 0;
        static const size_t shaderIdx = 3;
        sf::Shader & colorShader =
            getgResHandlerPtr()->getShader("shaders/color.frag");
        for (auto & element : gfxContext.faces) {
            switch (std::get<2>(element)) {
            case Rendertype::shadeDefault:
                std::get<0>(element).setColor(sf::Color(
                    190, 190, 210, std::get<sprIdx>(element).getColor().a));
                lightingMap.draw(std::get<sprIdx>(element));
                break;

            case Rendertype::shadeNone:
                lightingMap.draw(std::get<sprIdx>(element));
                break;

            case Rendertype::shadeWhite: {
                DEF_GLSL_COLOR(colors::White, White);
                colorShader.setUniform("amount", std::get<shaderIdx>(element));
                colorShader.setUniform("targetColor", White);
                lightingMap.draw(std::get<sprIdx>(element), &colorShader);
            } break;

            case Rendertype::shadeGldnGt: {
                DEF_GLSL_COLOR(colors::GldnGt, GldnGt);
                colorShader.setUniform("amount", std::get<shaderIdx>(element));
                colorShader.setUniform("targetColor", GldnGt);
                lightingMap.draw(std::get<sprIdx>(element), &colorShader);
            } break;

            case Rendertype::shadeRuby: {
                DEF_GLSL_COLOR(colors::Ruby, Ruby);
                colorShader.setUniform("amount", std::get<shaderIdx>(element));
                colorShader.setUniform("targetColor", Ruby);
                lightingMap.draw(std::get<sprIdx>(element), &colorShader);
            } break;

            case Rendertype::shadeElectric: {
                DEF_GLSL_COLOR(colors::Electric, Electric);
                colorShader.setUniform("amount", std::get<shaderIdx>(element));
                colorShader.setUniform("targetColor", Electric);
                lightingMap.draw(std::get<sprIdx>(element), &colorShader);
            } break;
            }
        }
	static const sf::Color entityLightBlending(185, 185, 185);
        for (auto & element : gfxContext.glowSprs2) {
	    element.setColor(entityLightBlending);
            lightingMap.draw(element,
                             sf::BlendMode(sf::BlendMode(
                                 sf::BlendMode::SrcAlpha, sf::BlendMode::One,
                                 sf::BlendMode::Add, sf::BlendMode::DstAlpha,
                                 sf::BlendMode::Zero, sf::BlendMode::Add)));
        }
        lightingMap.display();
        target.draw(sf::Sprite(lightingMap.getTexture()));
        target.setView(camera.getOverworldView());
        target.setView(worldView);
        sf::Vector2f fgMaskPos(
            viewPort.x * 0.115f + camera.getOffsetFromTarget().x * 0.75f,
            viewPort.y * 0.115f + camera.getOffsetFromTarget().y * 0.75f);
        vignetteSprite.setPosition(fgMaskPos);
        vignetteShadowSpr.setPosition(fgMaskPos);
        target.draw(vignetteSprite, sf::BlendMultiply);
        target.draw(vignetteShadowSpr);
        target.display();
    }
    const sf::Vector2u windowSize = window.getSize();
    const sf::Vector2f upscaleVec(windowSize.x / viewPort.x,
                                  windowSize.y / viewPort.y);
    sf::Sprite targetSprite(target.getTexture());
    window.setView(camera.getWindowView());
    targetSprite.setScale(upscaleVec);
    window.draw(targetSprite);
    window.setView(worldView);
    window.display();
}

// clang-format off
const char * heartBeatFn =
    "heartBeat = function()                             \
         for k, v in pairs(classes) do                  \
             local updateFn = classes[k].onUpdate       \
             if updateFn then                           \
                 local handles = entity.listAll(k)      \
                 for i = 1, #handles do                 \
                     updateFn(handles[i])               \
                 end                                    \
             end                                        \
         end                                            \
     end";
// clang-format on

void Game::updateLogic(LuaProvider & luaProv) {
    if (!hasFocus) {
        this->setSleep(std::chrono::microseconds(200));
        return;
    }
    std::lock_guard<std::mutex> overworldLock(overworldMutex);
    luaProv.applyHook([this](lua_State * state) {
	lua_getglobal(state, "heartBeat");
	if (lua_isnil(state, -1)) {
	    throw std::runtime_error("Error: missing heartBeat function");
	}
	if (lua_pcall(state, 0, 0, 0)) {
	    throw std::runtime_error(lua_tostring(state, -1));
	}
    });
    std::vector<sf::Vector2f> cameraTargets;
    camera.update(elapsedTime, cameraTargets);
}

bool Game::hasSlept() const { return slept; }

void Game::clearSleptFlag() { slept = false; }

void Game::setSleep(const std::chrono::microseconds & time) {
    slept = true;
    std::this_thread::sleep_for(time);
}

Camera & Game::getCamera() { return camera; }

InputController & Game::getInputController() { return input; }

SoundController & Game::getSounds() { return sounds; }

BackgroundController & Game::getBackground() { return background; }

sf::RenderWindow & Game::getWindow() { return window; }

ResHandler & Game::getResHandler() { return resHandler; }

const sf::Time & Game::getElapsedTime() { return elapsedTime; }

void Game::setElapsedTime(const sf::Time & elapsedTime) {
    this->elapsedTime = elapsedTime;
}

static Game * pGame;

void setgGamePtr(Game * pGame) { ::pGame = pGame; }

Game * getgGamePtr() { return ::pGame; }

EntityTable & Game::getEntityTable() { return entityTable; }

std::vector<Light> & Game::getLights() { return lights; }

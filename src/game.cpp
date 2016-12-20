//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "game.hpp"
#include "ResourcePath.hpp"
#include "easingTemplates.hpp"
#include "enemyPlacementFn.hpp"
#include "initMapVectors.hpp"
#include "lightingMap.hpp"
#include "mappingFunctions.hpp"
#include "math.h"
#include "pillarPlacement.h"

Game::Game(const ConfigData & conf)
    : viewPort(conf.drawableArea),
      transitionState(TransitionState::TransitionIn),
      player(viewPort.x / 2, viewPort.y / 2),
      window(sf::VideoMode::getDesktopMode(), EXECUTABLE_NAME,
             sf::Style::Fullscreen, sf::ContextSettings(0, 0, 6)),
      camera(&player, viewPort, window.getSize()),
      uiFrontend(
          sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)),
          viewPort.x / 2, viewPort.y / 2),
      level(0), stashed(false), preload(false),
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
    window.setFramerateLimit(conf.framerateLimit);
    window.setVerticalSyncEnabled(conf.enableVsync);
    this->init();
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
        getgResHandlerPtr()->getTexture(ResHandler::Texture::vignette));
    vignetteShadowSpr.setTexture(
        getgResHandlerPtr()->getTexture(ResHandler::Texture::vignetteShadow));
    beamGlowSpr.setTexture(getgResHandlerPtr()->getTexture(
        ResHandler::Texture::teleporterBeamGlow));
    vignetteShadowSpr.setColor(sf::Color(255, 255, 255, 100));
    hudView.setSize(viewPort.x, viewPort.y);
    hudView.setCenter(viewPort.x / 2, viewPort.y / 2);
    bkg.giveWindowSize(viewPort.x, viewPort.y);
    tiles.setPosition((viewPort.x / 2) - 16, (viewPort.y / 2));
    tiles.setWindowSize(viewPort.x, viewPort.y);
    // en.setWindowSize(viewPort.x, viewPort.y);
    beamGlowSpr.setColor(sf::Color(0, 0, 0, 255));
    transitionShape.setSize(sf::Vector2f(viewPort.x, viewPort.y));
    transitionShape.setFillColor(sf::Color(0, 0, 0, 0));
    vignetteSprite.setColor(sf::Color::White);
    level = -1;
    this->nextLevel();
}

extern bool gameHasFocus;

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
            ::gameHasFocus = true;
            break;

        case sf::Event::LostFocus:
            sounds.pause(SoundController::Sound | SoundController::Music);
            ::gameHasFocus = false;
            break;

        default:
            input.recordEvent(event);
            break;
        }
    }
}

void Game::updateGraphics() {
    window.clear();
    if (!::gameHasFocus) {
        util::sleep(milliseconds(200));
        return;
    }
    target.clear(sf::Color::Transparent);
    if (!stashed || preload) {
        {
            std::lock_guard<std::mutex> overworldLock(overworldMutex);
            lightingMap.setView(camera.getOverworldView());
            bkg.drawBackground(target, worldView, camera);
            tiles.draw(target, &gfxContext.glowSprs1, level, worldView,
                       camera.getOverworldView());
            gfxContext.glowSprs2.clear();
            gfxContext.glowSprs1.clear();
            gfxContext.shadows.clear();
            gfxContext.faces.clear();
            target.setView(camera.getOverworldView());
            auto drawPolicy = [this](auto & vec) {
                for (auto it = vec.begin(); it != vec.end(); ++it) {
                    it->get()->draw(gfxContext, camera.getOverworldView());
                }
            };
            detailGroup.apply(drawPolicy);
            if (player.visible) {
                player.draw(gfxContext.faces, gfxContext.shadows);
            }
            effectGroup.apply(drawPolicy);
            // en.draw(gfxContext.faces, gfxContext.shadows, camera);
            sounds.update();
        }
        if (!gfxContext.shadows.empty()) {
            for (const auto & element : gfxContext.shadows) {
                target.draw(std::get<0>(element));
            }
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
            getgResHandlerPtr()->getShader(ResHandler::Shader::color);
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
        static const sf::Color blendAmount(185, 185, 185);
        sf::Sprite tempSprite;
        for (auto & element : gfxContext.glowSprs2) {
            element.setColor(blendAmount);
            lightingMap.draw(element,
                             sf::BlendMode(sf::BlendMode(
                                 sf::BlendMode::SrcAlpha, sf::BlendMode::One,
                                 sf::BlendMode::Add, sf::BlendMode::DstAlpha,
                                 sf::BlendMode::Zero, sf::BlendMode::Add)));
        }
        lightingMap.display();
        target.draw(sf::Sprite(lightingMap.getTexture()));
        target.setView(camera.getOverworldView());
        bkg.drawForeground(target);
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
    if (UI.blurEnabled() && UI.desaturateEnabled()) {
        if (stashed) {
            sf::Sprite targetSprite(stash.getTexture());
            window.setView(camera.getWindowView());
            targetSprite.setScale(upscaleVec);
            window.draw(targetSprite);
        } else {
            sf::Shader & blurShader =
                getgResHandlerPtr()->getShader(ResHandler::Shader::blur);
            sf::Shader & desaturateShader =
                getgResHandlerPtr()->getShader(ResHandler::Shader::desaturate);
            secondPass.clear(sf::Color::Transparent);
            thirdPass.clear(sf::Color::Transparent);
            const sf::Vector2u textureSize = target.getSize();
            float blurAmount = UI.getBlurAmount();
            const sf::Glsl::Vec2 vBlur =
                sf::Glsl::Vec2(0.f, blurAmount / textureSize.y);
            blurShader.setUniform("blur_radius", vBlur);
            secondPass.draw(sf::Sprite(target.getTexture()), &blurShader);
            secondPass.display();
            const sf::Glsl::Vec2 hBlur =
                sf::Glsl::Vec2(blurAmount / textureSize.x, 0.f);
            blurShader.setUniform("blur_radius", hBlur);
            thirdPass.draw(sf::Sprite(secondPass.getTexture()), &blurShader);
            thirdPass.display();
            desaturateShader.setUniform("amount", UI.getDesaturateAmount());
            sf::Sprite targetSprite(thirdPass.getTexture());
            window.setView(camera.getWindowView());
            targetSprite.setScale(upscaleVec);
            window.draw(targetSprite, &desaturateShader);
            if (!stashed && (UI.getState() == ui::Backend::State::statsScreen ||
                             UI.getState() == ui::Backend::State::menuScreen) &&
                !camera.moving()) {
                stash.clear(sf::Color::Black);
                stash.draw(sf::Sprite(thirdPass.getTexture()),
                           &desaturateShader);
                stash.display();
                stashed = true;
            }
        }
    } else if (UI.blurEnabled() && !UI.desaturateEnabled()) {
        if (stashed) {
            if (input.pausePressed()) {
                preload = true;
            }
            sf::Sprite targetSprite(stash.getTexture());
            window.setView(camera.getWindowView());
            targetSprite.setScale(upscaleVec);
            window.draw(targetSprite);
        } else {
            sf::Shader & blurShader =
                getgResHandlerPtr()->getShader(ResHandler::Shader::blur);
            secondPass.clear(sf::Color::Transparent);
            sf::Vector2u textureSize = target.getSize();
            float blurAmount = UI.getBlurAmount();
            const sf::Glsl::Vec2 vBlur =
                sf::Glsl::Vec2(0.f, blurAmount / textureSize.y);
            blurShader.setUniform("blur_radius", vBlur);
            secondPass.draw(sf::Sprite(target.getTexture()), &blurShader);
            secondPass.display();
            const sf::Glsl::Vec2 hBlur =
                sf::Glsl::Vec2(blurAmount / textureSize.x, 0.f);
            blurShader.setUniform("blur_radius", hBlur);
            sf::Sprite targetSprite(secondPass.getTexture());
            window.setView(camera.getWindowView());
            targetSprite.setScale(upscaleVec);
            window.draw(targetSprite, &blurShader);
            if (!stashed && (UI.getState() == ui::Backend::State::statsScreen ||
                             UI.getState() == ui::Backend::State::menuScreen) &&
                !camera.moving()) {
                stash.clear(sf::Color::Black);
                stash.draw(sf::Sprite(secondPass.getTexture()), &blurShader);
                stash.display();
                stashed = true;
                preload = false;
            }
        }
    } else if (!UI.blurEnabled() && UI.desaturateEnabled()) {
        sf::Shader & desaturateShader =
            getgResHandlerPtr()->getShader(ResHandler::Shader::desaturate);
        desaturateShader.setUniform("amount", UI.getDesaturateAmount());
        sf::Sprite targetSprite(target.getTexture());
        window.setView(camera.getWindowView());
        targetSprite.setScale(upscaleVec);
        window.draw(targetSprite, &desaturateShader);
    } else {
        sf::Sprite targetSprite(target.getTexture());
        window.setView(camera.getWindowView());
        targetSprite.setScale(upscaleVec);
        window.draw(targetSprite);
    }
    {
        std::lock_guard<std::mutex> UILock(UIMutex);
        if (player.getState() == Player::State::dead) {
            UI.draw(window, uiFrontend);
        } else {
            if (transitionState == TransitionState::None) {
                UI.draw(window, uiFrontend);
            }
            uiFrontend.draw(window);
        }
    }
    window.setView(worldView);
    drawTransitions(window);
    window.display();
}

void Game::updateLogic(LuaProvider & luaProv) {
    if (!::gameHasFocus) {
        util::sleep(milliseconds(200));
        return;
    }
    // Blurring is graphics intensive, the game caches frames in a RenderTexture
    // when possible
    if (stashed && UI.getState() != ui::Backend::State::statsScreen &&
        UI.getState() != ui::Backend::State::menuScreen) {
        stashed = false;
    }
    if (!stashed || preload) {
        std::lock_guard<std::mutex> overworldLock(overworldMutex);
        if (level != 0) {
            const sf::Vector2f & cameraOffset = camera.getOffsetFromStart();
            bkg.setOffset(cameraOffset.x, cameraOffset.y);
        } else { // TODO: why is this necessary...?
            bkg.setOffset(0, 0);
        }
        tiles.update();
        luaProv.applyHook([this](lua_State * state) {
            lua_getglobal(state, "classes");
            if (!lua_istable(state, -1)) {
                throw std::runtime_error("Error: missing classtable");
            }
            for (auto & kvp : this->entityTable) {
                lua_getfield(state, -1, kvp.first.c_str());
                if (!lua_istable(state, -1)) {
                    throw std::runtime_error(
                        "Error: classtable entry is not table");
                }
                for (auto it = kvp.second.begin(); it != kvp.second.end();
                     ++it) {
                    time_point start = high_resolution_clock::now();
                    lua_getfield(state, -1, "OnUpdate");
                    if (!lua_isfunction(state, -1)) {
                        const std::string err =
                            "Error: missing or malformed OnUpdate for class" +
                            kvp.first;
                    }
                    lua_pushlightuserdata(state, (void *)(&(*it)));
                    if (lua_pcall(state, 1, 0, 9)) {
                        throw std::runtime_error(lua_tostring(state, -1));
                    }
                    time_point stop = high_resolution_clock::now();
                    duration diff =
                        std::chrono::duration_cast<nanoseconds>(stop - start);
                    std::cout << diff.count() << "\n";
                }
                lua_pop(state, 1);
            }
            lua_pop(state, 1);
        });
        auto objUpdatePolicy = [this](auto & vec) {
            for (auto it = vec.begin(); it != vec.end();) {
                if ((*it)->getKillFlag()) {
                    it = vec.erase(it);
                } else {
                    (*it)->update(this->elapsedTime, this);
                    ++it;
                }
            }
        };
        detailGroup.apply(objUpdatePolicy);
        std::vector<sf::Vector2f> cameraTargets;
        // en.update(this, !UI.isOpen(), elapsedTime, cameraTargets);
        camera.update(elapsedTime, cameraTargets);
        if (player.visible) {
            player.update(this, elapsedTime, sounds);
            const sf::Vector2f playerPos = player.getPosition();
            sf::Listener::setPosition(playerPos.x, playerPos.y, 35.f);
        }
        if (!UI.isOpen()) {
            effectGroup.apply(objUpdatePolicy);
        }
    }
    {
        std::lock_guard<std::mutex> UILock(UIMutex);
        if (player.getState() == Player::State::dead) {
            UI.dispDeathSeq();
            if (UI.isComplete()) {
                UI.reset();
                player.reset();
                // Game::nextLevel() increments level, set to -1 so that it will
                // be zero
                level = -1;
                this->nextLevel();
                uiFrontend.reset();
                static const char playerStartingHealth = 4;
                uiFrontend.updateHealth(playerStartingHealth);
                uiFrontend.updateMaxHealth(playerStartingHealth);
                uiFrontend.setWaypointText(level);
            }
            UI.update(this, elapsedTime);
        } else {
            if (transitionState == TransitionState::None) {
                UI.update(this, elapsedTime);
            }
        }
    }
    updateTransitions(elapsedTime);
}

void Game::drawTransitions(sf::RenderWindow & window) {
    std::lock_guard<std::mutex> grd(transitionMutex);
    switch (transitionState) {
    case TransitionState::None:
        break;

    case TransitionState::ExitBeamEnter:
        window.draw(beamShape);
        gfxContext.glowSprs1.push_back(beamGlowSpr);
        break;

    case TransitionState::ExitBeamInflate:
        window.draw(beamShape);
        gfxContext.glowSprs1.push_back(beamGlowSpr);
        break;

    case TransitionState::ExitBeamDeflate:
        window.draw(beamShape);
        gfxContext.glowSprs1.push_back(beamGlowSpr);
        break;

    // This isn't stateless, but only because it can't be. Reseting the level
    // involves texture creation, which is graphics code and therefore needs to
    // happen on the main thread for portability reasons.
    case TransitionState::TransitionOut:
        if (level != 0) {
            if (timer > 100000) {
                uint8_t alpha =
                    math::smoothstep(0.f, 900000, timer - 100000) * 255;
                transitionShape.setFillColor(sf::Color(0, 0, 0, alpha));
                window.draw(transitionShape);
            }
            if (timer > 1000000) {
                transitionState = TransitionState::TransitionIn;
                timer = 0;
                transitionShape.setFillColor(sf::Color(0, 0, 0, 255));
                beamGlowSpr.setColor(sf::Color::Black);
                this->nextLevel(); // Creates textures, needs to happen on main
                                   // thread
            }
        } else {
            if (timer > 1600000) {
                uint8_t alpha =
                    math::smoothstep(0.f, 1400000, timer - 1600000) * 255;
                transitionShape.setFillColor(sf::Color(0, 0, 0, alpha));
                window.draw(transitionShape);
                uint8_t textAlpha =
                    Easing::easeOut<1>(timer - 1600000,
                                       static_cast<int_fast64_t>(600000)) *
                    255;
                uiFrontend.drawTitle(textAlpha, window);
            } else {
                uiFrontend.drawTitle(255, window);
            }
            if (timer > 3000000) {
                transitionState = TransitionState::TransitionIn;
                beamGlowSpr.setColor(sf::Color::Black);
                timer = 0;
                transitionShape.setFillColor(sf::Color(0, 0, 0, 255));
                this->nextLevel();
            }
        }
        break;

    case TransitionState::TransitionIn:
        window.draw(transitionShape);
        break;

    case TransitionState::EntryBeamDrop:
        window.draw(beamShape);
        gfxContext.glowSprs1.push_back(beamGlowSpr);
        break;

    case TransitionState::EntryBeamFade:
        window.draw(beamShape);
        gfxContext.glowSprs1.push_back(beamGlowSpr);
        break;
    }
}

void Game::updateTransitions(const sf::Time & elapsedTime) {
    std::lock_guard<std::mutex> grd(transitionMutex);
    switch (transitionState) {
    case TransitionState::None: {
        auto teleporterAddr =
            detailGroup.get<DetailRef::Teleporter>().back().get();
        auto teleporterPos = teleporterAddr->getPosition();
        if ((std::abs(player.getXpos() - teleporterPos.x) < 8 &&
             std::abs(player.getYpos() - teleporterPos.y + 12) < 8)) {
            player.setPosition(teleporterPos.x - 2.f, teleporterPos.y - 16.f);
            player.setState(Player::State::deactivated);
            if (!camera.moving() &&
                (UI.getPowerupBubbleState() ==
                     ui::Backend::PowerupBubbleState::closed ||
                 UI.getPowerupBubbleState() ==
                     ui::Backend::PowerupBubbleState::dormant)) {
                transitionState = TransitionState::ExitBeamEnter;
            }
        }
        beamShape.setPosition(viewPort.x / 2 - 1.5, viewPort.y / 2 + 48);
        beamShape.setFillColor(sf::Color(114, 255, 229, 6));
        beamShape.setSize(sf::Vector2f(2, 0));
        beamGlowSpr.setPosition(viewPort.x / 2 - 200,
                                viewPort.y / 2 - 200 + 36);
    } break;

    case TransitionState::ExitBeamEnter:
        timer += elapsedTime.asMicroseconds();
        {
            static const int_fast64_t transitionTime = 500000;
            static const int_fast64_t alphaTransitionTime = 450000;
            const int beamTargetY = -(viewPort.y / 2 + 48);
            float beamHeight =
                Easing::easeIn<1>(timer, transitionTime) * beamTargetY;
            uint8_t brightness = Easing::easeIn<1>(timer, transitionTime) * 255;
            uint_fast8_t alpha =
                Easing::easeIn<1>(timer, alphaTransitionTime) * 255;
            beamGlowSpr.setColor(
                sf::Color(brightness, brightness, brightness, 255));
            beamShape.setFillColor(sf::Color(114, 255, 229, alpha));
            beamShape.setSize(sf::Vector2f(2, beamHeight));
            if (timer > transitionTime) {
                timer = 0;
                beamShape.setSize(sf::Vector2f(2, -(viewPort.y / 2 + 48)));
                beamShape.setFillColor(sf::Color(114, 255, 229, 255));
                transitionState = TransitionState::ExitBeamInflate;
            }
        }
        break;

    case TransitionState::ExitBeamInflate:
        timer += elapsedTime.asMicroseconds();
        {
            static const int64_t transitionTime = 250000;
            float beamWidth =
                std::max(2.f, Easing::easeIn<2>(timer, transitionTime) * 20.f);
            float beamHeight = beamShape.getSize().y;
            beamShape.setSize(sf::Vector2f(beamWidth, beamHeight));
            beamShape.setPosition(viewPort.x / 2 - 0.5f - beamWidth / 2.f,
                                  viewPort.y / 2 + 48);
            if (timer > transitionTime) {
                timer = 0;
                transitionState = TransitionState::ExitBeamDeflate;
                player.visible = false;
            }
        }
        break;

    case TransitionState::ExitBeamDeflate:
        timer += elapsedTime.asMilliseconds();
        {
            // beamWidth is carefully calibrated, be sure to recalculate the
            // regression based on the timer if you change it...
            float beamWidth =
                0.9999995 *
                std::exp(-0.0050125355 * static_cast<double>(timer)) * 20.f;
            float beamHeight = beamShape.getSize().y;
            beamShape.setSize(sf::Vector2f(beamWidth, beamHeight));
            beamShape.setPosition(viewPort.x / 2 - 0.5f - beamWidth / 2.f,
                                  viewPort.y / 2 + 48);
            if (timer >= 640) {
                timer = 0;
                transitionState = TransitionState::TransitionOut;
            }
        }
        break;

    case TransitionState::TransitionOut:
        timer += elapsedTime.asMicroseconds();
        // Logic updates instead when drawing transitions, see above comment.
        break;

    case TransitionState::TransitionIn:
        timer += elapsedTime.asMicroseconds();
        {
            uint8_t alpha = 255 - math::smoothstep(0.f, 800000, timer) * 255;
            transitionShape.setFillColor(sf::Color(0, 0, 0, alpha));
        }
        if (timer >= 800000) {
            if (level != 0) {
                transitionState = TransitionState::EntryBeamDrop;
            } else {
                transitionState = TransitionState::None;
            }
            timer = 0;
            beamShape.setSize(sf::Vector2f(4, 0));
            beamShape.setPosition(viewPort.x / 2 - 2, 0);
            beamShape.setFillColor(sf::Color(114, 255, 229, 240));
        }
        break;

    case TransitionState::EntryBeamDrop:
        timer += elapsedTime.asMicroseconds();
        {
            static const int64_t transitionTime = 350000;
            float beamHeight = Easing::easeIn<2>(timer, transitionTime) *
                               (viewPort.y / 2 + 36);
            uint8_t brightness = Easing::easeIn<1>(timer, transitionTime) * 255;
            beamGlowSpr.setColor(
                sf::Color(brightness, brightness, brightness, 255));
            beamShape.setSize(sf::Vector2f(4, beamHeight));
            if (timer > transitionTime) {
                transitionState = TransitionState::EntryBeamFade;
                timer = 0;
                player.visible = true;
                util::sleep(milliseconds(20));
                camera.shake(0.19f);
            }
        }
        break;

    case TransitionState::EntryBeamFade:
        timer += elapsedTime.asMicroseconds();
        {
            static const int64_t transitionTime = 300000;
            uint8_t alpha = Easing::easeOut<1>(timer, transitionTime) * 240;
            beamShape.setFillColor(sf::Color(114, 255, 229, alpha));
            uint8_t brightness =
                Easing::easeOut<2>(timer, transitionTime) * 255;
            beamGlowSpr.setColor(
                sf::Color(brightness, brightness, brightness, 255));
            if (timer > transitionTime) {
                transitionState = TransitionState::None;
                player.setState(Player::State::nominal);
                timer = 0;
            }
        }
        break;
    }
}

void Game::nextLevel() {
    level += 1;
    uiFrontend.setWaypointText(level);
    tiles.clear();
    effectGroup.clear();
    detailGroup.clear();
    player.setPosition(viewPort.x / 2 - 17, viewPort.y / 2);
    // en.clear();
    if (level == 0) {
        camera.snapToTarget();
        set = tileController::Tileset::intro;
    } else {
        camera.panDown();
        set = tileController::Tileset::regular;
    }
    // vignetteSprite.setColor(sf::Color::White); // TODO: See if this line is
    // actually benificial
    if (set != tileController::Tileset::intro) {
        int count;
        do {
            count = generateMap(tiles.mapArray);
        } while (count < 150);
    }
    tiles.rebuild(set);
    bkg.setBkg(tiles.getWorkingSet());
    tiles.setPosition((viewPort.x / 2) - 16, (viewPort.y / 2));
    bkg.setPosition((tiles.posX / 2) + 206, tiles.posY / 2);
    auto pickLocation = [](std::vector<Coordinate> & emptyLocations)
        -> framework::option<Coordinate> {
        if (emptyLocations.size() > 0) {
            int locationSelect = rng::random(emptyLocations.size());
            Coordinate c = emptyLocations[locationSelect];
            emptyLocations[locationSelect] = emptyLocations.back();
            emptyLocations.pop_back();
            return framework::option<Coordinate>(c);
        } else {
            return {};
        }
    };
    auto emptyOncreate = [](auto created) {};
    if (level != 0) {
        Coordinate c = tiles.getTeleporterLoc();
        detailGroup.add<DetailRef::Teleporter>(
            tiles.posX + c.x * 32 + 2, tiles.posY + c.y * 26 - 4,
            getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
            getgResHandlerPtr()->getTexture(
                ResHandler::Texture::teleporterGlow));
        // sounds.play(ResHandler::Sound::electricHum,
        // detailGroup.get<DetailRef::Teleporter>().back(), 72.f, 3.f, true);
        initEnemies(this);
        auto optCoord = pickLocation(tiles.emptyMapLocations);
        if (optCoord) {
            Powerup chestContents = static_cast<Powerup>(rng::random<2, 1>());
            detailGroup.add<DetailRef::TreasureChest>(
                optCoord.value().x * 32 + tiles.posX,
                optCoord.value().y * 26 + tiles.posY,
                getgResHandlerPtr()->getTexture(
                    ResHandler::Texture::gameObjects),
                chestContents);
        }
        if (!rng::random<2>()) {
            auto pCoordVec = tiles.getEmptyLocations();
            const size_t vecSize = pCoordVec->size();
            const int locationSel = rng::random(vecSize / 3);
            const int xInit = (*pCoordVec)[vecSize - 1 - locationSel].x;
            const int yInit = (*pCoordVec)[vecSize - 1 - locationSel].y;
            detailGroup.add<DetailRef::Terminal>(
                xInit * 32 + tiles.posX, yInit * 26 + tiles.posY,
                getgResHandlerPtr()->getTexture(
                    ResHandler::Texture::gameObjects),
                tiles.mapArray[xInit][yInit]);
        }
        gfxContext.glowSprs1.clear();
        gfxContext.glowSprs2.clear();
        Circle teleporterFootprint;
        teleporterFootprint.x = tiles.getTeleporterLoc().x;
        teleporterFootprint.y = tiles.getTeleporterLoc().y;
        teleporterFootprint.r = 50;
        std::vector<Coordinate> detailPositions;
        if (set == tileController::Tileset::regular) {
            getRockPositions(tiles.mapArray, detailPositions,
                             teleporterFootprint);
            for (auto element : detailPositions) {
                detailGroup.add<DetailRef::Rock>(
                    tiles.posX + 32 * element.x,
                    tiles.posY + 26 * element.y - 35,
                    getgResHandlerPtr()->getTexture(
                        ResHandler::Texture::gameObjects));
            }
            detailPositions.clear();
        }
        getLightingPositions(tiles.mapArray, detailPositions,
                             teleporterFootprint);
        const size_t len = detailPositions.size();
        for (size_t i = 0; i < len; i++) {
            detailGroup.add<DetailRef::Lamp>(
                tiles.posX + 16 + (detailPositions[i].x * 32),
                tiles.posY - 3 + (detailPositions[i].y * 26),
                getgResHandlerPtr()->getTexture(
                    ResHandler::Texture::gameObjects),
                getgResHandlerPtr()->getTexture(
                    ResHandler::Texture::lamplight));
        }
        detailPositions.clear();
    } else if (set == tileController::Tileset::intro) {
        detailGroup.add<DetailRef::Lamp>(
            tiles.posX - 180 + 16 + (5 * 32), tiles.posY + 200 - 3 + (6 * 26),
            getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
            getgResHandlerPtr()->getTexture(ResHandler::Texture::lamplight));
        detailGroup.add<DetailRef::Lamp>(
            tiles.posX - 180 + 16 + (5 * 32), tiles.posY + 200 - 3 + (0 * 26),
            getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
            getgResHandlerPtr()->getTexture(ResHandler::Texture::lamplight));
        detailGroup.add<DetailRef::Lamp>(
            tiles.posX - 180 + 16 + (11 * 32), tiles.posY + 200 - 3 + (11 * 26),
            getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
            getgResHandlerPtr()->getTexture(ResHandler::Texture::lamplight));
        detailGroup.add<DetailRef::Lamp>(
            tiles.posX - 180 + 16 + (10 * 32), tiles.posY + 204 + 8 + (-9 * 26),
            getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
            getgResHandlerPtr()->getTexture(ResHandler::Texture::lamplight));
        detailGroup.add<DetailRef::IntroDoor>(
            tiles.posX - 192 + 6 * 32, tiles.posY + 301,
            getgResHandlerPtr()->getTexture(ResHandler::Texture::introWall));
        sf::Sprite podSpr;
        podSpr.setTexture(
            getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects));
        podSpr.setTextureRect(sf::IntRect(164, 145, 44, 50));
        detailGroup.add<DetailRef::StaticDrawable>(
            tiles.posX + 3 * 32, tiles.posY + 4 + 17 * 26, podSpr);
        static const int initTeleporterLocX = 8;
        static const int initTeleporterLocY = -7;
        tiles.teleporterLocation.x = initTeleporterLocX;
        tiles.teleporterLocation.y = initTeleporterLocY;
        detailGroup.add<DetailRef::Teleporter>(
            tiles.posX - 178 + 8 * 32, tiles.posY + 284 + -7 * 26,
            getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
            getgResHandlerPtr()->getTexture(
                ResHandler::Texture::teleporterGlow));
        // sounds.play(ResHandler::Sound::electricHum,
        // detailGroup.get<DetailRef::Teleporter>().back(), 72.f, 3.f, true);
        for (auto it = ::levelZeroWalls.begin(); it != ::levelZeroWalls.end();
             ++it) {
            wall w;
            w.setXinit(it->first);
            w.setYinit(it->second);
            tiles.walls.push_back(w);
        }
    }
}

DetailGroup & Game::getDetails() { return detailGroup; }

// enemyController & Game::getEnemyController() { return en; }

tileController & Game::getTileController() { return tiles; }

Player & Game::getPlayer() { return player; }

Camera & Game::getCamera() { return camera; }

EffectGroup & Game::getEffects() { return effectGroup; }

InputController & Game::getInputController() { return input; }

ui::Backend & Game::getUI() { return UI; }

ui::Frontend & Game::getUIFrontend() { return uiFrontend; }

SoundController & Game::getSounds() { return sounds; }

int Game::getLevel() { return level; }

sf::RenderWindow & Game::getWindow() { return window; }

const std::array<std::pair<float, float>, 59> levelZeroWalls{
    {std::make_pair(-20, 500), std::make_pair(-20, 526),
     std::make_pair(-20, 474), std::make_pair(-20, 448),
     std::make_pair(-20, 422), std::make_pair(-20, 396),
     std::make_pair(-20, 370), std::make_pair(-20, 552),
     std::make_pair(-20, 578), std::make_pair(196, 500),
     std::make_pair(196, 526), std::make_pair(196, 474),
     std::make_pair(196, 448), std::make_pair(196, 422),
     std::make_pair(196, 396), std::make_pair(196, 370),
     std::make_pair(196, 552), std::make_pair(196, 578),
     std::make_pair(12, 604),  std::make_pair(44, 604),
     std::make_pair(76, 604),  std::make_pair(108, 604),
     std::make_pair(140, 604), std::make_pair(172, 604),
     std::make_pair(12, 370),  std::make_pair(34, 370),
     std::make_pair(120, 370), std::make_pair(152, 370),
     std::make_pair(184, 370), std::make_pair(34, 344),
     std::make_pair(120, 344), std::make_pair(34, 318),
     std::make_pair(120, 318), std::make_pair(34, 292),
     std::make_pair(120, 292), std::make_pair(34, 266),
     std::make_pair(120, 266), std::make_pair(12, 266),
     std::make_pair(-20, 266), std::make_pair(152, 266),
     std::make_pair(-20, 240), std::make_pair(172, 240),
     std::make_pair(-20, 214), std::make_pair(172, 214),
     std::make_pair(-20, 188), std::make_pair(172, 188),
     std::make_pair(-20, 162), std::make_pair(172, 162),
     std::make_pair(-20, 136), std::make_pair(172, 136),
     std::make_pair(-20, 110), std::make_pair(172, 110),
     std::make_pair(-20, 84),  std::make_pair(172, 84),
     std::make_pair(12, 58),   std::make_pair(44, 58),
     std::make_pair(76, 58),   std::make_pair(108, 58),
     std::make_pair(140, 58)}};

const sf::Time & Game::getElapsedTime() { return elapsedTime; }

void Game::setElapsedTime(const sf::Time & elapsedTime) {
    this->elapsedTime = elapsedTime;
}

static Game * pGame;

void setgGamePtr(Game * pGame) { ::pGame = pGame; }

Game * getgGamePtr() { return ::pGame; }

EntityTable & Game::getEntityTable() { return entityTable; }

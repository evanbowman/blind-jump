#include "Game.hpp"

extern bool gameHasFocus;

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
	    helperGroup.apply(drawPolicy);
            en.draw(gfxContext.faces, gfxContext.shadows, camera);
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

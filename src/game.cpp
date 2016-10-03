//========================================================================//
// Copyright (C) 2016 Evan Bowman										  //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.			  //
//========================================================================//

#include "mappingFunctions.hpp"
#include "enemyPlacementFn.hpp"
#include "easingTemplates.hpp"
#include "initMapVectors.hpp"
#include "pillarPlacement.h"
#include "ResourcePath.hpp"
#include "lightingMap.h"
#include "game.hpp"
#include "math.h"

namespace global {
	std::mutex overworldMutex, UIMutex, transitionMutex;
}

Game::Game(const sf::Vector2f & viewPort, InputController * _pInput, ui::Frontend * _pUiFrontend)
	: windowW(viewPort.x),
	  windowH(viewPort.y),
	  transitionState(TransitionState::None),
	  pInput(_pInput),
	  player(viewPort.x / 2, viewPort.y / 2),
	  camera(&player, viewPort),
	  pUiFrontend(_pUiFrontend),
	  level(0),
	  stashed(false),
	  preload(false),
	  worldView(sf::Vector2f(viewPort.x / 2, viewPort.y / 2), viewPort),
	  timer(0)
{
	init();
}

void Game::init() {
	target.create(windowW, windowH);
	secondPass.create(windowW, windowH);
	secondPass.setSmooth(true);
	thirdPass.create(windowW, windowH);
	thirdPass.setSmooth(true);
	stash.create(windowW, windowH);
	stash.setSmooth(true);
	lightingMap.create(windowW, windowH);
	vignetteSprite.setTexture(global::resHandlerPtr->getTexture(ResHandler::Texture::vignette));
	vignetteShadowSpr.setTexture(global::resHandlerPtr->getTexture(ResHandler::Texture::vignetteShadow));
	beamGlowSpr.setTexture(global::resHandlerPtr->getTexture(ResHandler::Texture::teleporterBeamGlow));
	vignetteSprite.setScale(windowW / 450, windowH / 450);
	vignetteShadowSpr.setScale(windowW / 450, windowH / 450);
	vignetteShadowSpr.setColor(sf::Color(255,255,255,100));
	hudView.setSize(windowW, windowH);
	hudView.setCenter(windowW / 2, windowH / 2);
	bkg.giveWindowSize(windowW, windowH);
	tiles.setPosition((windowW / 2) - 16, (windowH / 2));
	tiles.setWindowSize(windowW, windowH);
	en.setWindowSize(windowW, windowH);
	pUiFrontend->setWaypointText(level);
	beamGlowSpr.setColor(sf::Color(0, 0, 0, 255));
	transitionShape.setSize(sf::Vector2f(windowW, windowH));
	transitionShape.setFillColor(sf::Color(0, 0, 0, 0));
	vignetteSprite.setColor(sf::Color::White);
	level = -1;
	this->nextLevel();
}

void Game::draw(sf::RenderWindow & window) {
	if (!pInput->isFocused()) {
		util::sleep(milliseconds(200));
		return;
	}
	target.clear(sf::Color::Transparent);
	if (!stashed || preload) {
		{
			std::lock_guard<std::mutex> overworldLock(global::overworldMutex);
			lightingMap.setView(camera.getView());
			bkg.drawBackground(target, worldView, camera);
			tiles.draw(target, &glowSprs1, level, worldView, camera.getView());
			glowSprs2.clear();
			glowSprs1.clear();
			gameShadows.clear();
			gameObjects.clear();
			target.setView(camera.getView());
			const sf::Vector2f viewCenter = camera.getView().getCenter();
			const sf::Vector2f viewSize = camera.getView().getSize();
			drawGroup(details, gameObjects, gameShadows, glowSprs1, glowSprs2, target, viewCenter, viewSize);
			if (player.visible) {
				player.draw(gameObjects, gameShadows);
			}
			drawGroup(effectGroup, gameObjects, glowSprs1, viewCenter, viewSize);
			en.draw(gameObjects, gameShadows, camera);
			sounds.poll();
		}
		if (!gameShadows.empty()) {
			for (const auto & element : gameShadows) {
				target.draw(std::get<0>(element));
			}
		}
		target.setView(worldView);
		lightingMap.clear(sf::Color::Transparent);
		// Sort the game objects based on y-position for z-ordering
		static const size_t zOrderIdx = 1;
		std::sort(gameObjects.begin(), gameObjects.end(), [](const drawableMetadata & arg1,
															 const drawableMetadata & arg2) {
					  return (std::get<zOrderIdx>(arg1) < std::get<zOrderIdx>(arg2));
				  });
		window.setView(worldView);
		static const size_t sprIdx = 0;
		static const size_t shaderIdx = 3;
		sf::Shader & colorShader = global::resHandlerPtr->getShader(ResHandler::Shader::color);
		for (auto & element : gameObjects) {
			switch (std::get<2>(element)) {
			case Rendertype::shadeDefault:
				std::get<0>(element).setColor(sf::Color(190, 190, 210, std::get<sprIdx>(element).getColor().a));
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
		for (auto & element : glowSprs2) {
			element.setColor(blendAmount);
			lightingMap.draw(element, sf::BlendMode(sf::BlendMode(sf::BlendMode::SrcAlpha, sf::BlendMode::One,
																  sf::BlendMode::Add, sf::BlendMode::DstAlpha,
																  sf::BlendMode::Zero, sf::BlendMode::Add)));
		}
		lightingMap.display();
		target.draw(sf::Sprite(lightingMap.getTexture()));
		target.setView(camera.getView());
		bkg.drawForeground(target);
		target.setView(worldView);
		target.draw(vignetteSprite, sf::BlendMultiply);
		target.draw(vignetteShadowSpr);
		target.display();
	}
	if (UI.blurEnabled() && UI.desaturateEnabled()) {
		if (stashed) {
			window.setView(worldView);
			window.draw(sf::Sprite(stash.getTexture()));
		} else {
			sf::Shader & blurShader = global::resHandlerPtr->getShader(ResHandler::Shader::blur);
			sf::Shader & desaturateShader = global::resHandlerPtr->getShader(ResHandler::Shader::desaturate);
			secondPass.clear(sf::Color::Transparent);
			thirdPass.clear(sf::Color::Transparent);
			const sf::Vector2u textureSize = target.getSize();
			// Get the blur amount from the UI controller
			float blurAmount = UI.getBlurAmount();
			const sf::Glsl::Vec2 vBlur = sf::Glsl::Vec2(0.f, blurAmount / textureSize.y);
			blurShader.setUniform("blur_radius", vBlur);
			secondPass.draw(sf::Sprite(target.getTexture()), &blurShader);
			secondPass.display();
			const sf::Glsl::Vec2 hBlur = sf::Glsl::Vec2(blurAmount / textureSize.x, 0.f);
			blurShader.setUniform("blur_radius", hBlur);
			thirdPass.draw(sf::Sprite(secondPass.getTexture()), &blurShader);
			thirdPass.display();
			desaturateShader.setUniform("amount", UI.getDesaturateAmount());
			window.draw(sf::Sprite(thirdPass.getTexture()), &desaturateShader);
			if (!stashed && (UI.getState() == ui::Backend::State::statsScreen
							 || UI.getState() == ui::Backend::State::menuScreen) && !camera.moving()) {
				stash.clear(sf::Color::Black);
				stash.draw(sf::Sprite(thirdPass.getTexture()), &desaturateShader);
				stash.display();
				stashed = true;
			}
		}
	} else if (UI.blurEnabled() && !UI.desaturateEnabled()) {
		if (stashed) {
			if (pInput->pausePressed()) {
				preload = true;
			}
			window.setView(worldView);
			window.draw(sf::Sprite(stash.getTexture()));
		} else {
			sf::Shader & blurShader = global::resHandlerPtr->getShader(ResHandler::Shader::blur);
			secondPass.clear(sf::Color::Transparent);
			sf::Vector2u textureSize = target.getSize();
			// Get the blur amount from the UI controller
			float blurAmount = UI.getBlurAmount();
			const sf::Glsl::Vec2 vBlur = sf::Glsl::Vec2(0.f, blurAmount / textureSize.y);
			blurShader.setUniform("blur_radius", vBlur);
			secondPass.draw(sf::Sprite(target.getTexture()), &blurShader);
			secondPass.display();
			const sf::Glsl::Vec2 hBlur = sf::Glsl::Vec2(blurAmount / textureSize.x, 0.f);
			blurShader.setUniform("blur_radius", hBlur);
			window.draw(sf::Sprite(secondPass.getTexture()), &blurShader);
			if (!stashed && (UI.getState() == ui::Backend::State::statsScreen
							 || UI.getState() == ui::Backend::State::menuScreen) && !camera.moving()) {
				stash.clear(sf::Color::Black);
				stash.draw(sf::Sprite(secondPass.getTexture()), &blurShader);
				stash.display();
				stashed = true;
				preload = false;
			}
		}
	} else if (!UI.blurEnabled() && UI.desaturateEnabled()) {
		sf::Shader & desaturateShader = global::resHandlerPtr->getShader(ResHandler::Shader::desaturate);
		desaturateShader.setUniform("amount", UI.getDesaturateAmount());
		window.draw(sf::Sprite(target.getTexture()), &desaturateShader);
	} else {
		window.draw(sf::Sprite(target.getTexture()));
	}
	{
		std::lock_guard<std::mutex> UILock(global::UIMutex);
		if (player.getState() == Player::State::dead) {
			UI.draw(window, *pUiFrontend);
		} else {
			if (transitionState == TransitionState::None) {
				UI.draw(window, *pUiFrontend);
			}
			pUiFrontend->draw(window);
		}
	}
	window.setView(worldView);
	drawTransitions(window);
}

void Game::update(sf::Time & elapsedTime) {
	if (!pInput->isFocused()) {
		util::sleep(milliseconds(200));
		return;
	}
	// Blurring is graphics intensive, the game caches frames in a RenderTexture when possible
	if (stashed && UI.getState() != ui::Backend::State::statsScreen && UI.getState() != ui::Backend::State::menuScreen) {
		stashed = false;
	}
	if (!stashed || preload) {
		std::lock_guard<std::mutex> overworldLock(global::overworldMutex);
		if (level != 0) {
			const sf::Vector2f & cameraOffset = camera.getOffset();
			bkg.setOffset(cameraOffset.x, cameraOffset.y);
		} else { // TODO: why is this necessary...?
			bkg.setOffset(0, 0);
		}
		tiles.update();
		auto groupUpdatePolicy = [& elapsedTime](auto & vec) {
			for (auto it = vec.begin(); it != vec.end();) {
				if (it->getKillFlag()) {
					it = vec.erase(it);
				} else {
					it->update(elapsedTime);
					++it;
				}
			}
		};
		details.apply(groupUpdatePolicy);
		std::vector<sf::Vector2f> cameraTargets;
		en.update(this, player.getXpos(), player.getYpos(), !UI.isOpen(), elapsedTime, cameraTargets);
		camera.update(elapsedTime, cameraTargets);
		if (player.visible) player.update(this, elapsedTime, sounds);
		if (!UI.isOpen() || (UI.isOpen() && player.getState() == Player::State::dead)) {
			effectGroup.apply(groupUpdatePolicy);
		}
	}
	{
		std::lock_guard<std::mutex> UILock(global::UIMutex);
		if (player.getState() == Player::State::dead) {
			UI.dispDeathSeq();
			if (UI.isComplete()) {
				UI.reset();
				player.reset();
				// Game::nextLevel() increments level, set to -1 so that it will be zero
				level = -1;
				this->nextLevel();
				pUiFrontend->reset();
				static const char playerStartingHealth = 4;
				pUiFrontend->updateHealth(playerStartingHealth);
				pUiFrontend->updateMaxHealth(playerStartingHealth);
				pUiFrontend->setWaypointText(level);
			}
			UI.update(player, *pUiFrontend, pInput, elapsedTime);
		} else {
			if (transitionState == TransitionState::None) {
				UI.update(player, *pUiFrontend, pInput, elapsedTime);
			}
		}
	}
	updateTransitions(elapsedTime);
}

void Game::drawTransitions(sf::RenderWindow & window) {
	std::lock_guard<std::mutex> grd(global::transitionMutex);
	switch (transitionState) {
	case TransitionState::None:
		break;
		
	case TransitionState::ExitBeamEnter:
		window.draw(beamShape);
		glowSprs1.push_back(beamGlowSpr);
		break;
		
	case TransitionState::ExitBeamInflate:
		window.draw(beamShape);
		glowSprs1.push_back(beamGlowSpr);
		break;
		
	case TransitionState::ExitBeamDeflate:
		window.draw(beamShape);
		glowSprs1.push_back(beamGlowSpr);
		break;
		
		// This isn't stateless, but only because it can't be. Reseting the level
		// involves texture creation, which is graphics code and therefore needs to
		// happen on the main thread for portability reasons.
	case TransitionState::TransitionOut:
		if (level != 0) {
			if (timer > 100000) {
				uint8_t alpha = math::smoothstep(0.f, 900000, timer - 100000) * 255;
				transitionShape.setFillColor(sf::Color(0, 0, 0, alpha));
				window.draw(transitionShape);
			}
			if (timer > 1000000) {
				transitionState = TransitionState::TransitionIn;
				timer = 0;
				transitionShape.setFillColor(sf::Color(0, 0, 0, 255));
				beamGlowSpr.setColor(sf::Color::Black);
				this->nextLevel(); // Creates textures, needs to happen on main thread
			}
		} else {
			if (timer > 1600000) {
				uint8_t alpha = math::smoothstep(0.f, 1400000, timer - 1600000) * 255;
				transitionShape.setFillColor(sf::Color(0, 0, 0, alpha));
				window.draw(transitionShape);
				uint8_t textAlpha = Easing::easeOut<1>(timer - 1600000, static_cast<int_fast64_t>(600000)) * 255;
				pUiFrontend->drawTitle(textAlpha, window);
			} else {
				pUiFrontend->drawTitle(255, window);
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
		glowSprs1.push_back(beamGlowSpr);
		break;
		
	case TransitionState::EntryBeamFade:
		window.draw(beamShape);
		glowSprs1.push_back(beamGlowSpr);
		break;
	}
}

void Game::updateTransitions(const sf::Time & elapsedTime) {
	std::lock_guard<std::mutex> grd(global::transitionMutex);
	switch (transitionState) {
	case TransitionState::None:
		{
			// If the player is near the teleporter, snap to its center and deactivate.
			static const size_t teleporterIdx = 0;
			float teleporterX = details.get<teleporterIdx>().back().getPosition().x;
			float teleporterY = details.get<teleporterIdx>().back().getPosition().y;
			if ((std::abs(player.getXpos() - teleporterX) < 8 &&
				 std::abs(player.getYpos() - teleporterY + 12) < 8)) {
				player.setPosition(teleporterX - 2.f, teleporterY - 16.f);
				player.setState(Player::State::deactivated);
				if (!camera.moving()) {
					transitionState = TransitionState::ExitBeamEnter;
				}
			}
			beamShape.setPosition(windowW / 2 - 1.5, windowH / 2 + 36);
			beamShape.setFillColor(sf::Color(114, 255, 229, 6));
			beamShape.setSize(sf::Vector2f(2, 0));
			beamGlowSpr.setPosition(windowW / 2 - 200, windowH / 2 - 200 + 36);
		}
		break;
		
	case TransitionState::ExitBeamEnter:
		timer += elapsedTime.asMicroseconds();
		{
			static const int_fast64_t transitionTime = 500000;
			static const int_fast64_t alphaTransitionTime = 450000;
			const int beamTargetY = -(windowH / 2 + 36);
			float beamHeight = Easing::easeIn<1>(timer, transitionTime) * beamTargetY;
			uint8_t brightness = Easing::easeIn<1>(timer, transitionTime) * 255;
			uint_fast8_t alpha = Easing::easeIn<1>(timer, alphaTransitionTime) * 255;
			beamGlowSpr.setColor(sf::Color(brightness, brightness, brightness, 255));
			beamShape.setFillColor(sf::Color(114, 255, 229, alpha));
			beamShape.setSize(sf::Vector2f(2, beamHeight));
			if (timer > transitionTime) {
				timer = 0;
				beamShape.setSize(sf::Vector2f(2, -(windowH / 2 + 36)));
				beamShape.setFillColor(sf::Color(114, 255, 229, 255));
				transitionState = TransitionState::ExitBeamInflate;
			}
		}
		break;

	case TransitionState::ExitBeamInflate:
		timer += elapsedTime.asMicroseconds();
		{
			static const int64_t transitionTime = 250000;
			float beamWidth = std::max(2.f, Easing::easeIn<2>(timer, transitionTime) * 20.f);
			float beamHeight = beamShape.getSize().y;
			beamShape.setSize(sf::Vector2f(beamWidth, beamHeight));
			beamShape.setPosition(windowW / 2 - 0.5f - beamWidth / 2.f, windowH / 2 + 36);	
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
			// beamWidth is carefully calibrated, be sure to recalculate the regression based on the timer if you change it...
			float beamWidth = 0.9999995 * std::exp(-0.0050125355 * static_cast<double>(timer)) * 20.f;
			float beamHeight = beamShape.getSize().y;
			beamShape.setSize(sf::Vector2f(beamWidth, beamHeight));
			beamShape.setPosition(windowW / 2 - 0.5f - beamWidth / 2.f, windowH / 2 + 36);
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
			transitionState = TransitionState::EntryBeamDrop;
			timer = 0;
			beamShape.setSize(sf::Vector2f(4, 0));
			beamShape.setPosition(windowW / 2 - 2, 0);
			beamShape.setFillColor(sf::Color(114, 255, 229, 240));
		}
		break;

	case TransitionState::EntryBeamDrop:
		timer += elapsedTime.asMicroseconds();
		{
			static const int64_t transitionTime = 350000;
			float beamHeight = Easing::easeIn<2>(timer, transitionTime) * (windowH / 2 + 26);
			uint8_t brightness = Easing::easeIn<1>(timer, transitionTime) * 255;
			beamGlowSpr.setColor(sf::Color(brightness, brightness, brightness, 255));
			beamShape.setSize(sf::Vector2f(4, beamHeight));			
			if (timer > transitionTime) {
				transitionState = TransitionState::EntryBeamFade;
				timer = 0;
				player.visible = true;
				util::sleep(milliseconds(20));
				camera.shake(0.15f);
			}
		}
		break;

	case TransitionState::EntryBeamFade:
		timer += elapsedTime.asMicroseconds();
		{
			static const int64_t transitionTime = 300000;
			uint8_t alpha = Easing::easeOut<1>(timer, transitionTime) * 240;
			beamShape.setFillColor(sf::Color(114, 255, 229, alpha));
			uint8_t brightness = Easing::easeOut<2>(timer, transitionTime) * 255;
			beamGlowSpr.setColor(sf::Color(brightness, brightness, brightness, 255));
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
	pUiFrontend->setWaypointText(level);
	tiles.clear();
	effectGroup.clear();
	details.clear();
	player.setPosition(windowW / 2 - 17, windowH / 2);
	en.clear();
	if (level == 0) {
		camera.snapToTarget();
		set = tileController::Tileset::intro;
	} else {
		camera.panDown();
		set = tileController::Tileset::regular;
	}
	// vignetteSprite.setColor(sf::Color::White); // TODO: See if this line is actually benificial
	if (set != tileController::Tileset::intro) {
		int count;
		do {
			count = generateMap(tiles.mapArray);
		} while (count < 150);
	}
	tiles.rebuild(set);
	bkg.setBkg(tiles.getWorkingSet());
	tiles.setPosition((windowW / 2) - 16, (windowH / 2));
	bkg.setPosition((tiles.posX / 2) + 206, tiles.posY / 2);
	auto pickLocation = [](std::vector<Coordinate> & emptyLocations) -> framework::option<Coordinate> {
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
	static const size_t lampIdx = 2;
	if (level != 0) {
		Coordinate c = tiles.getTeleporterLoc();
		static const size_t teleporterIdx = 0;
		details.add<teleporterIdx>(tiles.posX + c.x * 32 + 2, tiles.posY + c.y * 26 - 4,
								   global::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
								   global::resHandlerPtr->getTexture(ResHandler::Texture::teleporterGlow));
		initEnemies(this);
		// Place 0-2 powerup chests on the map
		int iters = rng::random<2, 1>();
		for (int i = 0; i < iters; i++) {
			auto optCoord = pickLocation(tiles.emptyMapLocations);
			if (optCoord) {
				Powerup chestContents = static_cast<Powerup>(rng::random<2, 1>());
				static const size_t chestIdx = 1;
				details.add<chestIdx>(optCoord.value().x * 32 + tiles.posX, optCoord.value().y * 26 + tiles.posY,
									  global::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects), chestContents);
			}
		}
		glowSprs1.clear();
		glowSprs2.clear();
		Circle teleporterFootprint;
		teleporterFootprint.x = tiles.getTeleporterLoc().x;
		teleporterFootprint.y = tiles.getTeleporterLoc().y;
		teleporterFootprint.r = 50;
		std::vector<Coordinate> detailPositions;
		if (set == tileController::Tileset::regular) {
			getRockPositions(tiles.mapArray, detailPositions, teleporterFootprint);
			for (auto element : detailPositions) {
				static const size_t rockIdx = 3;
				details.add<rockIdx>(tiles.posX + 32 * element.x, tiles.posY + 26 * element.y - 35,
									 global::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects));
			}
			detailPositions.clear();
		}
		getLightingPositions(tiles.mapArray, detailPositions, teleporterFootprint);
		const size_t len = detailPositions.size();
		for (size_t i = 0; i < len; i++) {
			details.add<lampIdx>(tiles.posX + 16 + (detailPositions[i].x * 32),
								 tiles.posY - 3 + (detailPositions[i].y * 26),
								 global::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
								 global::resHandlerPtr->getTexture(ResHandler::Texture::lamplight));
		}
		detailPositions.clear();
	} else if (set == tileController::Tileset::intro) {
		static const size_t doorIdx = 4;
		static const size_t podIdx = 6;
		static const size_t teleporterIdx = 0;
		details.add<lampIdx>(tiles.posX - 180 + 16 + (5 * 32), tiles.posY + 200 - 3 + (6 * 26),
							 global::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
							 global::resHandlerPtr->getTexture(ResHandler::Texture::lamplight));
		details.add<lampIdx>(tiles.posX - 180 + 16 + (5 * 32), tiles.posY + 200 - 3 + (0 * 26),
							 global::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
							 global::resHandlerPtr->getTexture(ResHandler::Texture::lamplight));
		details.add<lampIdx>(tiles.posX - 180 + 16 + (11 * 32), tiles.posY + 200 - 3 + (11 * 26),
							 global::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
							 global::resHandlerPtr->getTexture(ResHandler::Texture::lamplight));
		details.add<lampIdx>(tiles.posX - 180 + 16 + (10 * 32), tiles.posY + 204 + 8 + (-9 * 26),
							 global::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
							 global::resHandlerPtr->getTexture(ResHandler::Texture::lamplight));
		details.add<doorIdx>(tiles.posX - 192 + 6 * 32, tiles.posY + 301,
							 global::resHandlerPtr->getTexture(ResHandler::Texture::introWall));
		sf::Sprite podSpr;
		podSpr.setTexture(global::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects));
		podSpr.setTextureRect(sf::IntRect(164, 145, 44, 50));
		details.add<podIdx>(tiles.posX + 3 * 32, tiles.posY + 4 + 17 * 26, podSpr);
		static const int initTeleporterLocX = 8;
		static const int initTeleporterLocY = -7;
		tiles.teleporterLocation.x = initTeleporterLocX;
		tiles.teleporterLocation.y = initTeleporterLocY;
		details.add<teleporterIdx>(tiles.posX - 178 + 8 * 32, tiles.posY + 284 + -7 * 26,
								   global::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
								   global::resHandlerPtr->getTexture(ResHandler::Texture::teleporterGlow));
		for (auto it = global::levelZeroWalls.begin(); it != global::levelZeroWalls.end(); ++it) {
			wall w;
			w.setXinit(it->first);
			w.setYinit(it->second);
			tiles.walls.push_back(w);
		}
	}
}

DetailGroup & Game::getDetails() {
	return details;
}

enemyController & Game::getEnemyController() {
	return en;
}

tileController & Game::getTileController() {
	return tiles;
}

Player & Game::getPlayer() {
	return player;
}

Camera & Game::getCamera() {
	return camera;
}

EffectGroup & Game::getEffects() {
	return effectGroup;
}

InputController * Game::getPInput() {
	return pInput;
}

ui::Backend & Game::getUI() {
	return UI;
}

ui::Frontend * Game::getPUIFrontend() {
	return pUiFrontend;
}

int Game::getLevel() {
	return level;
}

namespace global {
	const std::array<std::pair<float, float>, 59> levelZeroWalls {
		{ std::make_pair(-20, 500), std::make_pair(-20, 526), std::make_pair(-20, 474),
		  std::make_pair(-20, 448), std::make_pair(-20, 422), std::make_pair(-20, 396),
		  std::make_pair(-20, 370), std::make_pair(-20, 552), std::make_pair(-20, 578),
		  std::make_pair(196, 500), std::make_pair(196, 526), std::make_pair(196, 474),
		  std::make_pair(196, 448), std::make_pair(196, 422), std::make_pair(196, 396),
		  std::make_pair(196, 370), std::make_pair(196, 552), std::make_pair(196, 578),
		  std::make_pair(12, 604),  std::make_pair(44, 604),  std::make_pair(76, 604),
		  std::make_pair(108, 604), std::make_pair(140, 604), std::make_pair(172, 604),
		  std::make_pair(12, 370),  std::make_pair(34, 370),  std::make_pair(120, 370),
		  std::make_pair(152, 370), std::make_pair(184, 370), std::make_pair(34, 344),
		  std::make_pair(120, 344), std::make_pair(34, 318),  std::make_pair(120, 318),
		  std::make_pair(34, 292),  std::make_pair(120, 292), std::make_pair(34, 266),
		  std::make_pair(120, 266),	std::make_pair(12, 266),  std::make_pair(-20, 266),
		  std::make_pair(152, 266), std::make_pair(-20, 240), std::make_pair(172, 240),
		  std::make_pair(-20, 214), std::make_pair(172, 214), std::make_pair(-20, 188),
		  std::make_pair(172, 188), std::make_pair(-20, 162), std::make_pair(172, 162),
		  std::make_pair(-20, 136), std::make_pair(172, 136), std::make_pair(-20, 110),
		  std::make_pair(172, 110), std::make_pair(-20, 84),  std::make_pair(172, 84),
		  std::make_pair(12, 58),   std::make_pair(44, 58),   std::make_pair(76, 58),
		  std::make_pair(108, 58),  std::make_pair(140, 58)}
    };
}

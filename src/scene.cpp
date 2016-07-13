//  Created by Evan Bowman on 10/15/15.

#include "mappingFunctions.hpp"
#include "initMapVectors.hpp"
#include <cmath>
#include "ResourcePath.hpp"
#include "enemyPlacementFn.hpp"
#include "lightingMap.h"
#include "pillarPlacement.h"
#include "math.h"
#include "enemyCreationFunctions.hpp"
#include "scene.hpp"

Scene::Scene(float _windowW, float _windowH, InputController * _pInput, FontController * _pFonts)
	: details{_windowW, _windowH},
	  pInput{_pInput},
	  player{_windowW / 2, _windowH / 2},
	  UI{_windowW / 2, _windowH / 2},
	  tiles{}, // TODO: remove default constructible members
	  en{},
	  pFonts{_pFonts},
	  level{0},
	  teleporterCond{false},
	  windowW{_windowW},
	  windowH{_windowH}  
{
	//Make the background controller draw concenteric with the center of the view
	bkg.setPosition((tiles.posX / 2) + 226, tiles.posY / 2);

	// Set the size of the target render texture so that they'll fill the screen
	target.create(windowW, windowH);
	secondPass.create(windowW, windowH);
	secondPass.setSmooth(true);
	thirdPass.create(windowW, windowH);
	thirdPass.setSmooth(true);
	
	worldView.setSize(windowW, windowH);
	worldView.setCenter(windowW / 2, windowH / 2);
	hudView.setSize(windowW, windowH);
	hudView.setCenter(windowW / 2, windowH / 2);
	
	// Call a function to procedurally distribute items
	initLoot(itemArray);
	
	// Tell the background controller how big the window is so it doesn't draw out of bounds
	bkg.giveWindowSize(windowW, windowH);
	
	UI.setView(&worldView);
	
	// Set up the lighting map
	lightingMap.create(windowW, windowH);
	shadowShape.setFillColor(sf::Color(190, 190, 210, 255));
	sf::Vector2f v;
	v.x = windowW;
	v.y = windowH;
	shadowShape.setSize(v);
	
	transitioning = false;
	transitionDelay = 320;
	
	dispEntryBeam = false;
	transitionIn = false;
	
	// Each object that isn't an effect or passed through a shader gets darkened according to the ambient conditions of the current tileset
	objectShadeColor = sf::Color(190, 190, 210, 255);
	
	vignetteSprite.setTexture(globalResourceHandler.getTexture(ResourceHandler::Texture::vignette));
	vignetteSprite.setScale(windowW / 450, windowH / 450);
	vignetteShadowSpr.setTexture(globalResourceHandler.getTexture(ResourceHandler::Texture::vignetteShadow));
	vignetteShadowSpr.setScale(windowW / 450, windowH / 450);
	vignetteShadowSpr.setColor(sf::Color(255,255,255,100));
	
	//Let the tile controller know where player is
	tiles.setPosition((windowW / 2) - 16, (windowH / 2));
	tiles.setWindowSize(windowW, windowH);
	
	/*  Completely non-general code only used by the intro level */
	details.addLamplight(tiles.posX - 180, tiles.posY + 200, 5, 6, windowW, windowH);
	details.addLamplight(tiles.posX - 180, tiles.posY + 200, 5, 0, windowW, windowH);
	details.addLamplight(tiles.posX - 170, tiles.posY + 200, 11, 11, windowW, windowH);
	details.addLamplight(tiles.posX - 180, tiles.posY + 200, 10, -9, windowW, windowH);
	details.addDoor(tiles.posX - 192, tiles.posY + 301, 6, 0, windowW, windowH);
	details.addPod(tiles.posX, tiles.posY + 33, 3, 17);
	tiles.teleporterLocation.x = 8;
	tiles.teleporterLocation.y = -7;
	for (auto it = global_levelZeroWalls.begin(); it != global_levelZeroWalls.end(); ++it) {
		wall w;
		w.setXinit(it->first);
		w.setYinit(it->second);
		tiles.walls.push_back(w);
	}
	
	en.setWindowSize(windowW, windowH);
	
	//Initialize the fonts
	pFonts->setWaypointText(level);
	
	details.addTeleporter(tiles, tiles.posX - 178, tiles.posY + 284, windowW, windowH);
	
	// initialize the rectangle shape for the teleporter beam effect
	sf::Vector2f v1(2, 1);
	teleporterBeam.setPosition(windowW / 2 - 1.5, windowH / 2 + 36);
	teleporterBeam.setSize(v1);
	teleporterBeam.setFillColor(sf::Color(114, 255, 229, 6));

	// Initialize the rectangle shape for the teleporter entry beam
	sf::Vector2f v2(4, 8);
	entryBeam.setPosition(windowW / 2 - 2, -68);
	entryBeam.setSize(v2);
	entryBeam.setFillColor(sf::Color(104, 255, 229, 180));
	
	bkg.setBkg(0);
	
	beamExpanding = false;
	animationBegin = false;
	dispEntryBeam = false;
	
	sndCtrl.playMusic(0);
	beamGlowTxr.loadFromFile(resourcePath() + "teleporterBeamGlow.png");
	beamGlowSpr.setTexture(beamGlowTxr);
	beamGlowSpr.setPosition(windowW / 2 - 200, windowH / 2 - 200 + 30);
	beamGlowSpr.setColor(sf::Color(0, 0, 0, 255));
	
	transitionShape.setSize(sf::Vector2f(windowW, windowH));
	transitionShape.setFillColor(sf::Color(0, 0, 0, 0));
	
	vignetteSprite.setColor(sf::Color(255, 255, 255));
	
	// Place a weapon chest if needed
	if (itemArray[level][0] != 0) {
		details.addChest(tiles, tiles.posX, tiles.posY, windowW, windowH, itemArray[level][0]);
	}
	
	// place life capsule chests
	if (itemArray[level][1] == 90) {
		details.addChest(tiles, tiles.posX, tiles.posY, windowW, windowH, itemArray[level][1]);
	}
}

void Scene::update(sf::RenderWindow & window, sf::Time & elapsedTime) {
	target.clear(sf::Color::Transparent);
	// Start by getting the displacement that the player has moved, in order to update the position of all of the tiles and game objects
	float xOffset = player.getWorldOffsetX();
	float yOffset = player.getWorldOffsetY();

	bkg.setOffset(xOffset, yOffset);
	bkg.drawBackground(target);
	tiles.setOffset(xOffset, yOffset);
	tiles.drawTiles(target, &glowSprs1, &glowSprs2, level);
	glowSprs2.clear();
	// Update the overworld objects based on the displacement of the player
	details.update(this, elapsedTime, &glowSprs1, &glowSprs2);
	// Draw the details / add them to the game objects vector
	details.draw(gameObjects, gameShadows, target);
	// Update the enemy objects in the game based on the player's displacement
	en.update(gameObjects, gameShadows, player.getWorldOffsetX(), player.getWorldOffsetY(), effectGroup, tiles.walls, player.getState() != Player::State::dead, &tiles, &ssc, *pFonts, elapsedTime);
	// // Draw the lower layer of the effects, that is the ones that should show up behind the player sprite
	// effects.drawLower(target);
	
	if (player.visible) {
		// Draw the player to the window, as long as the object is visible
		player.update(this, elapsedTime);
		player.draw(gameObjects, gameShadows, elapsedTime);
	}
	
	// If player was hit rumble the screen.
	if (player.scrShakeState) {
		ssc.rumble();
	}

	glowSprs1.clear();
	float tempXOff{player.getWorldOffsetX()};
	float tempYOff{player.getWorldOffsetY()};
	effectGroup.update(tempXOff, tempYOff, elapsedTime);
	drawGroup(effectGroup, gameObjects, glowSprs1);
	
	// Draw shadows to the target
	if (!gameShadows.empty()) {
		for (auto & element : gameShadows) {
			target.draw(std::get<0>(element));
		}
	}
	gameShadows.clear();
	
	// Sort the game object based on y-position (performance for this is fine, only sorts objects inside the window, on the ordr of 10 in most cases)
	std::sort(gameObjects.begin(), gameObjects.end(), [](const std::tuple<sf::Sprite, float, Rendertype, float> & arg1, const std::tuple<sf::Sprite, float, Rendertype, float> & arg2) {
		return (std::get<1>(arg1) < std::get<1>(arg2));
	});
	
	lightingMap.clear(sf::Color::Transparent);
	
	window.setView(worldView);

	//===========================================================//
	// Object shading                                            //
	//===========================================================//
	if (!gameObjects.empty()) {
		sf::Shader & colorShader = globalResourceHandler.getShader(ResourceHandler::Shader::color);
		for (auto & element : gameObjects) {
			switch (std::get<2>(element)) {
				case Rendertype::shadeDefault:
					std::get<0>(element).setColor(sf::Color(objectShadeColor.r, objectShadeColor.g, objectShadeColor.b, std::get<0>(element).getColor().a));
					lightingMap.draw(std::get<0>(element));
					break;
					
				case Rendertype::shadeNone:
					lightingMap.draw(std::get<0>(element));
					break;
					
				case Rendertype::shadeWhite:
					colorShader.setParameter("amount", std::get<3>(element));
					colorShader.setParameter("targetColor", sf::Vector3f(1.00, 1.00, 1.00));
					lightingMap.draw(std::get<0>(element), &colorShader);
					break;
					
				case Rendertype::shadeRed:
					colorShader.setParameter("amount", std::get<3>(element));
					colorShader.setParameter("targetColor", sf::Vector3f(0.98, 0.22, 0.03));
					lightingMap.draw(std::get<0>(element), &colorShader);
					break;
					
				case Rendertype::shadeCrimson:
					colorShader.setParameter("amount", std::get<3>(element));
					colorShader.setParameter("targetColor", sf::Vector3f(0.94, 0.09, 0.34));
					lightingMap.draw(std::get<0>(element), &colorShader);
					break;
					
				case Rendertype::shadeNeon:
					colorShader.setParameter("amount", std::get<3>(element));
					colorShader.setParameter("targetColor", sf::Vector3f(0.29, 0.99, 0.99));
					lightingMap.draw(std::get<0>(element), &colorShader);
					break;
			}
		}
	}
	
	sf::Color blendAmount(185, 185, 185, 255);
	sf::Sprite tempSprite;
	for (auto element : glowSprs2) {
		tempSprite = *element;
		tempSprite.setColor(blendAmount);
		tempSprite.setPosition(tempSprite.getPosition().x, tempSprite.getPosition().y - 12);
		lightingMap.draw(tempSprite, sf::BlendMode(sf::BlendMode(sf::BlendMode::SrcAlpha, sf::BlendMode::One, sf::BlendMode::Add, sf::BlendMode::DstAlpha, sf::BlendMode::Zero, sf::BlendMode::Add)));
	}
	
	lightingMap.display();
	target.draw(sf::Sprite(lightingMap.getTexture()));
	
	// Clear out the vectors for the next round of drawing
	gameObjects.clear();
	bkg.drawForeground(target);
	target.draw(vignetteSprite, sf::BlendMultiply);
	target.draw(vignetteShadowSpr);
	target.display();
	
	//===========================================================//
	// Post Processing Effects                                   //
	//===========================================================//
	if (UI.blurEnabled() && UI.desaturateEnabled()) {
		sf::Shader & blurShader = globalResourceHandler.getShader(ResourceHandler::Shader::blur);
		sf::Shader & desaturateShader = globalResourceHandler.getShader(ResourceHandler::Shader::desaturate);
		secondPass.clear(sf::Color::Transparent);
		thirdPass.clear(sf::Color::Transparent);
		sf::Vector2u textureSize = target.getSize();
		// Get the blur amount from the UI controller
		float blurAmount = UI.getBlurAmount();
		blurShader.setParameter("blur_radius", sf::Vector2f(0.f, blurAmount / textureSize.y));
		secondPass.draw(sf::Sprite(target.getTexture()), &blurShader);
		secondPass.display();
		blurShader.setParameter("blur_radius", sf::Vector2f(blurAmount / textureSize.x, 0.f));
		thirdPass.draw(sf::Sprite(secondPass.getTexture()), &blurShader);
		thirdPass.display();
		desaturateShader.setParameter("amount", UI.getDesaturateAmount());
		window.draw(sf::Sprite(thirdPass.getTexture()), &desaturateShader);
	} else if (UI.blurEnabled() && !UI.desaturateEnabled()) {
		sf::Shader & blurShader = globalResourceHandler.getShader(ResourceHandler::Shader::blur);
		secondPass.clear(sf::Color::Transparent);
		sf::Vector2u textureSize = target.getSize();
		// Get the blur amount from the UI controller
		float blurAmount = UI.getBlurAmount();
		blurShader.setParameter("blur_radius", sf::Vector2f(0.f, blurAmount / textureSize.y));
		secondPass.draw(sf::Sprite(target.getTexture()), &blurShader);
		secondPass.display();
		blurShader.setParameter("blur_radius", sf::Vector2f(blurAmount / textureSize.x, 0.f));
		window.draw(sf::Sprite(secondPass.getTexture()), &blurShader);
	} else if (!UI.blurEnabled() && UI.getDesaturateAmount()) {
		sf::Shader & desaturateShader = globalResourceHandler.getShader(ResourceHandler::Shader::desaturate);
		desaturateShader.setParameter("amount", UI.getDesaturateAmount());
		window.draw(sf::Sprite(target.getTexture()), &desaturateShader);
	} else {
		window.draw(sf::Sprite(target.getTexture()));
	}
	
	if (player.getState() == Player::State::dead) {
		// //if (!UI.desaturateEnabled())
		// UI.dispDeathSeq();
		// // If the death sequence is complete and the UI controller is finished playing its animation
		// if (UI.isComplete()) {
		// 	// Reset the UI controller
		// 	UI.reset();
		// 	// Reset the player
		// 	player.reset();
		// 	// Reset the map
		// 	level = -1;
		// 	initLoot(itemArray);
		// 	enemySelectVec.clear();
		// 	Reset();
		// 	pFonts->reset();
		// 	transitionDelay = 320;
		// 	// Set the max health back to 3
		// 	pFonts->updateMaxHealth(4);
		// 	pFonts->setWaypointText(level);
		// 	dispEntryBeam = false;
		// }
		// UI.drawMenu(window, &player, *pFonts, effects, xOffset, yOffset, pInput, elapsedTime);
	} else {
		if (level != 0) {
			UI.drawMenu(window, &player, *pFonts, effectGroup, xOffset, yOffset, pInput, elapsedTime);
			// Pass the player's health to the font controller
			pFonts->updateHealth(player.getHealth());
			// Draw all of the game text to the window
			pFonts->print(window);
		}
	}
	// Update the screen shake controller
	ssc.update(player);
	
	window.setView(worldView);
	
	if (dispEntryBeam) {
		// Cast the beam's glow to the overworld
		glowSprs1.push_back(&beamGlowSpr);
		glowSprs2.push_back(&beamGlowSpr);

		// Get the current size of the beam shape
		sf::Vector2f v2 = entryBeam.getSize();
		// Keep track of the original size of the beam, makes it easier later to update the shape position
		double originalYval = v2.y;
		// Until the beam reaches the player position at the center of the window, increase it's height and move it down. Purely an aesthetic thing
		if (v2.y < 518) {
			v2.y *= 1.11;
			sf::Color c = beamGlowSpr.getColor();
			c.r += 5;
			c.b += 5;
			c.g += 5;
			beamGlowSpr.setColor(c);
		} else if (v2.y > 518) {
			player.visible = true;
			// Call a function within the screen shake controller to shake the screen
			ssc.shake();
			v2.y = 518;
			// Add a warp smoke effect when the player appears, purely aesthetic
			/// TODO: effects.addWarpEffect(windowW / 2 - 8, windowH / 2 + 16);
			// Add a warp impack detail to the overworld where the player landed
			/// TODO: details.addWarpImpact(windowW / 2 - 12, windowH / 2 + 18);
		} else {
			player.setState(Player::State::deactivated);
		}
		// Get the current color of the beam shape, in order to decrement its alpha value
		sf::Color c1 = entryBeam.getFillColor();
		// Decrement the alpha value of the beam shape
		if (v2.y == 518) {
			c1.a *= 0.88;
			sf::Color c = beamGlowSpr.getColor();
			c.r -= 8;
			c.b -= 8;
			c.g -= 8;
			beamGlowSpr.setColor(c);
		}
		// Update the shape color
		entryBeam.setFillColor(c1);
		// Update the size of the beam shape
		entryBeam.setSize(v2);
		// Reset the shape's position based on the distance that the player has moved and the beam's previous position
		entryBeam.setPosition(entryBeam.getPosition().x, entryBeam.getPosition().y + 0.5 * (originalYval - v2.y));
		// Draw the shape to the window
		window.draw(entryBeam);
		
		if (c1.a < 6) {
			// Beam has faded out, so now stop drawing it
			dispEntryBeam = false;
			beamGlowSpr.setColor(sf::Color(0, 0, 0, 255));
			// Reset the initial values for the shape so that the program can draw it again next level
			sf::Vector2f v2(4, 8);
			entryBeam.setPosition(windowW/2 - 2, -68);
			entryBeam.setSize(v2);
			entryBeam.setFillColor(sf::Color(104, 255, 229, 180));
			// Reactivate the player now that the beam animation has finished
			player.setState(Player::State::nominal);
		}
	}
	
	if (transitionIn) {
		sf::Color c = transitionShape.getFillColor();
		if (c.a > 10) {
			c.a -= 10;
		}
		transitionShape.setFillColor(c);
		window.draw(transitionShape);

		if (--transitionDelay == 0) {
			transitionIn = false;
			dispEntryBeam = true;
			// Allow the teleporter animation to play again
			animationBegin = false;
			transitionDelay = 65;
		}
	}
	
	// Check if the player is close to a teleporter. If so, go to the next level
	if ((std::abs(player.getXpos() - details.getTeleporter()->getXpos()) < 10 && std::abs(player.getYpos() - details.getTeleporter()->getYpos() + 12) < 8) /*&& player.isActive()*/) {
		// Center the player over the teleporter for the duration of the teleport animation (ie center the world under the player)
		if (!animationBegin) {
			player.setWorldOffsetX(xOffset + (player.getXpos() - details.getTeleporter()->getXpos()) + 2);
			player.setWorldOffsetY(yOffset + (player.getYpos() - details.getTeleporter()->getYpos()) + 16);
			beamExpanding = true;
			animationBegin = true;
		}
		player.setState(Player::State::deactivated);
		// Cast the beam's glow to the overworld
		if (!transitioning) {
			window.draw(teleporterBeam);
			glowSprs1.push_back(&beamGlowSpr);
			glowSprs2.push_back(&beamGlowSpr);
		}
		sf::Color beamColor = teleporterBeam.getFillColor();
		sf::Vector2f v1 = teleporterBeam.getSize();
		if (beamExpanding) {
			if (beamColor.a < 246) {
				beamColor.a += 5;
			}
			sf::Color c = beamGlowSpr.getColor();
			c.r += 4;
			c.b += 4;
			c.g += 4;
			beamGlowSpr.setColor(c);
			teleporterBeam.setFillColor(beamColor);
			if (v1.y < 300) {
				v1.y += 8;
				teleporterBeam.setPosition(teleporterBeam.getPosition().x, teleporterBeam.getPosition().y - 8);
			}
			
			if (v1.y > 260 && v1.x < 22) {
				double temp = v1.x;
				v1.x *= 1.18;
				teleporterBeam.setPosition(teleporterBeam.getPosition().x - (v1.x - temp) * 0.5, teleporterBeam.getPosition().y);
			} else if (v1.x > 21) {
				beamExpanding = false;
				player.visible = false;
			}
			teleporterBeam.setSize(v1);
		} else if (!beamExpanding) {
			double temp = v1.x;
			v1.x *= 0.92;
			beamColor.a -= 1.4;
			sf::Color c = beamGlowSpr.getColor();
			if (c.r > 6) {
				c.r -= 6;
				c.b -= 6;
				c.g -= 6;
			}
			beamGlowSpr.setColor(c);
			teleporterBeam.setFillColor(beamColor);
			teleporterBeam.setPosition(teleporterBeam.getPosition().x - (v1.x - temp) * 0.5, teleporterBeam.getPosition().y);
			teleporterBeam.setSize(v1);
			if (v1.x < 0.5) {
				transitioning = true;
				//teleporterCond = true;
				beamGlowSpr.setColor(sf::Color(0, 0, 0, 255));
				
			}
		}

		pFonts->update(window, xOffset, yOffset);
		window.setView(worldView);
		
		if (transitioning) {
			if (level == 0) {
				if (transitionDelay < 130) {
					sf::Color c = pFonts->getTitle()->getColor();
					if (c.a > 4) {
						c.a -= 4;
					} else {
						c.a = 0;
					}
					if (transitionDelay < 90) {
						sf::Color c2 = transitionShape.getFillColor();
						if (c2.a < 253) {
							c2.a += 3;
						}
						transitionShape.setFillColor(c2);
						window.draw(transitionShape);
					}
					pFonts->drawTitle(c.a, window);
				} else {
					pFonts->drawTitle(255, window);
				}
				
				if (--transitionDelay == 0) {
					transitioning = false;
					transitionDelay = 55;
					teleporterCond = true;
					titleSpr.setColor(sf::Color(255, 255, 255, 255));
				}
			} else {
				if (transitionDelay < 50) {
					sf::Color c = transitionShape.getFillColor();
					if (c.a < 250) {
						c.a += 5;
					}
					transitionShape.setFillColor(c);
					window.draw(transitionShape);
				}
				if (--transitionDelay == 0) {
					transitioning = false;
					transitionDelay = 30;
					teleporterCond = true;
					//transitionShape.setFillColor(sf::Color(255, 255, 255, 255));
				}
			}
		}
	}
}

void Scene::Reset() {
	level += 1;
	pFonts->setWaypointText(level);
	//Clear all the vectors before re-initializing them, we don't want objects from the previous map showing up again
	tiles.clear();
	effectGroup.clear();
	details.clear();
	player.setWorldOffsetX(0);
	player.setWorldOffsetY(0);
	en.clear();
	teleporterCond = 0;
	int count;
	
	set = tileController::Tileset::intro;
	
	if (level == 0) {
		set = tileController::Tileset::intro;
		objectShadeColor = sf::Color(190, 190, 210, 255);
	} else {
		if (rand() % 2) {
			set = tileController::Tileset::nova;
			objectShadeColor = sf::Color(210, 195, 195, 255);
		} else {
			set = tileController::Tileset::regular;
			objectShadeColor = sf::Color(190, 190, 210, 255);
		}
	}
	
	vignetteSprite.setColor(sf::Color(255, 255, 255, 255));
	
	if (set != tileController::Tileset::intro) {
		//Now call the mapping function again to generate a new map, and make sure it's large enough
		count = mappingFunction(tiles.mapArray, level, set != tileController::Tileset::nova);
			while (count < 150) {
			count = mappingFunction(tiles.mapArray, level, set != tileController::Tileset::nova);
		}
	} else if (level == 0) {
	
	}
	
	//Now lets rebuild the map from the new array, using the same function from the tileController class constructor
	tiles.rebuild(itemArray, set);
	// Now let the background handler know what tileset the tilecontroller is using
	bkg.setBkg(tiles.getWorkingSet());
	/*Of course, the tile controller needs to know how big the window is so that it can find the center when drawing the tiles (tiles outside the window don't draw, and the player object is in the center of the window--we don't want to draw it inside a wall!)
	*/
	tiles.setPosition((windowW / 2) - 16, (windowH / 2));
	bkg.setPosition((tiles.posX / 2) + 206, tiles.posY / 2);

	if (level != 0) {
		details.addTeleporter(tiles, tiles.posX, tiles.posY, windowW, windowH);
		
		initEnemies(this);
				
		// Place a weapon chest is needed
		if (itemArray[level][0] != 0) {
			details.addChest(tiles, tiles.posX, tiles.posY, windowW, windowH, itemArray[level][0]);
		}
		// place life capsule chests
		if (itemArray[level][1] == 90) {
			details.addChest(tiles, tiles.posX, tiles.posY, windowW, windowH, itemArray[level][1]);
		}
		
		glowSprs1.clear();
		glowSprs2.clear();
		
		size_t len;
		Teleporter* pTeleporter = details.getTeleporter();
		if (set == tileController::Tileset::regular) {
			// Put rock/pillar detail things on map
			getRockPositions(tiles.mapArray, rockPositions);
			for (auto element : rockPositions) {
				details.addRock(tiles.posX, tiles.posY - 35, element.x, element.y);
			}
			rockPositions.clear();
			// Delete rocks close to the teleporter
			std::vector<Rock>* pRocks = details.getRocks();
			for (auto it = pRocks->begin(); it != pRocks->end();) {
				if (fabsf(it->getXpos() - pTeleporter->getXpos()) < 80 && fabsf(it->getYpos() - pTeleporter->getYpos()) < 80) {
					it = pRocks->erase(it);
				} else {
					++it;
				}
			}
		}
		
		// Put light sources on the map
		getLightingPositions(tiles.mapArray, lightPositions);
		len = lightPositions.size();
		for (size_t i = 0; i < len; i++) {
			details.addLamplight(tiles.posX - 2, tiles.posY - 16, lightPositions[i].x, lightPositions[i].y, windowW, windowH);
		}
		lightPositions.clear();
		
		// Delete lamps near the teleporter (light blending is additive, it would be too bright if they were close together)
		// std::vector<LampLight> * pLamps = details.getLamps();
		// for (size_t i = 0; i < details.getLamps()->size(); i++) {
		// 	if (fabsf((*pLamps)[i].getXpos() - pTeleporter->getXpos()) < 90 && fabsf((*pLamps)[i].getYpos() - pTeleporter->getYpos()) < 90) {
		// 		(*pLamps)[i] = (*pLamps).back();
		// 		(*pLamps).pop_back();
		// 	}
		// }
	} else if (set == tileController::Tileset::intro) {
		details.addLamplight(tiles.posX - 180, tiles.posY + 200, 5, 6, windowW, windowH);
		details.addLamplight(tiles.posX - 180, tiles.posY + 200, 5, 0, windowW, windowH);
		details.addLamplight(tiles.posX - 170, tiles.posY + 200, 11, 11, windowW, windowH);
		details.addLamplight(tiles.posX - 180, tiles.posY + 200, 10, -9, windowW, windowH);
		details.addDoor(tiles.posX - 192, tiles.posY + 301, 6, 0, windowW, windowH);
		details.addPod(tiles.posX, tiles.posY + 33, 3, 17);
		tiles.teleporterLocation.x = 8;
		tiles.teleporterLocation.y = -7;
		details.addTeleporter(tiles, tiles.posX - 178, tiles.posY + 284, windowW, windowH);
		for (auto it = global_levelZeroWalls.begin(); it != global_levelZeroWalls.end(); ++it) {
			wall w;
			w.setXinit(it->first);
			w.setYinit(it->second);
			tiles.walls.push_back(w);
		}
	}
	
	// Reset the teleporter beam coordinates, alpha, & size
	sf::Vector2f v1(2, 1);
	teleporterBeam.setPosition(windowW/2 - 1, windowH/2 + 36);
	teleporterBeam.setSize(v1);
	teleporterBeam.setFillColor(sf::Color(104, 255, 229, 6));
	if (level != 0)
		transitionIn = true;
}

detailController & Scene::getDetails() {
	return details;
}

enemyController & Scene::getEnemyController() {
	return en;
}

tileController & Scene::getTileController() {
	return tiles;
}

Player & Scene::getPlayer() {
	return player;
}

EffectGroup & Scene::getEffects() {
	return effectGroup;
}

InputController * Scene::getPInput() {
	return pInput;
}

ScreenShakeController * Scene::getPSSC() {
	return &ssc;
}

userInterface & Scene::getUI() {
	return UI;
}

FontController * Scene::getPFonts() {
	return pFonts;
}

bool Scene::getTeleporterCond() {
	return teleporterCond;
}

std::vector<std::pair<int, int>>* Scene::getEnemySelectVec() {
	return &enemySelectVec;
}

int Scene::getLevel() {
	return level;
}


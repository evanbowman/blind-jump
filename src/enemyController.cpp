//
//  enemyController.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/18/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "enemyController.hpp"
#include "ResourcePath.hpp"
#include <cmath>
#include "wall.hpp"
#include "tileController.hpp"
#include "detailController.hpp"
#include "screenShakeController.hpp"


enemyController::enemyController() {
	//Load all of the textures to apply to the enemies
	const std::string turretfileExt[10] = {"turret5.png", "turret4.png", "turret3.png", "turret2.png", "turret1.png", "turretShadow5.png", "turretShadow4.png", "turretShadow3.png", "turretShadow2.png", "turretShadow1.png"};
	for (int i = 0; i < 10; i++) {
		turretTextures[i].loadFromFile(resourcePath() + turretfileExt[i]);
		turretSprites[i].setTexture(turretTextures[i]);
	}
	
	for (auto i = 0; i < 6; i++) {
		dasherTexture[i].loadFromFile(resourcePath() + "dasherSheet.png", sf::IntRect(i * 29, 0, 29, 38));
		dasherSprite[i].setTexture(dasherTexture[i]);
	}
	
	for (auto i = 0; i < 15; i++) {
		dasherDeathSeq[i].loadFromFile(resourcePath() + "dasherDeathSeq.png", sf::IntRect(i * 47, 0, 47, 38));
		dasherSprite[i + 6].setTexture(dasherDeathSeq[i]);
	}
	
	for (auto i = 0; i < 4; i++) {
		chaserTextures[i].loadFromFile(resourcePath() + "critterSheet.png", sf::IntRect(i * 18, 0, 18, 18));
		chaserSprites[i].setTexture(chaserTextures[i]);
	}
}

void enemyController::linkTextures(TextureManager * pTM) {
	this->pTM = pTM;
}

//A function to draw the enemies' current sprites to the screen
void enemyController::updateEnemies(std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>& gameObjects, std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>& gameShadows, float x, float y, effectsController& ef, std::vector<wall> w, bool enabled, detailController* dets, tileController* pTiles, ScreenShakeController* scrn, FontController& fonts, sf::Time & elapsedTime) {
	if (!turrets.empty()) {
		for (std::vector<turret>::iterator it = turrets.begin(); it != turrets.end();) {
			if (it->getKillFlag() == 1) {
				// Add some scrap to the map
				dets->addEnemyScrap(it->getXinit() + 4, it->getYinit() + 6, 0, 0);
				// Rumble the screen
				scrn->rumble();
				it = turrets.erase(it);
			}
			else {
				++it;
			}
		}
		
		for (auto & element : turrets) {									   //Use iterators to step through the vector
			element.setPosition(x + element.getXinit(), y + element.getYinit());		 //Update the enemies' position, x and y are offsets
			if (element.getXpos() > -64 && element.getXpos() < windowW + 64 && element.getYpos() > -64 && element.getYpos() < windowH + 64) {
				// Get the enemy's shadow
				std::tuple<sf::Sprite, float, Rendertype, float> shadow;
				std::get<0>(shadow) = *element.getShadow();
				gameShadows.push_back(shadow);

				std::tuple<sf::Sprite, float, Rendertype, float> tSpr;
				std::get<0>(tSpr) = *element.getSprite(elapsedTime);
				std::get<1>(tSpr) = element.getYpos();
				
				if (element.colored()) {
					std::get<2>(tSpr) = Rendertype::shadeWhite;
				} else {
					std::get<2>(tSpr) = Rendertype::shadeDefault;
				}
				
				gameObjects.push_back(tSpr);
				
				if (enabled) {
					element.updateShots(ef, fonts);								//If the turrets are ready to shoot, pass them the effects controller so to store the effects in
				}
			}
		}
	}
	
	if (!scoots.empty()) {
		for (std::vector<Scoot>::iterator it = scoots.begin(); it != scoots.end();) {
			if (it->getKillFlag()) {
				// Add some scrap to the map
				dets->addEnemyScrap(it->getXinit(), it->getYinit(), 0, 0);
				// Rumble the screen
				scrn->rumble();
				it = scoots.erase(it);
			}
			
			else {
				if (it->getXpos() > -64 && it->getXpos() < windowW + 64 && it->getYpos() > -64 && it->getYpos() < windowH + 64) {
					if (enabled) {
						it->update(x, y, w, ef, elapsedTime);
					}
					gameShadows.emplace_back(it->getShadow(), 0.f, Rendertype::shadeDefault, 0.f);
				    if (it->isColored()) {
						gameObjects.emplace_back(it->getSprite(), it->getYpos() - 16, Rendertype::shadeWhite, it->getColorAmount());
					} else {
						gameObjects.emplace_back(it->getSprite(), it->getYpos() - 16, Rendertype::shadeDefault, 0.f);
					}
				}
				
				else {
					// If outside the window, update the enemy's position, but don't move it, draw it, check collisions, etc.
					it->Enemy::update(x, y, w, ef, elapsedTime);
				}
				
				++it;
			}
		}
	}
	
	if (!critters.empty()) {
		// Need to check if each enemy overlaps with any other enemies so that they don't bunch up
		for (size_t i = 0; i < critters.size(); i++) {
			for (size_t j = 0; j < critters.size(); j++) {
				// Obviously it would be bad to compare an object to itself.
				if (i != j) {
					// If the enemy at index i is active and overlaps with another enemy that is also active...
					if (fabs(critters[i].getXpos() - critters[j].getXpos()) < 12 && fabs(critters[i].getYpos() - critters[j].getYpos()) < 12 && critters[i].isActive() && critters[j].isActive()) {
						critters[i].deActivate();
					}
				}
			}
		}
		
		for (std::vector<Critter>::iterator it = critters.begin(); it != critters.end();) {
			if (it->getKillFlag()) {
				// Rumble the screen
				scrn->rumble();
				it = critters.erase(it);
			}
			
			else {
				//if (it->getXpos() > -64 && it->getXpos() < windowW + 64 && it->getYpos() > -64 && it->getYpos() < windowH + 64) {
					if (enabled) {
						it->update(x, y, ef, pTiles, elapsedTime);
					} else {
						it->updatePlayerDead();
					}
					// Get the enemy's shadow
					std::tuple<sf::Sprite, float, Rendertype, float> shadow;
					std::get<0>(shadow) = *it->getShadow();
					gameShadows.push_back(shadow);
					
					std::tuple<sf::Sprite, float, Rendertype, float> tSpr;
					std::get<0>(tSpr) = *it->getSprite();
					std::get<1>(tSpr) = it->getYpos() - 16;
					// If the enemy should be colored, let the rendering code know to pass it through a fragment shader
					if (it->colored()) {
						std::get<2>(tSpr) = Rendertype::shadeWhite;
						std::get<3>(tSpr) = it->colorAmount;
					} else {
						std::get<2>(tSpr) = Rendertype::shadeDefault;
					}
					
					gameObjects.push_back(tSpr);
				
				++it;
			}
		}
		// Now we have to reactivate all of the objects. Perhaps there is a smarter way than this brute force approach...
		for (auto & element : critters) {
			element.activate();
		}
	}
	
	if (!dashers.empty()) {
		for (std::vector<Dasher>::iterator it = dashers.begin(); it != dashers.end();) {
			if (it->scrapReady()) {
				// Add some scrap to the map
				dets->addDasherScrap(it->getXinit() + 14, it->getYinit() + 15, it->getSprite()->getScale().x);
			}
			
			if (it->shakeReady()) {
				scrn->rumble();
			}
			
			if (it->getKillFlag()) {
				it = dashers.erase(it);
			}
			
			else {
				if (it->getXpos() > -64 && it->getXpos() < windowW + 64 && it->getYpos() > -64 && it->getYpos() < windowH + 64) {
					if (enabled) {
						it->update(x, y, w, ef, elapsedTime);
					}
					// Get the enemy's shadow
					if (!it->dying()) {
						std::tuple<sf::Sprite, float, Rendertype, float> shadow;
						std::get<0>(shadow) = *it->getShadow();
						gameShadows.push_back(shadow);
					}
					
					for (auto & element2 : *it->getBlurEffects()) {
						std::tuple<sf::Sprite, float, Rendertype, float> t;
						std::get<0>(t) = *element2.getSprite();
						std::get<1>(t) = element2.yInit + y;
						std::get<2>(t) = Rendertype::shadeDefault;
						gameObjects.push_back(t);
					}
					
					std::tuple<sf::Sprite, float, Rendertype, float> tSpr;
					std::get<0>(tSpr) = *it->getSprite();
					std::get<1>(tSpr) = it->getYpos();
					
					if (it->colored()) {
						std::get<2>(tSpr) = Rendertype::shadeWhite;
						std::get<3>(tSpr) = it->colorAmount;
					} else {
						std::get<2>(tSpr) = Rendertype::shadeDefault;
					}
					
					gameObjects.push_back(tSpr);
				}
				
				else {
					// If outside the window, update the enemy's position, but don't move it, draw it, check collisions, etc.
					it->softUpdate(x, y);
				}
				++it;
			}
		}
	}
}

void enemyController::clear() {
	turrets.clear();				//For world re-initialization, clear out the vector and start fresh
	scoots.clear();
	dashers.clear();
	critters.clear();
}

sf::Sprite* enemyController::getTurretSprites() {
	return turretSprites;
}

sf::Sprite* enemyController::getChaserSprites() {
	return chaserSprites;
}

sf::Sprite* enemyController::getGuardianSprites() {
	return droneSprites;
}

sf::Sprite* enemyController::getDasherSprites() {
	return dasherSprite;
}

void enemyController::addTurret(turret t) {
	turrets.push_back(t);
}

void enemyController::addScoot(tileController * pTiles) {
	auto pCoordVec = pTiles->getEmptyLocations();
	const int locationSelect = (rand() % 2) ? rand() % (pCoordVec->size() / 2) : rand() & (pCoordVec->size());
	float xInit = (*pCoordVec)[locationSelect].x * 32 + pTiles->getPosX();
	float yInit = (*pCoordVec)[locationSelect].y * 26 + pTiles->getPosY();
	scoots.emplace_back(pTM->getTexture(TextureManager::Texture::scoot), pTM->getTexture(TextureManager::Texture::scootShadow), xInit, yInit, windowW, windowH);
}

void enemyController::addDasher(Dasher d) {
	dashers.push_back(d);
}

void enemyController::addCritter(Critter c) {
	critters.push_back(c);
}

void enemyController::setWindowSize(float windowW, float windowH) {
	this->windowW = windowW;
	this->windowH = windowH;
}


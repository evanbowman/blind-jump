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


enemyController::enemyController(TextureManager * _pTM)
	: pTM{_pTM}
{
	//Load all of the textures to apply to the enemies
	const std::string turretfileExt[10] = {"turret5.png", "turret4.png", "turret3.png", "turret2.png", "turret1.png", "turretShadow5.png", "turretShadow4.png", "turretShadow3.png", "turretShadow2.png", "turretShadow1.png"};
	for (int i = 0; i < 10; i++) {
		turretTextures[i].loadFromFile(resourcePath() + turretfileExt[i]);
		turretSprites[i].setTexture(turretTextures[i]);
	}
}

void enemyController::updateEnemies(drawableVec & gameObjects, drawableVec & gameShadows, float x, float y, effectsController& ef, std::vector<wall> w, bool enabled, detailController* dets, tileController* pTiles, ScreenShakeController* scrn, FontController& fonts, sf::Time & elapsedTime) {
	if (!turrets.empty()) {
		for (auto it = turrets.begin(); it != turrets.end();) {
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
		
		for (auto & element : turrets) {
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
		for (auto it = scoots.begin(); it != scoots.end();) {
			if (it->getKillFlag()) {
				// Add some scrap to the map
				dets->addEnemyScrap(it->getXinit(), it->getYinit(), 0, 0);
				// Rumble the screen
				scrn->rumble();
				it = scoots.erase(it);
			} else {
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
		
		for (auto it = critters.begin(); it != critters.end();) {
			if (it->getKillFlag()) {
				// Rumble the screen
				scrn->rumble();
				it = critters.erase(it);
			}
			
			else {
				//if (it->getXpos() > -64 && it->getXpos() < windowW + 64 && it->getYpos() > -64 && it->getYpos() < windowH + 64) {
					if (enabled) {
						it->update(x, y, w, ef, elapsedTime);
					} else {
						it->Enemy::update(x, y, w, ef, elapsedTime);
					}
					// Get the enemy's shadow
					std::tuple<sf::Sprite, float, Rendertype, float> shadow;
					std::get<0>(shadow) = it->getShadow();
					gameShadows.push_back(shadow);
					
					std::tuple<sf::Sprite, float, Rendertype, float> tSpr;
					std::get<0>(tSpr) = it->getSprite();
					std::get<1>(tSpr) = it->getYpos() - 16;
					// If the enemy should be colored, let the rendering code know to pass it through a fragment shader
					if (it->isColored()) {
						std::get<2>(tSpr) = Rendertype::shadeWhite;
						std::get<3>(tSpr) = it->getColorAmount();
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
		for (auto & element : dashers) {
			if (element.getXpos() > -64 && element.getXpos() < windowW + 64 && element.getYpos() > -64 && element.getYpos() < windowH + 64) {
				if (enabled)
					element.update(x, y, w, ef, elapsedTime);	
					
				auto state = element.getState();
				if (state != Dasher::State::dying && state != Dasher::State::dead)
					gameShadows.emplace_back(element.getShadow(), 0.f, Rendertype::shadeDefault, 0.f);
					
				for (auto & blur : *element.getBlurEffects())
					gameObjects.emplace_back(*blur.getSprite(), blur.yInit + y, Rendertype::shadeDefault, 0.f);
					
				if (element.isColored())
					gameObjects.emplace_back(element.getSprite(), element.getYpos(), Rendertype::shadeWhite, element.getColorAmount());
				else
					gameObjects.emplace_back(element.getSprite(), element.getYpos(), Rendertype::shadeDefault, 0.f);
					
			} else {
				// If outside the window, update the enemy's position, but don't move it, draw it, check collisions, etc.
				element.Enemy::update(x, y, w, ef, elapsedTime);
			}
		}
	}
}

void enemyController::clear() {
	turrets.clear();
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

void enemyController::addTurret(turret t) {
	turrets.push_back(t);
}

void enemyController::addScoot(tileController * pTiles) {
	auto pCoordVec = pTiles->getEmptyLocations();
	int locationSelect = (rand() % 2) ? rand() % (pCoordVec->size() / 2) : rand() % (pCoordVec->size());
	float xInit = (*pCoordVec)[locationSelect].x * 32 + pTiles->getPosX();
	float yInit = (*pCoordVec)[locationSelect].y * 26 + pTiles->getPosY();
	scoots.emplace_back(pTM->getTexture(TextureManager::Texture::gameObjects),
						pTM->getTexture(TextureManager::Texture::scootShadow),
						xInit, yInit, windowW / 2, windowH / 2);
	(*pCoordVec)[locationSelect] = pCoordVec->back();
	pCoordVec->pop_back();
}

void enemyController::addDasher(tileController * pTiles) {
	auto pCoordVec = pTiles->getEmptyLocations();
	int locationSelect = (rand() % 2) ? rand() % (pCoordVec->size() / 3) : rand() % (pCoordVec->size() / 2);
	float xInit = (*pCoordVec)[locationSelect].x * 32 + pTiles->getPosX();
	float yInit = (*pCoordVec)[locationSelect].y * 26 + pTiles->getPosY();
	dashers.emplace_back(pTM->getTexture(TextureManager::Texture::gameObjects),
						 xInit, yInit, windowW / 2, windowH / 2);
	(*pCoordVec)[locationSelect] = pCoordVec->back();
	pCoordVec->pop_back();
}

void enemyController::addCritter(tileController * pTiles) {
	auto pCoordVec = pTiles->getEmptyLocations();
	int locationSelect = rand() % pCoordVec->size();
	float xInit = (*pCoordVec)[locationSelect].x * 32 + pTiles->getPosX();
	float yInit = (*pCoordVec)[locationSelect].y * 26 + pTiles->getPosY();
	critters.emplace_back(pTM->getTexture(TextureManager::Texture::gameObjects),
						  pTiles->mapArray, xInit, yInit,
						  windowW / 2, windowH / 2, pTiles->posX, pTiles->posY);
	(*pCoordVec)[locationSelect] = pCoordVec->back();
	pCoordVec->pop_back();
}

void enemyController::setWindowSize(float windowW, float windowH) {
	this->windowW = windowW;
	this->windowH = windowH;
}


//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
//                                                                        //
// This program is free software: you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or      //
// (at your option) any later version.                                    //
//                                                                        //
// This program is distributed in the hope that it will be useful,        //
// but WITHOUT ANY WARRANTY; without even the implied warranty of         //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
// GNU General Public License for more details.                           //
//                                                                        //
// You should have received a copy of the GNU General Public License      //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
//========================================================================//

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
}

void enemyController::draw(drawableVec & gameObjects, drawableVec & gameShadows) {
	for (auto & element : turrets) {
		if (element.getXpos() > -64 && element.getXpos() < windowW + 64 && element.getYpos() > -64 && element.getYpos() < windowH + 64) {
			// Get the enemy's shadow
			std::tuple<sf::Sprite, float, Rendertype, float> shadow;
			std::get<0>(shadow) = element.getShadow();
			gameShadows.push_back(shadow);
			std::tuple<sf::Sprite, float, Rendertype, float> tSpr;
			std::get<0>(tSpr) = element.getSprite();
			std::get<1>(tSpr) = element.getYpos();
			if (element.colored()) {
				std::get<2>(tSpr) = Rendertype::shadeWhite;
			} else {
				std::get<2>(tSpr) = Rendertype::shadeDefault;
			}
			gameObjects.push_back(tSpr);
		}
	}

	for (auto & element : critters) {
		gameShadows.emplace_back(element.getShadow(), 0.f, Rendertype::shadeDefault, 0.f);
		std::tuple<sf::Sprite, float, Rendertype, float> tSpr;
		std::get<0>(tSpr) = element.getSprite();
		std::get<1>(tSpr) = element.getYpos() - 16;
		// If the enemy should be colored, let the rendering code know to pass it through a fragment shader
		if (element.isColored()) {
			gameObjects.emplace_back(element.getSprite(), element.getYpos() - 16, Rendertype::shadeWhite, element.getColorAmount());
		} else {
			gameObjects.emplace_back(element.getSprite(), element.getYpos() - 16, Rendertype::shadeDefault, 0.f);
		}		
	}
	
	for (auto & element : scoots) {
		if (element.getXpos() > -64 && element.getXpos() < windowW + 64 && element.getYpos() > -64 && element.getYpos() < windowH + 64) {
			gameShadows.emplace_back(element.getShadow(), 0.f, Rendertype::shadeDefault, 0.f);
			if (element.isColored()) {
				gameObjects.emplace_back(element.getSprite(), element.getYpos() - 16, Rendertype::shadeWhite, element.getColorAmount());
			} else {
				gameObjects.emplace_back(element.getSprite(), element.getYpos() - 16, Rendertype::shadeDefault, 0.f);
			}
		}
	}
	
	for (auto & element : dashers) {
		if (element.getXpos() > -64 && element.getXpos() < windowW + 64 && element.getYpos() > -64 && element.getYpos() < windowH + 64) {
			auto state = element.getState();
			if (state != Dasher::State::dying && state != Dasher::State::dead) {
				gameShadows.emplace_back(element.getShadow(), 0.f, Rendertype::shadeDefault, 0.f);
			}		
			for (auto & blur : *element.getBlurEffects()) {
				gameObjects.emplace_back(*blur.getSprite(), blur.yInit + 200, Rendertype::shadeDefault, 0.f);
			}			
			if (element.isColored()) {
				gameObjects.emplace_back(element.getSprite(), element.getYpos(), Rendertype::shadeWhite, element.getColorAmount());
			} else {
				gameObjects.emplace_back(element.getSprite(), element.getYpos(), Rendertype::shadeDefault, 0.f);
			}
		}
	}
}

void enemyController::update(float x, float y, EffectGroup & ef, std::vector<wall> w, bool enabled, tileController* pTiles, ScreenShakeController* scrn, FontController& fonts, sf::Time & elapsedTime) {
	if (!turrets.empty()) {
		for (auto it = turrets.begin(); it != turrets.end();) {
			if (it->getKillFlag() == 1) {
				scrn->rumble();
				it = turrets.erase(it);
			} else {
				it->setPosition(x + it->getXinit(), y + it->getYinit());
				it->update(elapsedTime);
				if (enabled) {
					it->updateShots(ef, fonts);
				}
				++it;
			}
		}
	}
	
	if (!scoots.empty()) {
		for (auto it = scoots.begin(); it != scoots.end();) {
			if (it->getKillFlag()) {
				scrn->rumble();
				it = scoots.erase(it);
			} else {
				if (it->getXpos() > -64 && it->getXpos() < windowW + 64 && it->getYpos() > -64 && it->getYpos() < windowH + 64) {
					if (enabled) {
						it->update(x, y, w, ef, elapsedTime);
					}
				} else {
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
			} else {
				if (enabled) {
					it->critterUpdate(x, y, ef, elapsedTime, pTiles);
				} else {
					it->Enemy::update(x, y, w, ef, elapsedTime);
				}
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
				if (enabled) {
					element.update(x, y, w, ef, elapsedTime);	
				}	
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

sf::Sprite * enemyController::getTurretSprites() {
	return turretSprites;
}

void enemyController::addTurret(tileController * pTiles) {
	auto pCoordVec = pTiles->getEmptyLocations();
	int locationSelect = (std::abs(static_cast<int>(globalRNG())) % 2) ? std::abs(static_cast<int>(globalRNG())) % (pCoordVec->size() / 2) : std::abs(static_cast<int>(globalRNG())) % (pCoordVec->size());
	float xInit = (*pCoordVec)[locationSelect].x * 32 + pTiles->getPosX();
	float yInit = (*pCoordVec)[locationSelect].y * 26 + pTiles->getPosY();
	turrets.emplace_back(globalResourceHandler.getTexture(ResourceHandler::Texture::gameObjects), xInit, yInit, windowW / 2, windowH / 2);
	(*pCoordVec)[locationSelect] = pCoordVec->back();
	pCoordVec->pop_back();
}

void enemyController::addScoot(tileController * pTiles) {
	auto pCoordVec = pTiles->getEmptyLocations();
	int locationSelect = (std::abs(static_cast<int>(globalRNG())) % 2) ? std::abs(static_cast<int>(globalRNG())) % (pCoordVec->size() / 2) : std::abs(static_cast<int>(globalRNG())) % (pCoordVec->size());
	float xInit = (*pCoordVec)[locationSelect].x * 32 + pTiles->getPosX();
	float yInit = (*pCoordVec)[locationSelect].y * 26 + pTiles->getPosY();
	scoots.emplace_back(globalResourceHandler.getTexture(ResourceHandler::Texture::gameObjects),
						globalResourceHandler.getTexture(ResourceHandler::Texture::scootShadow),
						xInit, yInit, windowW / 2, windowH / 2);
	(*pCoordVec)[locationSelect] = pCoordVec->back();
	pCoordVec->pop_back();
}

void enemyController::addDasher(tileController * pTiles) {
	auto pCoordVec = pTiles->getEmptyLocations();
	int locationSelect = (std::abs(static_cast<int>(globalRNG())) % 2) ? std::abs(static_cast<int>(globalRNG())) % (pCoordVec->size() / 3) : std::abs(static_cast<int>(globalRNG())) % (pCoordVec->size() / 2);
	float xInit = (*pCoordVec)[locationSelect].x * 32 + pTiles->getPosX();
	float yInit = (*pCoordVec)[locationSelect].y * 26 + pTiles->getPosY();
	dashers.emplace_back(globalResourceHandler.getTexture(ResourceHandler::Texture::gameObjects),
						 xInit, yInit, windowW / 2, windowH / 2);
	(*pCoordVec)[locationSelect] = pCoordVec->back();
	pCoordVec->pop_back();
}

void enemyController::addCritter(tileController * pTiles) {
	auto pCoordVec = pTiles->getEmptyLocations();
	int locationSelect = std::abs(static_cast<int>(globalRNG())) % pCoordVec->size();
	float xInit = (*pCoordVec)[locationSelect].x * 32 + pTiles->getPosX();
	float yInit = (*pCoordVec)[locationSelect].y * 26 + pTiles->getPosY();
	critters.emplace_back(globalResourceHandler.getTexture(ResourceHandler::Texture::gameObjects),
						  pTiles->mapArray, xInit, yInit,
						  windowW / 2, windowH / 2);
	(*pCoordVec)[locationSelect] = pCoordVec->back();
	pCoordVec->pop_back();
}

void enemyController::setWindowSize(float windowW, float windowH) {
	this->windowW = windowW;
	this->windowH = windowH;
}

std::vector<Critter> & enemyController::getCritters() {
	return critters;
}

std::vector<Dasher> & enemyController::getDashers() {
	return dashers;
}

std::vector<Scoot> & enemyController::getScoots() {
	return scoots;
}

std::vector<Turret> & enemyController::getTurrets() {
	return turrets;
}

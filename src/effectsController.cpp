//
//  effectsController.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "effectsController.hpp"
#include "screenShakeController.hpp"

effectsController::effectsController(ResourceHandler * _pRH)
	: pRH{_pRH}
{}

template<typename T>
void updateVector(std::vector<T>& vec, float xOffset, float yOffset, sf::Time & elapsedTime) {
	if (!vec.empty()) {
		for (auto it = vec.begin(); it != vec.end();) {
			it->update(xOffset, yOffset, elapsedTime);
			if (it->getKillFlag()) {
				it = vec.erase(it);
			}
			else {
				++it;
			}
		}
	}
}

template<typename T>
void updateVectorGlow(std::vector<T>& vec, float xOffset, float yOffset, std::vector<sf::Sprite*>& glowSprs, sf::Time & elapsedTime) {
	if (!vec.empty()) {
		for (auto it = vec.begin(); it != vec.end();) {
			it->update(xOffset, yOffset, elapsedTime);
			glowSprs.push_back(it->getGlow());
			if (it->getKillFlag()) {
				it = vec.erase(it);
			}
			else {
				++it;
			}
		}
	}
}

void effectsController::update(float xOffset, float yOffset, ScreenShakeController* scrn, sf::Time & elapsedTime) {
	if (!bullets.empty()) {
		for (auto it = bullets.begin(); it != bullets.end();) {
			//If the duration has reached 0 or the object's kill flag is high
			if (it->getKillFlag()) {
				// Don't always want to add in additional effect where it could make the screen look cluttered, so check a condition first
				if (it->checkCanPoof()) {
					addPuff(it->getXpos() - xOffset, it->getYpos() - yOffset);
				}
				//Erase the bullet
				it = bullets.erase(it);
			}
			else {
				//Update the position
				it->update(xOffset, yOffset);
				glowSprs.push_back(it->getGlow());
				++it;
			}
		}
	}

	updateVector(turretFlashes, xOffset, yOffset, elapsedTime);
	updateVectorGlow(smallExplosions, xOffset, yOffset, glowSprs, elapsedTime);
	updateVectorGlow(hearts, xOffset, yOffset, glowSprs, elapsedTime);
	updateVectorGlow(turretShots, xOffset, yOffset, glowSprs, elapsedTime);
	updateVectorGlow(dasherShots, xOffset, yOffset, glowSprs, elapsedTime);
	updateVectorGlow(enemyShots, xOffset, yOffset, glowSprs, elapsedTime);
	updateVector(puffs, xOffset, yOffset, elapsedTime);
	updateVectorGlow(fireExplosions, xOffset, yOffset, glowSprs, elapsedTime);
	updateVector(warpEffects, xOffset, yOffset, elapsedTime);
	updateVectorGlow(coins, xOffset, yOffset, glowSprs, elapsedTime);
}

//A function for adding a turret flash animation
void effectsController::addTurretFlash(float x, float y) {
	turretFlashes.emplace_back(pRH->getTexture(ResourceHandler::Texture::gameObjects), x, y);
}

//A function for adding a turret shot effect
void effectsController::addTurretShot(float x, float y, short dir) {
	turretShots.emplace_back(pRH->getTexture(ResourceHandler::Texture::gameObjects), pRH->getTexture(ResourceHandler::Texture::redglow), x, y, dir);
}

void effectsController::addHearts(float x, float y) {
	Powerup h(pRH->getTexture(ResourceHandler::Texture::gameObjects), pRH->getTexture(ResourceHandler::Texture::redglow), x, y, Powerup::Type::heart);
	hearts.push_back(h);
}

void effectsController::addCoins(float x, float y) {
	Powerup c(pRH->getTexture(ResourceHandler::Texture::gameObjects), pRH->getTexture(ResourceHandler::Texture::blueglow), x, y, Powerup::Type::coin);
	coins.push_back(c);
}

void effectsController::addEnemyShot(float x, float y, short dir) {
	enemyShots.emplace_back(pRH->getTexture(ResourceHandler::Texture::gameObjects), pRH->getTexture(ResourceHandler::Texture::redglow), x, y, dir);
}

void effectsController::addDasherShot(float x, float y, short dir) {
	dasherShots.emplace_back(pRH->getTexture(ResourceHandler::Texture::gameObjects), pRH->getTexture(ResourceHandler::Texture::redglow), x, y, dir);
}

// A function for adding puffs
void effectsController::addPuff(float x, float y) {
	puffs.emplace_back(pRH->getTexture(ResourceHandler::Texture::gameObjects), x, y);
}

void effectsController::addFireExplosion(float x, float y) {
	fireExplosions.emplace_back(pRH->getTexture(ResourceHandler::Texture::gameObjects), pRH->getTexture(ResourceHandler::Texture::fireExplosionGlow), x, y);
}

void effectsController::addSmallExplosion(float x, float y) {
    smallExplosions.emplace_back(pRH->getTexture(ResourceHandler::Texture::gameObjects), pRH->getTexture(ResourceHandler::Texture::fireExplosionGlow), x, y);
}

void effectsController::addScootShot(float x, float y, short dir, float playerPosX, float playerPosY) {
	turretShot t(pRH->getTexture(ResourceHandler::Texture::gameObjects), pRH->getTexture(ResourceHandler::Texture::redglow), x, y, dir);
	t.speedFactor(2.8);
	turretShots.push_back(t);
}

//A function for adding a bullet
void effectsController::addBullet(bool select, char sprIndex, float xPos, float yPos) {
	bullets.emplace_back(pRH->getTexture(ResourceHandler::Texture::gameObjects), pRH->getTexture(ResourceHandler::Texture::whiteGlow), sprIndex, xPos, yPos);
}

void effectsController::addWarpEffect(float x, float y) {
	warpEffects.emplace_back(pRH->getTexture(ResourceHandler::Texture::gameObjects), x, y);
}

template <typename T>
void drawEffect(T& inpVec, std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>& gameObjects) {
	if (!inpVec.empty()) {
		for (auto & element : inpVec) {
			std::tuple<sf::Sprite, float, Rendertype, float> effectObject;
			std::get<0>(effectObject) = element.getSprite();
			std::get<1>(effectObject) = element.getYpos();
			std::get<2>(effectObject) = Rendertype::shadeNone;
			gameObjects.push_back(effectObject);
		}
	}
}

//Draw the sprites for all of the effect objects
void effectsController::draw(sf::RenderTexture& window, std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>& gameObjects) {
	drawEffect(hearts, gameObjects);
	drawEffect(coins, gameObjects);
	drawEffect(turretFlashes, gameObjects);
	drawEffect(bullets, gameObjects);
	drawEffect(puffs, gameObjects);
	drawEffect(turretShots, gameObjects);
	drawEffect(dasherShots, gameObjects);
	drawEffect(fireExplosions, gameObjects);
	drawEffect(smallExplosions, gameObjects);
	
	if (!warpEffects.empty()) {
		for (auto & element : warpEffects) {
			if (element.getDrawOrder() == 0) {
				window.draw(element.getSprite());
			}
		}
	}

	drawEffect(enemyShots, gameObjects);
}

void effectsController::drawLower(sf::RenderTexture& window) {
	if (!warpEffects.empty()) {
		for (auto & element : warpEffects) {
			if (element.getDrawOrder() == 1) {
				window.draw(element.getSprite());
			}
		}
	}
}

std::vector<sf::Sprite*>* effectsController::getGlowSprs() {
	return &glowSprs;
}

void effectsController::clear() {
	turretFlashes.clear();
	bullets.clear();
	puffs.clear();
	warpEffects.clear();
	enemyShots.clear();
	turretShots.clear();
	dasherShots.clear();
	smallExplosions.clear();
	fireExplosions.clear();
	hearts.clear();
	coins.clear();
}

std::vector<bulletType1>& effectsController::getBulletLayer1() {
	return bullets;
}

std::vector<turretShot>* effectsController::getTurretShots() {
	return &turretShots;
}

std::vector<Enemyshot>* effectsController::getEnemyShots() {
	return &enemyShots;
}

std::vector<DasherShot>* effectsController::getDasherShots() {
	return &dasherShots;
}

void effectsController::condClearGlowSpr(sf::Sprite * inpSpr) {
	glowSprs.clear();
	glowSprs.push_back(inpSpr);
}

std::vector<FireExplosion>* effectsController::getExplosions() {
	return &fireExplosions;
}

std::vector<sf::Sprite*>* effectsController::getGlowSprs2() {
	return &glowSprs2;
}

std::vector<Powerup>* effectsController::getHearts() {
	return &hearts;
}

std::vector<Powerup>* effectsController::getCoins() {
	return &coins;
}

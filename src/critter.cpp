//
//  chaser.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/26/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "critter.hpp"
#include "tileController.hpp"
#include "math.h"
#include <cmath>

Critter::Critter(const sf::Texture & txtr, short _map[61][61], float _xInit, float _yInit, float _playerPosX, float _playerPosY) :
	Enemy{_xInit, _yInit, _playerPosX, _playerPosY},
	currentDir{0.f},
	jumpTargetx{0.f},
	jumpTargety{0.f},
	spriteSheet{txtr},
	awake{false},
	active{true},
	recalc{4},
	map{_map}
{
	health = 3;
	spriteSheet.setOrigin(9, 9);
	shadow.setOrigin(9, 9);
	shadow.setTexture(txtr);
	shadow.setTextureRect(sf::IntRect(54, 57, 18, 18));
}

void Critter::updatePlayerDead() {
	frameIndex = 0;
}

void Critter::update(float, float, const std::vector<wall> &, effectsController &, const sf::Time &) {}

void Critter::critterUpdate(float xOffset, float yOffset, effectsController & effects, const sf::Time & elapsedTime, tileController * pTiles) {
	xPos = xInit + xOffset + 6;
	yPos = yInit + yOffset;
	Enemy::checkShotCollision(effects, 12.f);
	xPos -= 6; // Currently off-centered, this is just temporary work-around
	Enemy::updateColor(elapsedTime);

	float tilePosX = pTiles->posX;
	float tilePosY = pTiles->posY;
	
	if (awake) {
		float speed;
		if (active) {
			speed = 1.4;
		}
		
		else {
			speed= 0.7;
		}
		// If the enemy is finished following its path to the player
		if (path.empty() || recalc == 0) {
			recalc = 8;
			
			aStrCoordinate origin, target;
			origin.x = (xPos - tilePosX - xOffset) / 32;
			origin.y = (yPos - tilePosY - yOffset) / 26;
			target.x = (tilePosX - playerPosX + xOffset) / -32;
			target.y = (tilePosY - playerPosY - 26 + yOffset) / -26;
			if (map[target.x][target.y] == 3 || map[target.x][target.y] == 4 || map[target.x][target.y] == 5 || map[target.x][target.y] == 11 || map[target.x][target.y] == 8) {
				path = astar_path(target, origin, map);
				previous = path.back();
				path.pop_back();
				xInit = ((xPos - tilePosX - xOffset) / 32) * 32 + tilePosX;
				yInit = ((yPos - tilePosY - yOffset) / 26) * 26 + tilePosY;
				// Calculate the direction to move in, based on the coordinate of the previous location and the coordinate of the next location
				currentDir = atan2(yInit - (((path.back().y * 26) + 4 + tilePosY)), xInit - (((path.back().x * 32) + 4 + tilePosX)));
			}
		}
		
		// If the path is not empty
		else {
			// Add each component of the direction vector to the enemy's position datafields
			xInit -= speed * cos(currentDir) * (elapsedTime.asMilliseconds() / 17.6);
			yInit -= speed * sin(currentDir) * (elapsedTime.asMilliseconds() / 17.6);
			// If the enemy is sufficiently close to the target point, pop it and work on the next one
			if (fabs(xInit - (((path.back().x * 32) + 4 + tilePosX))) < 8 && fabs(yInit - (((path.back().y * 26) + 4 + tilePosY))) < 8) {
				recalc--;
				previous = path.back();
				path.pop_back();
				// Calculate the direction to move in
				currentDir = atan2(yInit - (((path.back().y * 26) + 4 + tilePosY)), xInit - (((path.back().x * 32) + 4 + tilePosX)));
			}
		}
		
		// Process the animation
		frameTimer += elapsedTime.asMilliseconds();
		if (frameTimer > 140) {
			frameTimer -= 140;
			frameIndex++;
			if (frameIndex > 2) {
				frameIndex = 0;
			}
		}
		
		// Flip the sprite to face the player
		if (xPos > playerPosX) {
			spriteSheet.setScale(1.f, 1.f);
			shadow.setScale(1.f, 1.f);
		} else {
			spriteSheet.setScale(-1.f, 1.f);
			shadow.setScale(-1.f, 1.f);
		}
	}
	
	else {
		if (fabsf(playerPosX - xPos) < 300 && fabsf(playerPosY - yPos) < 300)
			awake = true;
	}

	shadow.setPosition(xPos + 12, yPos + 1);
	spriteSheet.setPosition(xPos + 12, yPos);
}

const sf::Sprite & Critter::getShadow() const {
	return shadow;
}

const sf::Sprite & Critter::getSprite() const {
	return spriteSheet[frameIndex];
}

void Critter::activate() {
	active = true;
}

void Critter::deActivate() {
	active = false;
}

bool Critter::isActive() {
	return active;
}

void Critter::onDeath(effectsController & effects) {
	// With some random chance, add a heart item to the map
	unsigned long int temp = rand() % 5;
	if (temp == 0) {
		effects.addHearts(xInit + 10, yInit);
	} else {
		effects.addCoins(xInit + 10, yInit);
	}
	effects.addSmallExplosion(xInit + 8, yInit);
	killFlag = true;
}

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

Critter::Critter(sf::Sprite* sprs, short map[61][61]) : EnemyParent(sprs) {
	// Give this object a pointer to the game map
	this->map = map;
	for (auto i = 0; i < 4; i++) {
		sprites[i] = sprs[i];
		// Set the sprite's origin to the center of the texture
		sprites[i].setOrigin(9, 9);
	}
	
	moveCounter = 2;
	recalc = 4;
	moveCount = 3;
	active = true;
	health = 3;
	frameIndex = rand() % 3;
	frameRate = 8;
	awake = false;
}

void Critter::checkBulletCollision(effectsController& ef) {
	//Check collisions with player's shots, but only if the shot vectors aren't empty
	if (!ef.getBulletLayer1().empty()) {
		for (auto & element : ef.getBulletLayer1()) {
			if (std::abs(element.getXpos() - (xPos + 4)) < 8 && std::abs(element.getYpos() - (yPos - 8)) < 8 && !element.getKillFlag()) {
				element.setKillFlag();		   // Kill the bullet if there's a collision between the bullet and the enemy
				// Tons of effects in one place is distracting, so don't draw another one if the enemy is about to explode
				if (health == 1) {
					element.disablePuff();
				}
				health -= 1;
				isColored = true;
				colorAmount = 1.f;
			}
		}
	}
	
	if (health == 0) {
		killFlag = 1;
		// With some random chance, add a heart item to the map
		unsigned long int temp = rand() % 5;
		if (temp == 0) {
			ef.addHearts(xInit + 10, yInit);
		} else {
			ef.addCoins(xInit + 10, yInit);
		}
		ef.addSmallExplosion(xInit + 8, yInit);
	}
}

void Critter::updatePlayerDead() {
	frameIndex = 0;
}

void Critter::update(float xOffset, float yOffset, effectsController &effects, tileController* pTiles, sf::Time & elapsedTime) {
	setPosition(xOffset, yOffset);
	checkBulletCollision(effects);
	if (isColored) {
		colorTimer += elapsedTime.asMilliseconds();
		if (colorTimer > 20.f) {
			colorTimer -= 20.f;
			colorAmount -= 0.1f;
		}
		
		if (colorAmount <= 0.f) {
			isColored = false;
		}
	}
	
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
			origin.x = (xPos - pTiles->posX - xOffset) / 32;
			origin.y = (yPos - pTiles->posY - yOffset) / 26;
			target.x = (pTiles->posX - playerPosX / 2 + xOffset) / -32;
			target.y = (pTiles->posY - playerPosY / 2 - 26 + yOffset) / -26;
			if (map[target.x][target.y] == 3 || map[target.x][target.y] == 4 || map[target.x][target.y] == 5 || map[target.x][target.y] == 11 || map[target.x][target.y] == 8) {
				path = astar_path(target, origin, map);
				previous = path.back();
				path.pop_back();
				xInit = ((xPos - pTiles->posX - xOffset) / 32) * 32 + pTiles->posX;
				yInit = ((yPos - pTiles->posY - yOffset) / 26) * 26 + pTiles->posY;
				// Calculate the direction to move in, based on the coordinate of the previous location and the coordinate of the next location
				currentDir = atan2(yInit - (((path.back().y * 26) + 4 + pTiles->posY)), xInit - (((path.back().x * 32) + 4 + pTiles->posX)));
			}
		}
		
		// If the path is not empty
		else {
			// Add each component of the direction vector to the enemy's position datafields
			xInit -= speed * cos(currentDir);
			yInit -= speed * sin(currentDir);
			// If the enemy is sufficiently close to the target point, pop it and work on the next one
			if (fabs(xInit - (((path.back().x * 32) + 4 + pTiles->posX))) < 8 && fabs(yInit - (((path.back().y * 26) + 4 + pTiles->posY))) < 8) {
				recalc--;
				previous = path.back();
				path.pop_back();
				// Calculate the direction to move in
				currentDir = atan2(yInit - (((path.back().y * 26) + 4 + pTiles->posY)), xInit - (((path.back().x * 32) + 4 + pTiles->posX)));
			}
		}
		
		// Process the animation
		if (--frameRate == 0) {
			frameRate = 8;
			frameIndex++;
			if (frameIndex > 2) {
				frameIndex = 0;
			}
		}
		
		// Flip the sprite to face the player
		if (xPos > playerPosX / 2) {
			sf::Vector2f scaleVec(1, 1);
			sprites[frameIndex].setScale(scaleVec);
			sprites[3].setScale(scaleVec);
		}
		else {
			sf::Vector2f scaleVec(-1, 1);
			sprites[frameIndex].setScale(scaleVec);
			sprites[3].setScale(scaleVec);
		}
	}
	
	else {
		if (fabsf(playerPosX / 2 - xPos) < 300 && fabsf(playerPosY / 2 - yPos) < 300)
			awake = true;
	}
}

sf::Sprite* Critter::getShadow() {
	sprites[3].setPosition(xPos + 12, yPos + 1);
	return &sprites[3];
}

sf::Sprite* Critter::getSprite() {
	// Update the position of the current sprite (rounding is important, otherwise movement will be shaky)
	sprites[frameIndex].setPosition(xPos + 12, yPos);
	return &sprites[frameIndex];
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

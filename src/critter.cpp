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

#include "critter.hpp"
#include "tileController.hpp"
#include "math.h"
#include <cmath>

Critter::Critter(const sf::Texture & txtr, uint8_t _map[61][61], float _xInit, float _yInit) :
	Enemy(_xInit, _yInit),
	xInit(_xInit),
	yInit(_yInit),
	currentDir(0.f),
	jumpTargetx(0.f),
	jumpTargety(0.f),
	spriteSheet(txtr),
	awake(false),
	active(true),
	recalc(4),
	map(_map)
{
	health = 3;
	spriteSheet.setOrigin(9, 9);
	shadow.setOrigin(9, 9);
	shadow.setTexture(txtr);
	shadow.setTextureRect(sf::IntRect(54, 57, 18, 18));
}

const Critter::HBox & Critter::getHitBox() const {
	return hitBox;
}

void Critter::updatePlayerDead() {
	frameIndex = 0;
}

void Critter::update(float, float, const std::vector<wall> &, EffectGroup &, const sf::Time &) {}

void Critter::critterUpdate(float playerPosX, float playerPosY, EffectGroup & effects, const sf::Time & elapsedTime, tileController * pTiles) {
	xPos = xInit + 12;
	yPos = yInit;
	for (auto & element : effects.get<9>()) {
		if (element.getHitBox().overlapping(hitBox) && element.checkCanPoof()) {
			if (health == 1) {
				element.disablePuff();
				element.setKillFlag();
			}
			element.poof();
			health -= 1;
			colored = true;
			colorAmount = 1.f;
		}
	}
	if (health == 0) {
		onDeath(effects);
	}
	xPos -= 12; // Currently off-centered, this is just temporary work-around
	Enemy::updateColor(elapsedTime);
	hitBox.setPosition(xPos, yPos);
	float tilePosX = pTiles->posX;
	float tilePosY = pTiles->posY;
	
	if (awake) {
		float speed;
		if (active) {
			speed = 1.4;
		} else {
			speed= 0.7;
		}
		// If the enemy is finished following its path to the player
		if (path.empty() || recalc == 0) {
			recalc = 8;
			
			aStrCoordinate origin, target;
			origin.x = (xPos - tilePosX) / 32;
			origin.y = (yPos - tilePosY) / 26;
			target.x = (tilePosX - playerPosX - 12) / -32;
			target.y = (tilePosY - playerPosY - 32) / -26;
			if (map[target.x][target.y] == 3 || map[target.x][target.y] == 4 || map[target.x][target.y] == 5 || map[target.x][target.y] == 11 || map[target.x][target.y] == 8) {
				path = astar_path(target, origin, map);
				previous = path.back();
				path.pop_back();
				xInit = ((xPos - tilePosX) / 32) * 32 + tilePosX;
				yInit = ((yPos - tilePosY) / 26) * 26 + tilePosY;
				// Calculate the direction to move in, based on the coordinate of the previous location and the coordinate of the next location
				currentDir = atan2(yInit - (((path.back().y * 26) + 4 + tilePosY)), xInit - (((path.back().x * 32) + 4 + tilePosX)));
			}
		}
		
		// If the path is not empty
		else {
			// Add each component of the direction vector to the enemy's position datafields
			xInit -= speed * cos(currentDir) * (elapsedTime.asMicroseconds() * 0.00005f);
			yInit -= speed * sin(currentDir) * (elapsedTime.asMicroseconds() * 0.00005f);
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

void Critter::onDeath(EffectGroup & effects) {
	// With some random chance, add a heart item to the map
	unsigned long int temp = std::abs(static_cast<int>(global::RNG())) % 5;
	if (temp == 0) {
	    effects.add<4>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects),
					   global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::redglow),
					   xInit + 10, yInit, Item::Type::Heart);
	} else {
	    effects.add<5>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects),
					   global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::blueglow),
					   xInit + 10, yInit, Item::Type::Coin);
	}
    effects.add<1>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects),
				   global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::fireExplosionGlow),
				   xInit + 8, yInit);
	killFlag = true;
}

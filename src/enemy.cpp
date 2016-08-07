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

#include "enemy.hpp"

Enemy::Enemy(float _xPos, float _yPos)
	: killFlag{false},
	  colored{false},
	  xPos{_xPos},
	  yPos{_yPos},
	  colorAmount{0.f},
	  frameIndex{0},
	  colorTimer{0},
	  frameTimer{0}
{}

bool Enemy::getKillFlag() const {
	return killFlag;
}

float Enemy::getColorAmount() const {
	return colorAmount;
}

void Enemy::setKillFlag(bool _killFlag = true) {
	killFlag = _killFlag;
}

bool Enemy::isColored() const {
	return colored;
}

float Enemy::getXpos() const {
	return xPos;
}

float Enemy::getYpos() const {
	return yPos;
}

void Enemy::update(float xOffset, float yOffset, const std::vector<wall> & w, EffectGroup & effects, const sf::Time & elapsedTime) {
}

uint_fast8_t Enemy::checkWallCollision(const std::vector<wall> & w, float collisionRadius, float xPos, float yPos) {
	uint_fast8_t collisionMask = 0;
	for (auto & element : w) {
		if ((xPos + 6 < (element.getPosX() + element.getWidth()) && (xPos + 6 > (element.getPosX()))) && (fabs((yPos + 16) - element.getPosY()) <= 13))  {
			collisionMask |= 0x01;
		}
		
		if ((xPos + 24 > (element.getPosX()) && (xPos + 24 < (element.getPosX() + element.getWidth()))) && (fabs((yPos + 16) - element.getPosY()) <= 13))  {
			collisionMask |= 0x02;
		}
		
		if (((yPos + 22 < (element.getPosY() + element.getHeight())) && (yPos + 22 > (element.getPosY()))) && (fabs((xPos) - element.getPosX()) <= 16))  {
			collisionMask |= 0x04;
		}
		
		if (((yPos + 36 > element.getPosY()) && (yPos + 36 < element.getPosY() + element.getHeight())) && (fabs((xPos) - element.getPosX()) <= 16))  {
			collisionMask |= 0x08;
		}
	}
	return collisionMask;
}

bool Enemy::wallInPath(const std::vector<wall> & w, float dir, float xPos, float yPos) {
	for (int i{10}; i < 100; i += 16) {
		if (checkWallCollision(w, 0, xPos + cos(dir) * i, yPos + sin(dir) * i)) {
			return true;
		}
	}
	
	return false;
}

void Enemy::checkShotCollision(EffectGroup & effects, float rad) {
	if (health == 0) {
		onDeath(effects);
	}
}

void Enemy::updateColor(const sf::Time & elapsedTime) {
	if (colored) {
		colorTimer += elapsedTime.asMilliseconds();
		if (colorTimer > 20.f) {
			colorTimer -= 20.f;
			colorAmount -= 0.1f;
		}
	}

	if (colorAmount <= 0.f) {
		colored = false;
	}
}

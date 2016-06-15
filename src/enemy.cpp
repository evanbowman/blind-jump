//
//  enemyParent.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/21/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "enemy.hpp"

Enemy::Enemy(float _xInit, float _yInit, float _playerPosX, float _playerPosY)
	: killFlag{false},
	  colored{false},
	  xInit{_xInit},
	  yInit{_yInit},
	  playerPosX{_playerPosX},
	  playerPosY{_playerPosY},
	  xPos{0.f},
	  yPos{0.f},
	  colorAmount{0.f},
	  colorTimer{0},
	  frameTimer{0}
{}

bool Enemy::getKillFlag() const {
	return killFlag;
}

float Enemy::getColorAmount() const {
	return colorAmount;
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

float Enemy::getXinit() const {
	return xInit;
}

float Enemy::getYinit() const {
	return yInit;
}

void Enemy::update(float xOffset, float yOffset, const std::vector<wall> & w, effectsController & effects, const sf::Time & elapsedTime) {
	xPos = xInit + xOffset;
	yPos = yInit + yOffset;
}

bool Enemy::checkWallCollision(const std::vector<wall> & w, float collisionRadius, float xPos, float yPos) {
	for (auto & element : w) {
		if ((xPos + 6 < (element.getPosX() + element.width) && (xPos + 6 > (element.getPosX()))) && (fabs((yPos + 16) - element.getPosY()) <= 13))  {
			return true;
		}
		
		if ((xPos + 24 > (element.getPosX()) && (xPos + 24 < (element.getPosX() + element.width))) && (fabs((yPos + 16) - element.getPosY()) <= 13))  {
			return true;
		}
		
		if (((yPos + 22 < (element.getPosY() + element.height)) && (yPos + 22 > (element.getPosY()))) && (fabs((xPos) - element.getPosX()) <= 16))  {
			return true;
		}
		
		if (((yPos + 36 > element.getPosY()) && (yPos + 36 < element.getPosY() + element.height)) && (fabs((xPos) - element.getPosX()) <= 16))  {
			return true;
		}
	}
	return false;
}

bool Enemy::wallInPath(const std::vector<wall> & w, float dir, float xPos, float yPos) {
	for (int i{10}; i < 100; i += 16) {
		if (checkWallCollision(w, 0, xPos + cos(dir) * i, yPos + sin(dir) * i)) {
			return true;
		}
	}
	
	return false;
}

void Enemy::checkShotCollision(effectsController & effects, float rad) {
	if (!effects.getBulletLayer1().empty()) {
		for (auto & element : effects.getBulletLayer1()) {
			if (std::abs(element.getXpos() - (xPos - 6)) < rad
				&& std::abs(element.getYpos() - (yPos - 6)) < rad
				&& !element.getKillFlag()) {
				if (health == 1) {
					element.disablePuff();
				}
				element.setKillFlag();
				health -= 1;
				colored = true;
				colorAmount = 1.f;
			}
		}
	}

	if (health == 0) {
		killFlag = true;
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

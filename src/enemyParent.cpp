//
//  enemyParent.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/21/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "enemyParent.hpp"
#include <math.h>

EnemyParent::EnemyParent(sf::Sprite* sprArr) {
	killFlag = false;
	xInit = 0;
	yInit = 0;
	xPos = 0;
	yPos = 0;
	frameIndex = 0;
	isColored = false;
	colorAmount = 0.f;
	colorTimer = 0.f;
}

bool EnemyParent::getKillFlag() const {
	return killFlag;
}

bool EnemyParent::colored() {
	return isColored;
}

void EnemyParent::setPlayerPos(float x, float y) {
	playerPosX = x;
	playerPosY = y;
}

void EnemyParent::setPosition(float xOffset, float yOffset) {
	xPos = xOffset + xInit;
	yPos = yOffset + yInit;
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

void EnemyParent::setInitPosition(float x, float y) {
	xInit = x;
	yInit = y;
}

float EnemyParent::getXpos() const {
	return xPos;
}

float EnemyParent::getYpos() const {
	return yPos;
}

float EnemyParent::getXinit() const {
	return xInit;
}

float EnemyParent::getYinit() const {
	return yInit;
}

bool EnemyParent::checkCollisionWall(std::vector<wall> w, float collisionRadius) {
	for (auto & element : w) {
		if ((xPos - 4 < (element.getPosX() + element.getWidth()) && (xPos - 4 > (element.getPosX()))) && (fabs((yPos + 4) - element.getPosY()) <= 16))  {
			xInit += 1;
			return true;
		}

		if ((xPos + 12 > (element.getPosX()) && (xPos + 12 < (element.getPosX() + element.getWidth()))) && (fabs((yPos + 4) - element.getPosY()) <= 16))  {
			xInit -= 1;
			return true;
		}

		if (((yPos - 6 < (element.getPosY() + element.getHeight())) && (yPos - 6 > (element.getPosY()))) && (fabs((xPos) - element.getPosX()) <= 16))  {
			yInit += 1;
			return true;
		}

		if (((yPos + 6 > element.getPosY()) && (yPos + 6 < element.getPosY() + element.getHeight())) && (fabs((xPos) - element.getPosX()) <= 16))  {
			yInit -= 1;
			return true;
		}
	}
	return false;
}

//
//  enemyShot.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/2/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "enemyShot.hpp"

Enemyshot::Enemyshot(sf::Texture * pMainTxtr, sf::Texture * pGlowTxtr, float x, float y, float dir) {
	xPos = 0;
	yPos = 0;
	xInit = x;
	yInit = y;
	imageIndex = 0;
	glowSprite.setTexture(*pGlowTxtr);
	glowSprite.setOrigin(22.5, 22.5);
	frameTimer = 0;
	elapsedTime = 0;
	spriteSheet.setTexture(pMainTxtr);
	direction = (dir - 270) * (3.14 / 180);
	killFlag = false;
}

void Enemyshot::update(float xOffset, float yOffset, sf::Time & elapsedTime) {
	xInit += 4.4 * (elapsedTime.asMilliseconds() / 17.6) * (cos(direction));		 // Note: timeout starts at 60, so 60 - timout grows linearly with time
	yInit += 4.4 * (elapsedTime.asMilliseconds() / 17.6) * (sin(direction));
	xPos = xInit + xOffset;
	yPos = yInit + yOffset + 11;

	glowSprite.setPosition(xPos, yPos + 18);
	
	this->elapsedTime += elapsedTime.asMilliseconds();
	frameTimer += elapsedTime.asMilliseconds();
	
	if (frameTimer > 211) {
		frameTimer -= 211;
		if (imageIndex == 0) {
			imageIndex = 1;
		}
		else {
			imageIndex = 0;
		}
	}
	
	if (this->elapsedTime > 600) {
		killFlag = true;
	}
	
	float offset = rand() % 20;
	glowSprite.setColor(sf::Color(230 + offset, 230 + offset, 230 + offset, 255));
	spriteSheet.setPosition(xPos, yPos);
}

sf::Sprite * Enemyshot::getGlow() {
	return &glowSprite;
}

const sf::Sprite & Enemyshot::getSprite() {
	return spriteSheet[imageIndex];
}

bool Enemyshot::getKillFlag() {
	return killFlag;
}

void Enemyshot::setKillFlag() {
	killFlag = true;
}

float Enemyshot::getXpos() {
	return xPos;
}

float Enemyshot::getYpos() {
	return yPos;
}

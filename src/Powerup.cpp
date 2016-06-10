//
//  Hearts.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 4/2/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "Powerup.hpp"

#define PI 3.1415926535

Powerup::Powerup(sf::Texture * pBodyTxtr, sf::Texture * pGlowTxtr, float xInit, float yInit, Type id) {
	this->xInit = xInit;
	this->yInit = yInit;
	glow.setTexture(*pGlowTxtr);
	glow.setOrigin(22.5, 22.5);
	powerupSheet.setTexture(pBodyTxtr);
	// Square brace overloads provide access, but in doing so also set the working frame
	powerupSheet[static_cast<int>(id)];
	powerupSheet.setOrigin(7, 7);
	timer = 0;
	killFlag = false;
}

void Powerup::update(float xoffset, float yoffset, sf::Time & elapsedTime) {
	xPos = xInit + xoffset;
	yPos = yInit + yoffset;
	timer += elapsedTime.asMilliseconds();
}

const sf::Sprite & Powerup::getSprite() {
	float offset = (3 * sinf(2 * PI * 0.001 * timer + 180));
	// Make the sprite float up and down
	powerupSheet.setPosition(xPos, yPos + offset);
	return powerupSheet.getSprite();
}

sf::Sprite* Powerup::getGlow() {
	glow.setPosition(xPos, yPos + 10);
	return &glow;
}

bool Powerup::getKillFlag() {
	return killFlag;
}

void Powerup::setKillFlag(bool killFlag) {
	this->killFlag = killFlag;
}

float Powerup::getXpos() {
	return xPos;
}

float Powerup::getYpos() {
	return yPos - 16;
}

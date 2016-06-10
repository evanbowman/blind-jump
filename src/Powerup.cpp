//
//  Hearts.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 4/2/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "Powerup.hpp"

#define PI 3.1415926535

Powerup::Powerup(sf::Sprite* inpSpr, sf::Sprite glow, float xInit, float yInit) {
	this->xInit = xInit;
	this->yInit = yInit;
	this->glow = glow;
	spr = *inpSpr;
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
	spr.setPosition(xPos, yPos + offset);
	return spr;
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

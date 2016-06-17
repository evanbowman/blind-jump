//
//  turretShot.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/26/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "turretShot.hpp"

turretShot::turretShot(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr, float x, float y, float dir) {
	spriteSheet.setTexture(mainTxtr);
	glowSprite.setTexture(glowTxtr);
	xPos = 0;
	yPos = 0;
	xInit = x;
	yInit = y;
	int diff = pow(-1,rand() % 2) + rand() % 6 - 3;
	spriteSheet.setRotation(dir + diff);
	spriteSheet.setOrigin(4, 6);
	glowSprite.setOrigin(22.5, 22.5);
	direction = (dir - 270 + diff) * (3.14 / 180);	 // I added 270 previously to get the sprite to face in the right direction, so subract it
												//back out and convert back to radians
	killFlag = false;
	scale = 4.4;
	frameIndex = 0;
	timer = 0;
	animationTimer = 0;
}

void turretShot::update(float xOffset, float yOffset, sf::Time & elapsedTime) {
	xInit += scale * 1.5 * (elapsedTime.asMilliseconds() / 17.6) * (cos(direction));		 // Note: timeout starts at 60, so 60 - timout grows linearly with time
	yInit += scale * 1.5 * (elapsedTime.asMilliseconds() / 17.6) * (sin(direction));
	xPos = xInit + xOffset;
	yPos = yInit + yOffset + 11;
	spriteSheet.setPosition(xPos, yPos);
	glowSprite.setPosition(xPos, yPos + 18);
	timer += elapsedTime.asMilliseconds();
	if (timer > 600) {
		killFlag = true;
	}
	float offset = rand() % 20;
	glowSprite.setColor(sf::Color(230 + offset, 230 + offset, 230 + offset, 255));
	animationTimer += elapsedTime.asMilliseconds();
	if (animationTimer > 50) {
		animationTimer -= 50;
		if (frameIndex == 1) {
			frameIndex = 0;
		} else {
			frameIndex = 1;
		}
	}
}

const sf::Sprite & turretShot::getSprite() {
	return spriteSheet[frameIndex];
}

sf::Sprite* turretShot::getGlow() {
	return &glowSprite;
}

bool turretShot::getKillFlag() {
	return killFlag;
}

void turretShot::setKillFlag() {
	killFlag = true;
}

float turretShot::getXpos() {
	return xPos;
}

float turretShot::getYpos() {
	return yPos;
}

void turretShot::speedFactor(float factor) {
	scale = factor;
}

//
//  turretFlashEffect.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "turretFlashEffect.hpp"

turretFlashEffect::turretFlashEffect(sf::Texture * pTxtr, float x, float y) {
	spriteSheet.setTexture(pTxtr);
	xPos = 0;
	yPos = 0;
	xInit = x;
	yInit = y;
	imageIndex = 0;
	clock.restart();
	killFlag = false;
	bool select = rand() % 2;
	if (select) {
		spriteSheet.setScale(-1.f, 1.f);
		yInit += 18;
		xInit += 17;
	}
}

//Update the position of the image
void turretFlashEffect::update(float xOffset, float yOffset) {
	if (clock.getElapsedTime().asMilliseconds() > 40) {
		imageIndex += 1;
		if (imageIndex > 4) {
			killFlag = true;
			imageIndex = 4;
		}
		clock.restart();
	}
	xPos = xInit + xOffset;
	yPos = yInit + 11 + yOffset;
	spriteSheet.setPosition(xPos, yPos);
}

//A funtion to return the current sprite
const sf::Sprite & turretFlashEffect::getSprite() {
	return spriteSheet[imageIndex];
}

float turretFlashEffect::getYpos() {
	return yPos;
}

bool turretFlashEffect::getKillFlag() {
	return killFlag;
}

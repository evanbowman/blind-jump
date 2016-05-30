//
//  turretFlashEffect.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "turretFlashEffect.hpp"

turretFlashEffect::turretFlashEffect(sf::Sprite sprites[5], float x, float y) {
	//Take all of the input sprites and save them for alter
	for (int i = 0; i < 5; i++) {
		flashSprites[i] = sprites[i];
	}
	xPos = 0;
	yPos = 0;
	xInit = x;
	yInit = y;
	imageIndex = 0;
	clock.restart();
	killFlag = false;
	bool select = rand() % 2;
	if (select) {
		for (int i = 0; i < 5; i++) {
			flashSprites[i].setScale(-1,-1);
		}
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
}

//A funtion to return the current sprite
sf::Sprite turretFlashEffect::getSprite() {
	flashSprites[imageIndex].setPosition(xPos, yPos);
	return flashSprites[imageIndex];
}

float turretFlashEffect::getYpos() {
	return yPos;
}

bool turretFlashEffect::getKillFlag() {
	return killFlag;
}

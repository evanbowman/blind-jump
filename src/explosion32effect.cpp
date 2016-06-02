//
//  explosion32effect.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 11/7/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "explosion32effect.hpp"

Explosion32effect::Explosion32effect(sf::Sprite sprIn[6], float x, float y) {
	xPos = x;
	yPos = y;
	//Store all of the sprites for later
	for (int i = 0; i < 6; i++) {
		sprExp[i] = sprIn[i];
	}
	spriteIndex = 0;
	animationCounter = 4;
	//A variable to tell the effect controller when to pop the effect
	imFinished = 0;
	xInit = xPos;
	yInit = yPos;
	animationLength = 6;
}

//Updates the position of the effect
void Explosion32effect::positionUpdateF(float xOffset, float yOffset) {
	xPos = xInit + xOffset;
	yPos = yInit + yOffset;
}

sf::Sprite Explosion32effect::getSprite() {
	if (--animationCounter == 0) {
		animationCounter = 2;
		spriteIndex += 1;
		if (spriteIndex == animationLength) {
			spriteIndex = 5;
			imFinished = 1;
		}
	}
	sprExp[spriteIndex].setPosition(xPos, yPos);
	return sprExp[spriteIndex];
}

float Explosion32effect::getXpos() {
	return xPos;
}

float Explosion32effect::getYpos() {
	return yPos;
}
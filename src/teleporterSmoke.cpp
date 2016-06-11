//
//  teleporterSmoke.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/1/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "teleporterSmoke.hpp"

#define ANIMATION_LENGTH 6

TeleporterSmoke::TeleporterSmoke(sf::Texture * pTxtr, float x, float y) {
	xPos = x;
	xInit = x;
	yPos = y;
	yInit = y;
	spriteSheet.setTexture(pTxtr);
	// Initialize the current frame of the animation to the first one
	frameIndex = 0;
	frameTimer = 0;
	killFlag = false;
	// Initialize the depth to 0
	drawOrder = 0;
}

void TeleporterSmoke::update(float xOffset, float yOffset, sf::Time & elapsedTime) {
	xPos = xInit + xOffset;
	yPos = yInit + yOffset;
	// Drift up
	yInit -= (elapsedTime.asMilliseconds() / 17.6) * 0.6;
	frameTimer += elapsedTime.asMilliseconds();
	spriteSheet.setPosition(xPos, yPos);
}

const sf::Sprite & TeleporterSmoke::getSprite() {
	// Due to ordering of the controller code, updates to the frame index need
	// to happen here. This is a special case where the sprite maps to a different
	// vector depending on its layer. In other instances, 'get...()' member functions
	// should not alter internal datafields for objects.
	if (frameTimer > 105) {
		frameTimer -= 105;
		frameIndex++;
		if (frameIndex > 2) {
			drawOrder = 1;
		}
		
		if (frameIndex == ANIMATION_LENGTH) {
			frameIndex = 5;
			killFlag = true;
		}
	}
	return spriteSheet[frameIndex];
}

bool TeleporterSmoke::getKillFlag() {
	return killFlag;
}

float TeleporterSmoke::getPosX() {
	return xPos;
}

float TeleporterSmoke::getYpos() {
	return yPos;
}

char TeleporterSmoke::getDrawOrder() {
	return drawOrder;
}

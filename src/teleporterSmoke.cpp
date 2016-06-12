//
//  teleporterSmoke.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/1/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "teleporterSmoke.hpp"

#define ANIMATION_LENGTH 6

TeleporterSmoke::TeleporterSmoke(sf::Texture * pTxtr, float x, float y) : Effect(x, y) {
	spriteSheet.setTexture(pTxtr);
	drawOrder = 0;
}

void TeleporterSmoke::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	yPos = yInit + yOffset;
	// Drift up
	yInit -= (elapsedTime.asMilliseconds() / 17.6) * 0.6;
	timer += elapsedTime.asMilliseconds();
	spriteSheet.setPosition(xInit + xOffset, yPos);
}

const sf::Sprite & TeleporterSmoke::getSprite() {
	// Due to ordering of the controller code, updates to the frame index need
	// to happen here. This is a special case where the sprite maps to a different
	// vector depending on its layer. In other instances, 'get...()' member functions
	// should not alter internal datafields for objects.
	if (timer > 105) {
		timer -= 105;
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

char TeleporterSmoke::getDrawOrder() {
	return drawOrder;
}

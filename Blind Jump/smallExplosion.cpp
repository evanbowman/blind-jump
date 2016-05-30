//
//  smallExplosion.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/19/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "smallExplosion.hpp"

SmallExplosion::SmallExplosion(sf::Sprite* sprs, sf::Sprite glow, float x, float y) {
	for (int i = 0; i < 6; i++) {
		sprites[i] = sprs[i];
		sprites[i].setOrigin(18, 18);
	}
	this->glow = glow;
	this->glow.setColor(sf::Color(220, 220, 220));
	xInit = x;
	yInit = y;
	killFlag = false;
	frameIndex = 0;
	frameRate = 5;
}

void SmallExplosion::update(float xOffset, float yOffset, sf::Time & elapsedTime) {
	xPos = xInit + xOffset;
	yPos = yInit + yOffset;
	if (--frameRate == 0) {
		frameRate = 5;
		frameIndex++;
		if (frameIndex > 5) {
			frameIndex = 5;
			killFlag = true;
		}
	}
	sf::Color c = glow.getColor();
	if (c.r > 8) {
		c.r -= 10;
		c.g -= 10;
		c.b -= 10;
		glow.setColor(c);
	}
	sprites[frameIndex].setPosition(xPos, yPos);
	glow.setPosition(xPos - 225, yPos - 225);
}

sf::Sprite* SmallExplosion::getGlow() {
	return &glow;
}

sf::Sprite SmallExplosion::getSprite() {
	return sprites[frameIndex];
}

bool SmallExplosion::getKillFlag() {
	return killFlag;
}

float SmallExplosion::getYpos() {
	return yPos;
}

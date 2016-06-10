//
//  smallExplosion.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/19/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "smallExplosion.hpp"

SmallExplosion::SmallExplosion(sf::Texture * pMainTxtr, sf::Texture * pGlowTxtr, float x, float y) {
    spriteSheet.setTexture(pMainTxtr);
	spriteSheet.setOrigin(18, 18);
	glow.setTexture(*pGlowTxtr);
    glow.setColor(sf::Color(220, 220, 220));
	xInit = x;
	yInit = y;
	killFlag = false;
	frameIndex = 0;
	timer = 0;
}

void SmallExplosion::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	xPos = xInit + xOffset;
	yPos = yInit + yOffset;
	timer += elapsedTime.asMilliseconds();
	if (timer > 88) {
		timer -= 88;
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
	spriteSheet.setPosition(xPos, yPos);
	glow.setPosition(xPos - 225, yPos - 225);
}

sf::Sprite * SmallExplosion::getGlow() {
	return &glow;
}

const sf::Sprite & SmallExplosion::getSprite() {
	return spriteSheet[frameIndex];
}

bool SmallExplosion::getKillFlag() {
	return killFlag;
}

float SmallExplosion::getYpos() {
	return yPos;
}

//
//  FireExplosion.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/18/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "FireExplosion.hpp"

FireExplosion::FireExplosion(sf::Texture * pMainTxtr, sf::Texture * pGlowTxtr, float x, float y) {
	spriteSheet.setTexture(pMainTxtr);
	spriteSheet.setOrigin(29, 25);
	glow.setTexture(*pGlowTxtr);
	glow.setColor(sf::Color(240, 240, 240));
	xInit = x;
	yInit = y;
	killFlag = false;
	frameIndex = 0;
	animationTimer = 0;
	valid = true;
}

void FireExplosion::update(float xOffset, float yOffset, sf::Time & elapsedTime) {
	xPos = xInit + xOffset;
	yPos = yInit + yOffset;
	animationTimer += elapsedTime.asMilliseconds();
	if (animationTimer > 70) {
		animationTimer -= 70;
		frameIndex++;
		if (frameIndex > 8) {
			frameIndex = 8;
			killFlag = true;
		}
	}
	sf::Color c = glow.getColor();
	if (c.r > 8) {
		c.r -= 8;
		c.g -= 8;
		c.b -= 8;
		glow.setColor(c);
	}
	spriteSheet.setPosition(xPos, yPos);
	glow.setPosition(xPos - 225, yPos - 225);
}

sf::Sprite * FireExplosion::getGlow() {
	return &glow;
}

const sf::Sprite & FireExplosion::getSprite() {
	return spriteSheet[frameIndex];
}

bool FireExplosion::getKillFlag() {
	return killFlag;
}

float FireExplosion::getYpos() {
	return yPos;
}

float FireExplosion::getXpos() {
	return xPos;
}

bool FireExplosion::isValid() {
	return valid;
}

void FireExplosion::invalidate() {
	valid = false;
}

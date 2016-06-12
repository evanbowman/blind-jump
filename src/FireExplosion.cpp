//
//  FireExplosion.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/18/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "FireExplosion.hpp"

FireExplosion::FireExplosion(sf::Texture * pMainTxtr, sf::Texture * pGlowTxtr, float x, float y) : Effect(x, y) {
	spriteSheet.setTexture(pMainTxtr);
	spriteSheet.setOrigin(29, 25);
	glow.setTexture(*pGlowTxtr);
	glow.setColor(sf::Color(240, 240, 240));
}

void FireExplosion::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	yPos = yInit + yOffset;
	timer += elapsedTime.asMilliseconds();
	if (timer > 70) {
		timer -= 70;
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
	
	spriteSheet.setPosition(xInit + xOffset, yPos);
	glow.setPosition(xInit + xOffset - 225, yPos - 225);
}

sf::Sprite * FireExplosion::getGlow() {
	return &glow;
}

const sf::Sprite & FireExplosion::getSprite() {
	return spriteSheet[frameIndex];
}

bool FireExplosion::isValid() {
	return valid;
}

void FireExplosion::invalidate() {
	valid = false;
}

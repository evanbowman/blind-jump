//
//  smallExplosion.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/19/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "smallExplosion.hpp"

SmallExplosion::SmallExplosion(sf::Texture * pMainTxtr, sf::Texture * pGlowTxtr, float x, float y) : Effect(x, y) {
    spriteSheet.setTexture(pMainTxtr);
	spriteSheet.setOrigin(18, 18);
	glow.setTexture(*pGlowTxtr);
    glow.setColor(sf::Color(220, 220, 220));
}

void SmallExplosion::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	yPos = yInit + yOffset;
	timer += elapsedTime.asMilliseconds();
	if (timer > 60) {
		timer -= 60;
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
	spriteSheet.setPosition(xInit + xOffset, yPos);
	glow.setPosition(xInit + xOffset - 225, yPos - 225);
}

sf::Sprite * SmallExplosion::getGlow() {
	return &glow;
}

const sf::Sprite & SmallExplosion::getSprite() const {
	return spriteSheet[frameIndex];
}

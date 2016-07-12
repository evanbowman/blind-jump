//
//  FireExplosion.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/18/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "FireExplosion.hpp"

FireExplosion::FireExplosion(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr, float x, float y) : Effect(x, y) {
	spriteSheet.setTexture(mainTxtr);
	spriteSheet.setOrigin(29, 25);
	glow.setTexture(glowTxtr);
	glow.setColor(sf::Color(240, 240, 240));
}

void FireExplosion::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	setPosition(xInit + xOffset, yInit + yOffset);
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
	
	spriteSheet.setPosition(position.x, position.y);
	glow.setPosition(position.x - 225, position.y - 225);
}

Sprite * FireExplosion::getGlow() {
	return &glow;
}

const Sprite & FireExplosion::getSprite() const {
	return spriteSheet[frameIndex];
}

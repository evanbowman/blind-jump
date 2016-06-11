//
//  turretFlashEffect.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "turretFlashEffect.hpp"

turretFlashEffect::turretFlashEffect(sf::Texture * pTxtr, float x, float y) : Effect(x, y) {
	spriteSheet.setTexture(pTxtr);
	bool select = rand() % 2;
	if (select) {
		spriteSheet.setScale(-1.f, 1.f);
		xInit += 17;
	}
}

void turretFlashEffect::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	timer += elapsedTime.asMilliseconds();
	if (timer > 40) {
		timer -= 40;
		frameIndex += 1;
		if (frameIndex > 4) {
			killFlag = true;
			frameIndex = 4;
		};
	}
	yPos = yInit + 11 + yOffset;
	spriteSheet.setPosition(xInit + xOffset, yPos);
}

const sf::Sprite & turretFlashEffect::getSprite() {
	return spriteSheet[frameIndex];
}

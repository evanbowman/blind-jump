//
//  turretFlashEffect.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "turretFlashEffect.hpp"

turretFlashEffect::turretFlashEffect(const sf::Texture & txtr, float x, float y) : Effect(x, y) {
	spriteSheet.setTexture(txtr);
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
			setKillFlag();
			frameIndex = 4;
		};
	}
	setPosition(xInit + xOffset, yInit + yOffset);
	spriteSheet.setPosition(position.x, position.y);
}

const Sprite & turretFlashEffect::getSprite() const {
	return spriteSheet[frameIndex];
}

//
//  shotPoof.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/14/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "shotPuff.hpp"

shotPuff::shotPuff(sf::Texture * pTxtr, float x, float y) : Effect(x, y) {
	spriteSheet.setTexture(pTxtr);
}

void shotPuff::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	yPos = yInit + yOffset;
	timer += elapsedTime.asMilliseconds();
	if (timer > 50) {
		timer -= 50;
		frameIndex += 1;
		if (frameIndex == 4) {
			frameIndex = 3;
			killFlag = true;
		}
	}
	spriteSheet.setPosition(xInit + xOffset, yPos);
}

const sf::Sprite & shotPuff::getSprite() const {
	return spriteSheet[frameIndex];
}

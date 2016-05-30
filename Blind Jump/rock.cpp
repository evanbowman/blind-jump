//
//  rock.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/5/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "rock.hpp"

Rock::Rock(float xStart, float yStart, sf::Sprite* inpSpr, int len, float width, float height) : detailParent(xStart, yStart, inpSpr, len, width, height) {
	sprite = inpSpr[0];
}

void Rock::update(float xOffset, float yOffset) {
	// Update the object's position
	xPos = xOffset + xInit;
	yPos = yOffset + yInit;
}

sf::Sprite* Rock::getSprite() {
	sprite.setPosition(xPos, yPos);
	return &sprite;
}
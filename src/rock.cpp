//
//  rock.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/5/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "rock.hpp"

Rock::Rock(float xStart, float yStart, sf::Texture * inpTxtr, int len, float width, float height) : detailParent(xStart, yStart, len, width, height) {
	rockSheet.setTexture(inpTxtr);
    if (rand() % 2) {
		rockSheet.setScale(-1, 1);
	    xInit += 32;
	}

	if (rand() % 2) {
		rockSheet[1];
	} else {
		rockSheet[0];
	}
}

void Rock::update(float xOffset, float yOffset) {
	rockSheet.setPosition(xOffset + xInit, yOffset + yInit);
}

sf::Sprite* Rock::getSprite() {
	return rockSheet.getSpritePtr();
}

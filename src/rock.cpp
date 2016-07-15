//
//  rock.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/5/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "rock.hpp"

Rock::Rock(float _xInit, float _yInit, const sf::Texture & inpTxtr)
	: Detail{_xInit, _yInit}
{
	rockSheet.setTexture(inpTxtr);
    if (rand() % 2) {
		rockSheet.setScale(-1, 1);
	    xInit += 32;
	}
	rockSheet[rand() % 4];
}

void Rock::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	setPosition(xInit + xOffset, yInit + yOffset);
	rockSheet.setPosition(position.x, position.y);
}

const sf::Sprite & Rock::getSprite() const {
	return rockSheet.getSprite();
}

//
//  treasureChest.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 11/14/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "treasureChest.hpp"
#include <cmath>

TreasureChest::TreasureChest(float _xInit, float _yInit, const sf::Texture & chestTextures, const sf::Texture & shadowTexture, char _item)
	: Detail{_xInit, _yInit},
	  state{State::closed},
	  item{_item},
	  animationTimer{0},
	  frameIndex{0},
	  chestSheet{chestTextures}
{
	chestShadow.setTexture(shadowTexture);
}

const sf::Sprite & TreasureChest::getShadow() const {
	return chestShadow;
}

const sf::Sprite & TreasureChest::getSprite() const {
	return chestSheet[frameIndex];
}

void TreasureChest::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	yPos = yInit + yOffset;
	xPos = xInit + xOffset;
	chestSheet.setPosition(xPos, yPos - 16);
	chestShadow.setPosition(xPos, yPos + 12);

	switch (state) {
	case State::opening:
		animationTimer += elapsedTime.asMilliseconds();
		if (animationTimer > 50) {
			animationTimer -= 50;
			frameIndex++;
			if (frameIndex > 5) {
				frameIndex = 4;
				state = State::ready;
			}
		}
		break;

	default:
		break;
	}
}

char TreasureChest::getItem() const {
	return item;
}

TreasureChest::State TreasureChest::getState() const {
	return state;
}

float TreasureChest::getXpos() {
	return xPos;
}

void TreasureChest::setState(const TreasureChest::State _state) {
	state = _state;
}

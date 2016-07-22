//
//  damagedRobot.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/5/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "damagedRobot.hpp"

DamagedRobot::DamagedRobot(float _xInit, float _yInit, const sf::Texture & inpTxtr)
	: Detail{_xInit, _yInit}, robotSheet{inpTxtr}
{
	robotSheet[std::abs(static_cast<int>(globalRNG())) % 2]; // Randomly pick one of the textures...
}

void DamagedRobot::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	setPosition(xInit + xOffset, yInit + yOffset);
	robotSheet.setPosition(position.x, position.y);
}

const sf::Sprite & DamagedRobot::getSprite() const {
	return robotSheet.getSprite();
}

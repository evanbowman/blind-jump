//
//  lampLight.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/16/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "lampLight.hpp"

LampLight::LampLight(float _xInit, float _yInit, const sf::Texture & txtr, const sf::Texture & glwTxtr)
	: Detail{_xInit, _yInit}
{
	glowSprite.setTexture(glwTxtr);
	lampSprite.setTexture(txtr);
	lampSprite.setTextureRect(sf::IntRect(40, 91, 10, 9));
}

void LampLight::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	setPosition(xInit + xOffset, yInit + yOffset);
	lampSprite.setPosition(position.x, position.y + 8);
	glowSprite.setPosition(position.x - 250 + 16, position.y - 250 + 16);
	float offset = rand() % 20;
	glowSprite.setColor(sf::Color(230 + offset, 230 + offset, 230 + offset, 255));
}

const sf::Sprite & LampLight::getSprite() const {
	return lampSprite;
}

sf::Sprite * LampLight::getGlow() {
	return &glowSprite;
}

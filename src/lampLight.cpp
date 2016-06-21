//
//  lampLight.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/16/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "lampLight.hpp"

LampLight::LampLight(float _xInit, float _yInit, const sf::Texture & txtr, sf::Sprite & glwSpr)
	: Detail{_xInit, _yInit},
	  killflag{false}
{
	glowSprite = glwSpr;
	lampSprite.setTexture(txtr);
	lampSprite.setTextureRect(sf::IntRect(40, 91, 10, 9));
}

void LampLight::setKillFlag(bool cond) {
	killflag = cond;
}

bool LampLight::getKillFlag() {
	return killflag;
}

void LampLight::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	xPos = xOffset + xInit;
	yPos = yOffset + yInit - 8;
	lampSprite.setPosition(xPos, yPos + 8);
	glowSprite.setPosition(xPos - 250 + 16, yPos - 250 + 16);
	float offset = rand() % 20;
	glowSprite.setColor(sf::Color(230 + offset, 230 + offset, 230 + offset, 255));
}

const sf::Sprite & LampLight::getSprite() const {
	return lampSprite;
}

float LampLight::getXpos() {
	return xPos;
}

sf::Sprite * LampLight::getGlow() {
	return &glowSprite;
}

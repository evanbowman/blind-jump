//
//  lampLight.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/16/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "lampLight.hpp"

LampLight::LampLight(float xStart, float yStart, sf::Sprite inpSpr, sf::Sprite glowSprite, int len, float width, float height) : detailParent(xStart, yStart, &inpSpr, len, width, height) {
	this->glowSprite = glowSprite;
	lampSprite = inpSpr;
	killflag = false;
}

void LampLight::setKillFlag(bool cond) {
	killflag = cond;
}

bool LampLight::getKillFlag() {
	return killflag;
}

void LampLight::update(float xOffset, float yOffset) {
	xPos = xOffset + xInit;
	yPos = yOffset + yInit - 8;
	lampSprite.setPosition(xPos, yPos + 8);
	glowSprite.setPosition(xPos - 250 + 16, yPos - 250 + 16);
	float offset = rand() % 20;
	glowSprite.setColor(sf::Color(230 + offset, 230 + offset, 230 + offset, 255));
}

sf::Sprite* LampLight::getSprite() {
	return &lampSprite;
}

sf::Sprite* LampLight::getGlow() {
	return &glowSprite;
}

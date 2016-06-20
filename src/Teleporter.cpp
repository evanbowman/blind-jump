
//
//  mapTower.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 11/7/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "Teleporter.hpp"

Teleporter::Teleporter(float _xInit, float _yInit, const sf::Texture & mainTxtr, sf::Sprite * pGlow)
	: Detail{_xInit, _yInit},
	  smokeTimer{0}
{
	for (int i = 0; i < 2; i++)
		TeleporterSprites[i].setTexture(mainTxtr);
	glowSprite = *pGlow;
	glowSprite.setOrigin(200, 200);
	TeleporterSprites[0].setTextureRect(sf::IntRect(752, 76, 34, 29));
	TeleporterSprites[1].setTextureRect(sf::IntRect(174, 195, 34, 29));
}

const sf::Sprite & Teleporter::getShadow() const {
	return TeleporterSprites[1];
}

const sf::Sprite & Teleporter::getSprite() const {
	return TeleporterSprites[0];
}

void Teleporter::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	smokeTimer += elapsedTime.asMilliseconds();
	xPos = xOffset + xInit;
	yPos = yOffset + yInit;
	glowSprite.setPosition(xPos + 16, yPos + 13);
	TeleporterSprites[0].setPosition(xPos - 3, yPos);
	TeleporterSprites[1].setPosition(xPos - 3, yPos + 4);
}

sf::Sprite * Teleporter::getGlow() {
	return &glowSprite;
}

float Teleporter::getXpos() {
	return xPos;
}

bool Teleporter::smokeReady() {
	if (smokeTimer > 264) {
		smokeTimer -= 264;
		return true;
	}
	return false;
}


//
//  mapTower.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 11/7/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "Teleporter.hpp"

Teleporter::Teleporter(float _xInit, float _yInit, const sf::Texture & mainTxtr, const sf::Texture & glowTxtr)
	: Detail{_xInit, _yInit},
	  smokeTimer{0}
{
	for (int i = 0; i < 2; i++) {
		TeleporterSprites[i].setTexture(mainTxtr);
	}
	glowSprite.setTexture(glowTxtr);
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
	setPosition(xInit + xOffset, yInit + yOffset);
	glowSprite.setPosition(position.x + 16, position.y + 13);
	TeleporterSprites[0].setPosition(position.x - 3, position.y);
	TeleporterSprites[1].setPosition(position.x - 3, position.y + 4);
}

sf::Sprite * Teleporter::getGlow() {
	return &glowSprite;
}

bool Teleporter::smokeReady() {
	if (smokeTimer > 264) {
		smokeTimer -= 264;
		return true;
	}
	return false;
}

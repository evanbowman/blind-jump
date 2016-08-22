//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

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
	TeleporterSprites[0].setTextureRect(sf::IntRect(390, 224, 34, 29));
	TeleporterSprites[1].setTextureRect(sf::IntRect(174, 195, 34, 29));
	glowSprite.setPosition(position.x + 16, position.y + 13);
	TeleporterSprites[0].setPosition(position.x - 3, position.y);
	TeleporterSprites[1].setPosition(position.x - 3, position.y + 4);
}

const sf::Sprite & Teleporter::getShadow() const {
	return TeleporterSprites[1];
}

const sf::Sprite & Teleporter::getSprite() const {
	return TeleporterSprites[0];
}

void Teleporter::update(const sf::Time &) {
	// nil
}

const sf::Sprite & Teleporter::getGlow() const {
	return glowSprite;
}

bool Teleporter::smokeReady() {
	if (smokeTimer > 264) {
		smokeTimer -= 264;
		return true;
	}
	return false;
}

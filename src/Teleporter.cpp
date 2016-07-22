//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
//                                                                        //
// This program is free software: you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or      //
// (at your option) any later version.                                    //
//                                                                        //
// This program is distributed in the hope that it will be useful,        //
// but WITHOUT ANY WARRANTY; without even the implied warranty of         //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
// GNU General Public License for more details.                           //
//                                                                        //
// You should have received a copy of the GNU General Public License      //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
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

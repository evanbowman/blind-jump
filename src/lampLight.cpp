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

#include "lampLight.hpp"

LampLight::LampLight(float _xInit, float _yInit, const sf::Texture & txtr, const sf::Texture & glwTxtr)
	: Detail{_xInit, _yInit}
{
	glowSprite.setTexture(glwTxtr);
	lampSprite.setTexture(txtr);
	lampSprite.setTextureRect(sf::IntRect(40, 91, 10, 9));
	lampSprite.setPosition(position.x, position.y + 8);
	glowSprite.setPosition(position.x - 250 + 16, position.y - 250 + 16);
}

void LampLight::update(const sf::Time & elapsedTime) {
	// ...
}

const sf::Sprite & LampLight::getSprite() const {
	return lampSprite;
}

const sf::Sprite & LampLight::getGlow() const {
	return glowSprite;
}

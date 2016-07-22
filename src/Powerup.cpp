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

#include "Powerup.hpp"

const static float PI{3.1415926535};

Powerup::Powerup(const sf::Texture & bodyTxtr, const sf::Texture & glowTxtr, float xInit, float yInit, Type id) :
	Effect(xInit, yInit)
{
	glow.setTexture(glowTxtr);
	glow.setOrigin(22.5, 22.5);
	powerupSheet.setTexture(bodyTxtr);
	// Square brace overloads provide access, but in doing so also set the working frame
	powerupSheet[static_cast<int>(id)];
	powerupSheet.setOrigin(7, 7);
	timer = 0;
	killFlag = false;
}

void Powerup::update(float xOffset, float yOffset, sf::Time & elapsedTime) {
	setPosition(xInit + xOffset, yInit + yOffset);
	hitBox.setPosition(position);
	timer += elapsedTime.asMilliseconds();
}

const sf::Sprite & Powerup::getSprite() {
	const float offset = (3 * sinf(2 * PI * 0.001 * timer + 180));
	// Make the sprite float up and down
	powerupSheet.setPosition(position.x, position.y + offset);
	return powerupSheet.getSprite();
}

sf::Sprite * Powerup::getGlow() {
	glow.setPosition(position.x, position.y + 10);
	return &glow;
}

const Powerup::HBox & Powerup::getHitBox() const {
	return hitBox;
}

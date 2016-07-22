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

#include "FireExplosion.hpp"

FireExplosion::FireExplosion(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr, float x, float y) : Effect(x, y) {
	spriteSheet.setTexture(mainTxtr);
	spriteSheet.setOrigin(29, 25);
	glow.setTexture(glowTxtr);
	glow.setColor(sf::Color(240, 240, 240));
}

void FireExplosion::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	setPosition(xInit + xOffset, yInit + yOffset);
	timer += elapsedTime.asMilliseconds();
	if (timer > 70) {
		timer -= 70;
		frameIndex++;
		if (frameIndex > 8) {
			frameIndex = 8;
			killFlag = true;
		}
	}
	
	sf::Color c = glow.getColor();
	if (c.r > 8) {
		c.r -= 8;
		c.g -= 8;
		c.b -= 8;
		glow.setColor(c);
	}
	
	spriteSheet.setPosition(position.x, position.y);
	glow.setPosition(position.x - 225, position.y - 225);
}

Sprite * FireExplosion::getGlow() {
	return &glow;
}

const Sprite & FireExplosion::getSprite() const {
	return spriteSheet[frameIndex];
}

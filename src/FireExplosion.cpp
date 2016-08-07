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

FireExplosion::FireExplosion(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr, float x, float y) :
	Effect(x, y),
	glowFadeTimer(0)
{
	spriteSheet.setTexture(mainTxtr);
	spriteSheet.setOrigin(29, 25);
	glow.setTexture(glowTxtr);
	glow.setColor(sf::Color(240, 240, 240));
	spriteSheet.setPosition(position.x, position.y);
	glow.setPosition(position.x - 225, position.y - 225);
}

void FireExplosion::update(const sf::Time & elapsedTime) {
	timer += elapsedTime.asMicroseconds();
	glowFadeTimer += elapsedTime.asMicroseconds();
	if (timer > 70000) {
		timer -= 70000;
		frameIndex++;
		if (frameIndex > 8) {
			frameIndex = 8;
			killFlag = true;
		}
	}
	uint8_t color = Easing::easeOut<1>(glowFadeTimer, static_cast<int64_t>(560000));
    glow.setColor(sf::Color(color, color, color, 255));
}

const Sprite & FireExplosion::getGlow() const {
	return glow;
}

const Sprite & FireExplosion::getSprite() const {
	return spriteSheet[frameIndex];
}

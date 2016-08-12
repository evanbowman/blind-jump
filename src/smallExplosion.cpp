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

#include "smallExplosion.hpp"

SmallExplosion::SmallExplosion(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr, float x, float y) :
	Effect(x, y),
	glowFadeTimer(0)
{
    spriteSheet.setTexture(mainTxtr);
	spriteSheet.setOrigin(18, 18);
	glow.setTexture(glowTxtr);
    glow.setColor(sf::Color(220, 220, 220));
	spriteSheet.setPosition(position.x, position.y);
	glow.setPosition(position.x - 225, position.y - 225);
}

void SmallExplosion::update(const sf::Time & elapsedTime) {
	timer += elapsedTime.asMicroseconds();
	glowFadeTimer += elapsedTime.asMicroseconds();
	if (timer > 60000) {
		timer -= 60000;
		frameIndex++;
		if (frameIndex > 5) {
			frameIndex = 5;
			killFlag = true;
		}
	}
	uint8_t color = Easing::easeOut<2>(glowFadeTimer, static_cast<int64_t>(300000)) * 230;
    glow.setColor(sf::Color(color, color, color, 255));
}

const sf::Sprite & SmallExplosion::getGlow() const {
	return glow;
}

const sf::Sprite & SmallExplosion::getSprite() const {
	return spriteSheet[frameIndex];
}

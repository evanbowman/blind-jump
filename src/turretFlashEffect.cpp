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

#include "turretFlashEffect.hpp"

TurretFlashEffect::TurretFlashEffect(const sf::Texture & txtr, float x, float y) : Effect(x, y) {
	spriteSheet.setTexture(txtr);
	bool select = std::abs(static_cast<int>(globalRNG())) % 2;
	if (select) {
		spriteSheet.setScale(-1.f, 1.f);
		xInit += 17;
	}
}

void TurretFlashEffect::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	timer += elapsedTime.asMilliseconds();
	if (timer > 40) {
		timer -= 40;
		frameIndex += 1;
		if (frameIndex > 4) {
			setKillFlag();
			frameIndex = 4;
		};
	}
	setPosition(xInit + xOffset, yInit + yOffset);
	spriteSheet.setPosition(position.x, position.y);
}

const Sprite & TurretFlashEffect::getSprite() const {
	return spriteSheet[frameIndex];
}

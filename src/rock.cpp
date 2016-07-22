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

#include "rock.hpp"

Rock::Rock(float _xInit, float _yInit, const sf::Texture & inpTxtr)
	: Detail{_xInit, _yInit}
{
	rockSheet.setTexture(inpTxtr);
    if (std::abs(static_cast<int>(globalRNG())) % 2) {
		rockSheet.setScale(-1, 1);
	    xInit += 32;
	}
	rockSheet[std::abs(static_cast<int>(globalRNG())) % 4];
}

void Rock::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	setPosition(xInit + xOffset, yInit + yOffset);
	rockSheet.setPosition(position.x, position.y);
}

const sf::Sprite & Rock::getSprite() const {
	return rockSheet.getSprite();
}

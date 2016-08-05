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

#include "treasureChest.hpp"
#include <cmath>

TreasureChest::TreasureChest(float _xInit, float _yInit, const sf::Texture & mainTxtr, char _item)
	: Detail{_xInit + (std::abs(static_cast<int>(globalRNG())) % 4) + -2, _yInit},
	  state{State::closed},
	  item{_item},
	  animationTimer{0},
	  frameIndex{0},
	  chestSheet{mainTxtr}
{
	chestShadow.setTexture(mainTxtr);
	chestShadow.setTextureRect(sf::IntRect(18, 107, 16, 8));
}

const sf::Sprite & TreasureChest::getShadow() const {
	return chestShadow;
}

const sf::Sprite & TreasureChest::getSprite() const {
	return chestSheet[frameIndex];
}

void TreasureChest::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	setPosition(xInit + xOffset, yInit + yOffset);
	chestSheet.setPosition(position.x, position.y - 16);
	chestShadow.setPosition(position.x, position.y + 12);

	switch (state) {
	case State::opening:
		animationTimer += elapsedTime.asMicroseconds();
		if (animationTimer > 50000) {
			animationTimer -= 50000;
			frameIndex++;
			if (frameIndex > 5) {
				frameIndex = 4;
				state = State::ready;
			}
		}
		break;

	default:
		break;
	}
}

char TreasureChest::getItem() const {
	return item;
}

TreasureChest::State TreasureChest::getState() const {
	return state;
}

void TreasureChest::setState(const TreasureChest::State _state) {
	state = _state;
}

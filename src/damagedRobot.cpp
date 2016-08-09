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

#include "damagedRobot.hpp"

DamagedRobot::DamagedRobot(float _xInit, float _yInit, const sf::Texture & inpTxtr)
	: Detail{_xInit, _yInit}, robotSheet{inpTxtr}
{
	robotSheet[std::abs(static_cast<int>(globalRNG())) % 2]; // Randomly pick one of the textures...
	robotSheet.setPosition(position.x, position.y);
}

void DamagedRobot::update(const sf::Time &) {
	// ...
}

const sf::Sprite & DamagedRobot::getSprite() const {
	return robotSheet.getSprite();
}

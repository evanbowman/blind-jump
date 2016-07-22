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

#include "IntroDoor.hpp"
#include <cmath>
#include "screenShakeController.hpp"

IntroDoor::IntroDoor(float _xInit, float _yInit, const sf::Texture & inpTxtr)
	: Detail{_xInit, _yInit},
	  doorSheet{inpTxtr},
	  frameIndex{0}/
	  timer{0},
	  state{State::dormant}
{}
 
bool checkBulletCollision(float xPos, float yPos, EffectGroup & ef) {
	for (auto & element : ef.getBulletLayer1()) {
		if (std::abs(element.getXpos() - xPos) < 4 && std::abs(element.getYpos() - yPos) < 4) {
			element.setKillFlag();
			return true;
		}
	}
	return false;
}

void IntroDoor::_update(float xOffset, float yOffset, ScreenShakeController * pscr, EffectGroup & ef, const sf::Time & elapsedTime) {
	switch (state) {
		case State::dormant:
		    if (checkBulletCollision(xOffset + xInit + 124, yPos + 62, ef)) {
				state = State::opening;
			}
			break;
			
		case State::opening:
			timer += elapsedTime.asMilliseconds();
			if (timer > 52) {
				timer -= 52;
				frameIndex++;
				if (frameIndex > 3) {
					frameIndex = 3;
					state = State::opened;
					pscr->rumble();
				}
			}
			break;
			
		case State::opened:
			// Does nothing
			break;
	}
    
	yPos = yOffset + yInit;
	doorSheet.setPosition(xOffset + xInit, yPos);
}

const sf::Sprite & IntroDoor::getSprite() const {
	return doorSheet[frameIndex];
}

void IntroDoor::update(float xOffset, float yOffset, const sf::Time &) {
	setPosition(xInit + xOffset, yInit + yOffset);
	doorSheet.setPosition(position.x, position.y);
}

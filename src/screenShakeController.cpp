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

#include "screenShakeController.hpp"

ScreenShakeController::ScreenShakeController() {
	active = false;
	timer = 0;
	shakeIndex = 0;
	shakeMode = 0;
}

void ScreenShakeController::update(Player & p, const sf::Time & elapsedTime) {
	if (!active) {
		return;
	} else {
		switch (shakeMode) {
			case 0:
				timer += elapsedTime.asMicroseconds();
				if (timer > 50000) {
					timer = 0;
					p.setPosition(p.getXpos(), p.getYpos() + shakeArray[shakeIndex]);
					p.setWorldOffsetY(p.getWorldOffsetY() + shakeArray[shakeIndex]);
					shakeIndex++;
				}
				if (shakeIndex > 5) {
					shakeIndex = 0;
					active = false;
				}
				break;
				
			case 1:
				timer += elapsedTime.asMicroseconds();
				if (timer > 50000) {
					timer = 0;
					p.setPosition(p.getXpos(), p.getYpos() + shakeArray2[shakeIndex]);
					p.setWorldOffsetY(p.getWorldOffsetY() + shakeArray2[shakeIndex]);
					shakeIndex++;
				}
				if (shakeIndex > 4) {
					shakeIndex = 0;
					active = false;
				}
				break;
				
			
			default:
				break;
		}
	}
}

void ScreenShakeController::shake() {
	if (!active) {
		active = true;
		shakeMode = 0;
	}
}

void ScreenShakeController::rumble() {
	if (!active) {
		active = true;
		shakeMode = 1;
	}
}


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

#pragma once
#ifndef screenShakeController_hpp
#define screenShakeController_hpp

#include "player.hpp"

class ScreenShakeController {
public:
	ScreenShakeController();
	void update(Player&);
	void shake();
	void rumble();
	
private:
	bool active;
	const char shakeArray[6] = {4, -8, 6, -4, 3, -1};
	const char shakeArray2[5] = {3, -5, 3, -2, 1};
	char shakeMode;
	unsigned char shakeIndex;
	unsigned char updateCounter;
};

#endif /* screenShakeController_hpp */

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

#include <stdint.h>

class wall {
private:
	float xPosInitial, yPosInitial,  xPos, yPos;

public:
	float getPosX() const;
	float getPosY() const;
	
	inline int8_t getWidth() const {
		return 32;
	}

	inline int8_t getHeight() const {
		return 26;
	}

	wall();
	void setPosition(float, float);
	void setYinit(float);
	void setXinit(float);
	float getXinit() const;
	float getYinit() const;
};

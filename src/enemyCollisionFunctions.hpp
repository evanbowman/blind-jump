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
#ifndef enemyCollisionFunctions_hpp
#define enemyCollisionFunctions_hpp

#include "wall.hpp"

// Simple bounding box collision checking
inline void checkCollision(std::vector<wall> walls, bool& CollisionDown, bool& CollisionUp, bool& CollisionRight, bool& CollisionLeft, float posY, float posX) {
	bool foundCollision[4] = {0, 0, 0, 0};
	for (int i = 0; i < walls.size(); i++) {
		
		if ((posX + 6 < (walls[i].getPosX() + walls[i].width) && (posX + 6 > (walls[i].getPosX()))) && (fabs((posY + 16) - walls[i].getPosY()) <= 13) && foundCollision[0] == 0)  {
			CollisionLeft =  1;
			foundCollision[0] = 1;
		}
		
		if ((posX + 24 > (walls[i].getPosX()) && (posX + 24 < (walls[i].getPosX() + walls[i].width))) && (fabs((posY + 16) - walls[i].getPosY()) <= 13) && foundCollision[1] == 0)  {
			CollisionRight =  1;
			foundCollision[1] = 1;
		}
		
		if (((posY + 22 < (walls[i].getPosY() + walls[i].height)) && (posY + 22 > (walls[i].getPosY()))) && (fabs((posX) - walls[i].getPosX()) <= 16) && foundCollision[2] == 0)  {
			CollisionUp =  1;
			foundCollision[2] = 1;
		}
		
		if (((posY + 36 > walls[i].getPosY()) && (posY + 36 < walls[i].getPosY() + walls[i].height)) && (fabs((posX) - walls[i].getPosX()) <= 16) && foundCollision[3] == 0)  {
			CollisionDown =  1;
			foundCollision[3] = 1;
		}
	}
}

#endif /* enemyCollisionFunctions_hpp */

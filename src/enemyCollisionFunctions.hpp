//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

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

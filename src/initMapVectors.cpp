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

#include "initMapVectors.hpp"
#include <cmath>
#include "tileController.hpp"

void initMapVectors(tileController * pTiles) {
	
	// First pick points for the hero character and level exit, to make sure not to place any objects on the critical path
	int playerX, playerY, transporterX, transporterY;

	wall w;
	
	do {
		transporterX = std::abs(static_cast<int>(globalRNG())) % 55;
		transporterY = std::abs(static_cast<int>(globalRNG())) % 55;
	} while ((pTiles->mapArray[transporterX][transporterY] != 4));
	
	pTiles->teleporterLocation.x = transporterX;
	pTiles->teleporterLocation.y = transporterY;

	
	//int count;
	for (int i = 0; i < 61; i++) {
		for (int j = 0; j < 61; j++) {
			if (pTiles->mapArray[i][j] == 3 || pTiles->mapArray[i][j] == 4 || pTiles->mapArray[i][j] == 11) {				 //This function checks the case for each map element, and pushes back the correct sprites and positions
				// Create a new coordinate structure holding the ordered pair set (i,j)
				Coordinate c1;
				c1.x = i;
				c1.y = j;
				// Assign coordinate priority based on distance from the transporter (and possibly items, tbd)
				c1.priority = sqrtf((i - transporterX) * (i - transporterX) + (j - transporterY) * (j - transporterY));
				pTiles->emptyMapLocations.push_back(c1);
			

			}
			
			else if (pTiles->mapArray[i][j] == 5 || pTiles->mapArray[i][j] == 8) {
				Coordinate c1;
				c1.x = i;
				c1.y = j;
				pTiles->edgeLocations.push_back(c1);
			}
			
			else if (pTiles->mapArray[i][j] == 2 || pTiles->mapArray[i][j] == 9) {
					//Set the wall's x position
				    w.setXinit((i * 32));
					w.setYinit((j * 26));
					w.setPosition(w.getXinit(), w.getYinit());
					//Push it back
					pTiles->walls.push_back(w);
			}
			
			else if (pTiles->mapArray[i][j] == 6 || pTiles->mapArray[i][j] == 10) {
					//Set the wall's x position
				    w.setXinit((i * 32));
				    w.setYinit((j * 26));
					w.setPosition(w.getXinit(), w.getYinit());
					//Push it back
					pTiles->walls.push_back(w);
			}
				
			else if (pTiles->mapArray[i][j] == 1) {		 //If the array index corresponds to a wall
					//Set the wall's position
				    w.setXinit((i * 32));
				    w.setYinit((j * 26));
				    w.setPosition(w.getXinit(), w.getYinit());
					//Push it back
					pTiles->walls.push_back(w);
			}
			
		}
	}
	// Sort the empty location vector based on coordinate priorities
	std::sort(pTiles->emptyMapLocations.begin(), pTiles->emptyMapLocations.end(), [](const Coordinate c1, const Coordinate c2) {return c1.priority < c2.priority;});
	playerX = pTiles->emptyMapLocations.back().x;
	playerY = pTiles->emptyMapLocations.back().y;
	
	pTiles->posX = -(32 * playerX);
	pTiles->posY = -(26 * playerY) - 4;
	
	// Remove that location from the vector
	pTiles->emptyMapLocations.pop_back();
}

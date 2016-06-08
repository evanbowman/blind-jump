//
//  initMapVectors.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "initMapVectors.hpp"
#include <iostream>
#include <cmath>
#include "tileController.hpp"

void initMapVectors(tileController * pTiles, int level) {
	
	// First pick points for the hero character and level exit, to make sure not to place any objects on the critical path
	int playerX, playerY, transporterX, transporterY;

	wall w;
	
	do {
		transporterX = rand() % 55;
		transporterY = rand() % 55;
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
	
	// Put the player as far away from the transporter as possible
	if (level != 10) {
		playerX = pTiles->emptyMapLocations.back().x;
		playerY = pTiles->emptyMapLocations.back().y;
	}
	
	else {
		playerX = 36;
		playerY = 31;
	}
	
	pTiles->posX = -(32 * playerX);
	pTiles->posY = -(26 * playerY) - 4;
	
	// Remove that location from the vector
	pTiles->emptyMapLocations.pop_back();
}

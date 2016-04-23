//
//  initMapVectors.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "initMapVectors.hpp"
#include "aStar.cpp"
#include <iostream>


// Counts the number of neighboring elements for a map location
int countNeighbors(short mapArray[61][61], int xIndex, int yIndex, char desiredNum1, char desiredNum2) {
    int count = 0;
    
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            // If match exists
            if (mapArray[xIndex + i][yIndex + j] == desiredNum1 || mapArray[xIndex + i][yIndex + j] == desiredNum2) {
                // Increment count
                count++;
            }
        }
    }
    
    return count;
}

bool checkCritical(std::vector<aStrCoordinate>& path, int x, int y) {
    for (auto element : path) {
        if (element.x == x || element.y == y) {
            return true;
        }
    }
    
    return false;
}

void initMapVectors(short mapArray[61][61], wall w, std::vector<wall>& walls, float& posX, float& posY, std::vector<Coordinate>& emptyLocations, std::vector<Coordinate>& largeEmptyLocations, std::vector<Coordinate>& edgeLocations, std::vector<Coordinate>& chestLocations, Coordinate& transporterLocation, char itemArray[48][3], int level) {
    
    // First pick points for the hero character and level exit, to make sure not to place any objects on the critical path
    int playerX, playerY, transporterX, transporterY;
    
    do {
        transporterX = rand() % 55;
        transporterY = rand() % 55;
    } while ((mapArray[transporterX][transporterY] != 4));
    
    transporterLocation.x = transporterX;
    transporterLocation.y = transporterY;

    
    //int count;
    for (int i = 0; i < 61; i++) {
        for (int j = 0; j < 61; j++) {
            if (mapArray[i][j] == 3 || mapArray[i][j] == 4 || mapArray[i][j] == 11) {                 //This function checks the case for each map element, and pushes back the correct sprites and positions
                // Create a new coordinate structure holding the ordered pair set (i,j)
                Coordinate c1;
                c1.x = i;
                c1.y = j;
                //count = countNeighbors(mapArray, i, j, 3, 4);
                //count += countNeighbors(mapArray, i, j, 8, 8);
                // Assign coordinate priority based on distance from the transporter (and possibly items, tbd)
                c1.priority = sqrtf((i - transporterX) * (i - transporterX) + (j - transporterY) * (j - transporterY));
                emptyLocations.push_back(c1);
            
                if ((mapArray[i - 1][j - 1] == 3 || mapArray[i - 1][j - 1] == 4) &&
                    (mapArray[i - 1][j] == 3 || mapArray[i - 1][j] == 4) &&
                    (mapArray[i - 1][j + 1] == 3 || mapArray[i - 1][j + 1] == 4) &&
                    (mapArray[i][j - 1] == 3 || mapArray[i][j - 1] == 4) &&
                    (mapArray[i][j + 1] == 3 || mapArray[i - 1][j + 1] == 4) &&
                    (mapArray[i + 1][j - 1] == 3 || mapArray[i + 1][j - 1] == 4) &&
                    (mapArray[i + 1][j] == 3 || mapArray[i + 1][j] == 4) &&
                    (mapArray[i + 1][j + 1] == 3 || mapArray[i + 1][j + 1] == 4)) {
                        largeEmptyLocations.push_back(c1);
                }

            }
            
            else if (mapArray[i][j] == 5 || mapArray[i][j] == 8) {
                Coordinate c1;
                c1.x = i;
                c1.y = j;
                edgeLocations.push_back(c1);
            }
            
            else if (mapArray[i][j] == 2 || mapArray[i][j] == 9) {
                    //Set the wall's x position
                    w.setXinit((i * 32));
                    w.setYinit((j * 26));
                    w.setPosition(w.getXinit(), w.getYinit());
                    //Push it back
                    walls.push_back(w);
            }
            
            else if (mapArray[i][j] == 6 || mapArray[i][j] == 10) {
                    //Set the wall's x position
                    w.setXinit((i * 32));
                    w.setYinit((j * 26));
                    w.setPosition(w.getXinit(), w.getYinit());
                    //Push it back
                    walls.push_back(w);
            }
                
            else if (mapArray[i][j] == 1) {         //If the array index corresponds to a wall
                    //Set the wall's position
                    w.setXinit((i * 32));
                    w.setYinit((j * 26));
                    w.setPosition(w.getXinit(), w.getYinit());
                    //Push it back
                    walls.push_back(w);
            }
            
        }
    }
    // Sort the empty location vector based on coordinate priorities
    std::sort(emptyLocations.begin(), emptyLocations.end(), [](const Coordinate c1, const Coordinate c2) {return c1.priority < c2.priority;});
    
    // Put the player as far away from the transporter as possible
    if (level != 10) {
        playerX = emptyLocations.back().x;
        playerY = emptyLocations.back().y;
    }
    
    else {
        playerX = 36;
        playerY = 31;
    }
    
    posX = -(32 * playerX);
    posY = -(26 * playerY) - 4;
    
    // Remove that location from the vector
    emptyLocations.pop_back();
}

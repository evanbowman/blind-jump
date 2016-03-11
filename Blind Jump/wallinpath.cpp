//
//  wallinpath.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/29/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "wallinpath.hpp"

bool checkWallCollision(std::vector<wall> w, float collisionRadius, float xPos, float yPos) {
    for (auto & element : w) {
        if ((xPos + 6 < (element.getPosX() + element.width) && (xPos + 6 > (element.getPosX()))) && (fabs((yPos + 16) - element.getPosY()) <= 13))  {
            return true;
        }
        
        if ((xPos + 24 > (element.getPosX()) && (xPos + 24 < (element.getPosX() + element.width))) && (fabs((yPos + 16) - element.getPosY()) <= 13))  {
            return true;
        }
        
        if (((yPos + 22 < (element.getPosY() + element.height)) && (yPos + 22 > (element.getPosY()))) && (fabs((xPos) - element.getPosX()) <= 16))  {
            return true;
        }
        
        if (((yPos + 36 > element.getPosY()) && (yPos + 36 < element.getPosY() + element.height)) && (fabs((xPos) - element.getPosX()) <= 16))  {
            return true;
        }
    }
    return false;
}

// Function to check whether there is a wall in the enemy's path
bool wallInPath(std::vector<wall> w, float dir, float xPos, float yPos) {
    for (auto i = 10; i < 100; i += 16) {
        if (checkWallCollision(w, 0, xPos + cos(dir) * i, yPos + sin(dir) * i)) {
            return true;
        }
    }
    return false;
}
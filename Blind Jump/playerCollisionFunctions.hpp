//
//  playerCollisionFunctions.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 11/14/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef playerCollisionFunctions_hpp
#define playerCollisionFunctions_hpp

#include <stdio.h>
#include "wall.hpp"
#include "treasureChest.hpp"
#include "terminal.hpp"

inline void checkCollisionWall(std::vector<wall> walls, bool& CollisionDown, bool& CollisionUp, bool& CollisionRight, bool& CollisionLeft, float posY, float posX) {
    bool foundCollision[4] = {0, 0, 0, 0};
    for (int i = 0; i < walls.size(); i++) {
        //if (walls[i].isInsideWindow()) {
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
    //}
    }
}

inline void checkCollisionChest (std::vector<TreasureChest> chests, bool& CollisionDown, bool& CollisionUp, bool& CollisionRight, bool& CollisionLeft, float posY, float posX) {
    bool foundCollision[4] = {0, 0, 0, 0};
    for (int i = 0; i < chests.size(); i++) {
        if ((posX + 6 < (chests[i].getxPos() + 16) && (posX + 6 > (chests[i].getxPos()))) && (fabs((posY + 16) - chests[i].getyPos()) <= 8) && foundCollision[0] == 0)  {
            CollisionLeft =  1;
            foundCollision[0] = 1;
        }
        
        if ((posX + 24 > (chests[i].getxPos()) && (posX + 24 < (chests[i].getxPos() + 16))) && (fabs((posY + 16) - chests[i].getyPos()) <= 8) && foundCollision[1] == 0)  {
            CollisionRight =  1;
            foundCollision[1] = 1;
        }
        
        if (((posY + 22 < (chests[i].getyPos() + 16)) && (posY + 22 > (chests[i].getyPos()))) && (fabs((posX) - chests[i].getxPos() + 6) <= 12) && foundCollision[2] == 0)  {
            CollisionUp =  1;
            foundCollision[2] = 1;
        }
        
        if (((posY + 36 > chests[i].getyPos()) && (posY + 36 < chests[i].getyPos() + 16)) && (fabs((posX) - chests[i].getxPos() + 6) <= 12) && foundCollision[3] == 0)  {
            CollisionDown =  1;
            foundCollision[3] = 1;
        }
    }
}

inline void checkCollisionTerminal (std::vector<Terminal> terms, bool& CollisionDown, bool& CollisionUp, bool& CollisionRight, bool& CollisionLeft, float posY, float posX) {
    bool foundCollision[4] = {0, 0, 0, 0};
    for (int i = 0; i < terms.size(); i++) {
        if ((posX + 6 < (terms[i].getxPos() + 16) && (posX + 6 > (terms[i].getxPos()))) && (fabs((posY + 16) - terms[i].getyPos()) <= 8) && foundCollision[0] == 0)  {
            CollisionLeft =  1;
            foundCollision[0] = 1;
        }
        
        if ((posX + 24 > (terms[i].getxPos()) && (posX + 24 < (terms[i].getxPos() + 16))) && (fabs((posY + 16) - terms[i].getyPos()) <= 8) && foundCollision[1] == 0)  {
            CollisionRight =  1;
            foundCollision[1] = 1;
        }
        
        if (((posY + 22 < (terms[i].getyPos() + 16)) && (posY + 22 > (terms[i].getyPos()))) && (fabs((posX) - terms[i].getxPos() + 6) <= 12) && foundCollision[2] == 0)  {
            CollisionUp =  1;
            foundCollision[2] = 1;
        }
        
        if (((posY + 36 > terms[i].getyPos()) && (posY + 36 < terms[i].getyPos() + 16)) && (fabs((posX) - terms[i].getxPos() + 6) <= 12) && foundCollision[3] == 0)  {
            CollisionDown =  1;
            foundCollision[3] = 1;
        }
    }
}

#endif /* playerCollisionFunctions_hpp */

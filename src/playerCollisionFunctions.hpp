//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "DetailGroup.hpp"
#include "wall.hpp"
#include <cmath>

inline uint_fast8_t checkCollisionWall(std::vector<wall> & walls, float posY,
                                       float posX) {
    uint_fast8_t collisionMask = 0;
    for (auto & wall : walls) {
        if ((posX + 6 < (wall.getPosX() + wall.getWidth()) &&
             (posX + 6 > (wall.getPosX()))) &&
            (fabs((posY + 16) - wall.getPosY()) <= 13)) {
            collisionMask |= 0x01;
        }
        if ((posX + 24 > (wall.getPosX()) &&
             (posX + 24 < (wall.getPosX() + wall.getWidth()))) &&
            (fabs((posY + 16) - wall.getPosY()) <= 13)) {
            collisionMask |= 0x02;
        }
        if (((posY + 22 < (wall.getPosY() + wall.getHeight())) &&
             (posY + 22 > (wall.getPosY()))) &&
            (fabs((posX)-wall.getPosX()) <= 16)) {
            collisionMask |= 0x04;
        }
        if (((posY + 36 > wall.getPosY()) &&
             (posY + 36 < wall.getPosY() + wall.getHeight())) &&
            (fabs((posX)-wall.getPosX()) <= 16)) {
            collisionMask |= 0x08;
        }
    }
    return collisionMask;
}

inline uint_fast8_t
checkCollisionChest(std::vector<std::shared_ptr<TreasureChest>> & chests,
                    float posY, float posX) {
    uint_fast8_t collisionMask = 0;
    for (auto & sharedChest : chests) {
        auto chestPosition = sharedChest.get()->getPosition();
        if ((posX + 6 < (chestPosition.x + 16) &&
             (posX + 6 > (chestPosition.x))) &&
            (fabs((posY + 16) - chestPosition.y) <= 8)) {
            collisionMask |= 0x01;
        }
        if ((posX + 24 > (chestPosition.x) &&
             (posX + 24 < (chestPosition.x + 16))) &&
            (fabs((posY + 16) - chestPosition.y) <= 8)) {
            collisionMask |= 0x02;
        }
        if (((posY + 22 < (chestPosition.y + 16)) &&
             (posY + 22 > (chestPosition.y))) &&
            (fabs((posX)-chestPosition.x + 6) <= 12)) {
            collisionMask |= 0x04;
        }
        if (((posY + 36 > chestPosition.y) &&
             (posY + 36 < chestPosition.y + 16)) &&
            (fabs((posX)-chestPosition.x + 6) <= 12)) {
            collisionMask |= 0x08;
        }
    }
    return collisionMask;
}

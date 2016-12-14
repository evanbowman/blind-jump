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

inline uint_fast8_t checkCollisionChest(std::vector<TreasureChest> chests,
                                        float posY, float posX) {
    uint_fast8_t collisionMask = 0;
    for (auto & chest : chests) {
        if ((posX + 6 < (chest.getPosition().x + 16) &&
             (posX + 6 > (chest.getPosition().x))) &&
            (fabs((posY + 16) - chest.getPosition().y) <= 8)) {
            collisionMask |= 0x01;
        }

        if ((posX + 24 > (chest.getPosition().x) &&
             (posX + 24 < (chest.getPosition().x + 16))) &&
            (fabs((posY + 16) - chest.getPosition().y) <= 8)) {
            collisionMask |= 0x02;
        }

        if (((posY + 22 < (chest.getPosition().y + 16)) &&
             (posY + 22 > (chest.getPosition().y))) &&
            (fabs((posX)-chest.getPosition().x + 6) <= 12)) {
            collisionMask |= 0x04;
        }

        if (((posY + 36 > chest.getPosition().y) &&
             (posY + 36 < chest.getPosition().y + 16)) &&
            (fabs((posX)-chest.getPosition().x + 6) <= 12)) {
            collisionMask |= 0x08;
        }
    }
    return collisionMask;
}

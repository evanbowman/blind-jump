//
//  playerCollisions.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/12/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "playerCollisions.hpp"
#include "player.hpp"
#include "wall.hpp"

bool collisionLeft(double xpos, wall& w) {
    if (((xpos - 1) <= (w.xPos + 15)) && ((xpos - 1) > w.xPos)) {
        return 1;
    }
    return 0;
}

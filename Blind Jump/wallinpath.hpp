//
//  wallinpath.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/29/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef wallinpath_hpp
#define wallinpath_hpp

#include <stdio.h>
#include <vector>
#include "wall.hpp"
#include <cmath>

bool checkWallCollision(std::vector<wall>, float, float, float);

// Function to check whether there is a wall in the enemy's path
bool wallInPath(std::vector<wall>, float, float, float);

#endif /* wallinpath_hpp */

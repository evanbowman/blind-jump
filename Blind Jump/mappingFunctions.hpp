//
//  mapingFunctions.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/15/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef mappingFunctions_hpp
#define mappingFunctions_hpp

#include <stdio.h>
#include "building.hpp"
#include "tileController.hpp"

#define BOSS_LEVEL_1 10

int mappingFunction(short map[61][61], int level);
Building addHouse(short map[61][61], tileController&);


#endif /* mappingFunctions_hpp */

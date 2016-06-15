//
//  enemyCreationFunctions.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/19/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef enemyCreationFunctions_hpp
#define enemyCreationFunctions_hpp

#include <stdio.h>
#include "enemyController.hpp"
#include "coordinate.h"

void addTurret(short mapArray[61][61], short descriptionArray[61][61], enemyController&, float, float, float, float, std::vector<Coordinate>&);
void addCritter(short mapArray[61][61], short descriptionArray[61][61], enemyController&, float, float, float, float, std::vector<Coordinate>&, int);
void addDasher(short mapArray[61][61], short descriptionArray[61][61], enemyController&, float, float, float, float, std::vector<Coordinate>&);

#endif /* enemyCreationFunctions_hpp */

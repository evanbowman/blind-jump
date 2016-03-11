//
//  building.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/25/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "building.hpp"



// Destructor deletes all the textures associated with it
Building::~Building() {
    delete [] floors;
}
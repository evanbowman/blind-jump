//
//  building.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/25/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef building_hpp
#define building_hpp

#include <stdio.h>
#include "sfml/graphics.hpp"

class Building {
public:
    Building(sf::Image*);
    ~Building();
    
private:
    sf::Texture* floors;
};

#endif /* building_hpp */

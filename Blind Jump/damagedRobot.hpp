//
//  damagedRobot.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/5/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef damagedRobot_hpp
#define damagedRobot_hpp

#include <stdio.h>
#include "detailParent.hpp"
#include "SFML/graphics.hpp"

class DamagedRobot : public detailParent {
public:
    DamagedRobot(float, float, sf::Sprite*, int, float, float);
    void update(float, float);
    sf::Sprite* getSprite();
    
private:
    sf::Sprite sprite;
    
};

#endif /* damagedRobot_hpp */

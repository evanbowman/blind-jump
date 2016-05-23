//
//  energyCube.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/28/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef terminal_hpp
#define terminal_hpp

#include <stdio.h>
#include "detailParent.hpp"

class Terminal : public detailParent {
    
public:
    Terminal(float, float, sf::Sprite*, int, float, float);
    sf::Sprite* getSprite();
    sf::Sprite* getShadow();
    void update(float, float);
    
private:
    bool currentframe;
    sf::Sprite termSprites[3];
};

#endif /* energyCube_hpp */

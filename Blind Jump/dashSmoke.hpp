//
//  dashSmoke.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/18/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef dashSmoke_hpp
#define dashSmoke_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"

class DashSmoke {
private:
    sf::Sprite sprites[8];
    float xInit, yInit, xPos, yPos;
    bool killFlag;
    char frameIndex;
    unsigned int frameTimer;
    
public:
    DashSmoke(sf::Sprite*, float, float, int, int);
    void update(float, float, sf::Time &);
    sf::Sprite getSprite();
    bool getKillFlag();
    float getYpos();
};

#endif /* dashSmoke_hpp */

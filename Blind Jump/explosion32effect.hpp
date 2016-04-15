//
//  explosion32effect.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 11/7/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef explosion32effect_hpp
#define explosion32effect_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"

class Explosion32effect {
public:
    Explosion32effect(sf::Sprite[6], float, float);
    float xPos;
    float yPos;
    float xInit;
    float yInit;
    void positionUpdateF(float, float);
    sf::Sprite getSprite();
    char spriteIndex;
    char animationCounter;
    bool imFinished;
    char animationLength;
    sf::Sprite sprExp[6];
    float getXpos();
    float getYpos();
};

#endif /* shotPuff_hpp */

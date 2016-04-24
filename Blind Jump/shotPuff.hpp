//
//  shotPoof.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/14/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef shotPuff_hpp
#define shotPuff_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <cmath>

class shotPuff {
public:
    shotPuff(sf::Sprite[4], float, float, char, int);
    float xPos;
    float yPos;
    float xInit;
    float yInit;
    void update(float, float);
    sf::Sprite getSprite();
    char spriteIndex;
    char animationCounter;
    bool imFinished;
    char animationLength;
    bool getKillFlag();
    float getYpos();
    
private:
    sf::Sprite sprPuff[4];
    sf::Texture sprText[4];
};
#endif /* shotPuff_hpp */

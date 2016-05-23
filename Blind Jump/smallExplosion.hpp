//
//  smallExplosion.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/19/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef smallExplosion_hpp
#define smallExplosion_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"

class SmallExplosion {
private:
    sf::Sprite sprites[9];
    sf::Sprite glow;
    float xInit, yInit, xPos, yPos;
    bool killFlag;
    char frameIndex, frameRate;
    
    
public:
    SmallExplosion(sf::Sprite*, sf::Sprite, float, float);
    void update(float, float, sf::Time &);
    sf::Sprite getSprite();
    bool getKillFlag();
    float getYpos();
    sf::Sprite* getGlow();
};

#endif /* smallExplosion_hpp */

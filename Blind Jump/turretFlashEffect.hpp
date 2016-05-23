//
//  turretFlashEffect.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef turretFlashEffect_hpp
#define turretFlashEffect_hpp

#include <stdio.h>
#include "SFML/graphics.hpp"

class turretFlashEffect {
private:
    float xPos;
    float yPos;
    float xInit;
    float yInit;
    sf::Sprite flashSprites[5];
    sf::Clock clock;
    bool killFlag;
    
public:
    void update(float, float);
    char imageIndex;
    turretFlashEffect(sf::Sprite sprites[5], float, float);
    float getYpos();
    bool getKillFlag();
    sf::Sprite getSprite();
};
#endif /* turretFlashEffect_hpp */

//
//  turretFlashEffect.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef turretFlashEffect_hpp
#define turretFlashEffect_hpp

#include <stdio.h>
#include "SFML/graphics.hpp"

class turretFlashEffect {
public:
    short timeout;
    float xPos;
    float yPos;
    float xInit;
    float yInit;
    sf::Sprite flashSprites[5];
    sf::Sprite getSprite();
    void update(float, float);
    char imageIndex;
    char frameLength;
    turretFlashEffect(sf::Sprite sprites[5], float, float);
};
#endif /* turretFlashEffect_hpp */

//
//  PowerupParticles.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 5/18/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef PowerupParticles_hpp
#define PowerupParticles_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"

class PowerupParticle {
private:
    sf::Sprite spr;
    
public:
    PowerupParticle(sf::Sprite &, float, float, float);
    void update(float, float, sf::Time &);
    float getYpos();
    sf::Sprite getSprite();
};

#endif /* PowerupParticles_hpp */

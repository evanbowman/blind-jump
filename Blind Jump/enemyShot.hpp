//
//  enemyShot.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/2/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef enemyShot_hpp
#define enemyShot_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"

class Enemyshot {
private:
    sf::Sprite sprites[2];
    float xPos;
    float yPos;
    float xInit;
    double yInit;
    unsigned char imageIndex;
    unsigned int frameTimer;
    unsigned int elapsedTime;
    float direction;
    bool killFlag;
    sf::Sprite glowSprite;
    
public:
    Enemyshot(sf::Sprite*, sf::Sprite, float, float, float);
    void update(float, float, sf::Time &);
    sf::Sprite getSprite();
    bool getKillFlag();
    void setKillFlag();
    float getXpos();
    float getYpos();
    sf::Sprite* getGlow();
};

#endif /* enemyShot_hpp */

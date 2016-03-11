//
//  bulletType1.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/14/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef bulletType1_hpp
#define bulletType1_hpp
#include <SFML/Graphics.hpp>

#include <stdio.h>


class bulletType1 {
private:
    unsigned short duration;
    sf::Sprite bulletSprite[2];
    char direction;
    float xPos;
    float yPos;
    float xInit;
    float yInit;
    bool killFlag;
    bool canPoof;
    
public:
    bulletType1(sf::Sprite s, sf::Sprite s2, char, float, float);
    sf::Sprite getSprite();
    sf::Sprite* getGlow();
    void update(float, float);
    bool getKillFlag();
    void setKillFlag();
    void setPosition(float, float);
    float getPosX();
    float getPosY();
    char getDirection();
    bool checkCanPoof();
    void disablePuff();
};

#endif /* bulletType1_hpp */

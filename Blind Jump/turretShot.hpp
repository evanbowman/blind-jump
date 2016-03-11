//
//  turretShot.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/26/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef turretShot_hpp
#define turretShot_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"

class turretShot {
public:
    turretShot(sf::Sprite*, sf::Sprite, float, float, float);
    unsigned short timeout;
    float xPos;
    float yPos;
    float xInit;
    float yInit;
    sf::Sprite sprs[2];
    sf::Sprite glowSprite;
    sf::Sprite* getGlow();
    sf::Sprite getSprite();
    void update(float, float);
    char imageIndex;
    char frameLength;
    float direction;
    bool killFlag;
    bool getKillFlag();
    void setKillFlag();
    float getXpos();
    float getYpos();
    void speedFactor(float);
    void enableTracking(float, float);
    float playerPosX;
    float playerPosY;
    
private:
    float scale;
    bool trackPlayer;
    int duration;
    char frameIndex;
    char frameRate;
    
};
#endif /* turretShot_hpp */

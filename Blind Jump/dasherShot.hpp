//
//  dasherShot.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/12/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef dasherShot_hpp
#define dasherShot_hpp

#include <stdio.h>
#include "sfml/graphics.hpp"

class DasherShot {
public:
    DasherShot(sf::Sprite*, sf::Sprite, float, float, float);
    unsigned short timeout;
    float xPos;
    float yPos;
    float xInit;
    float yInit;
    sf::Sprite sprs[2];
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
    float playerPosX;
    float playerPosY;
    bool frameIndex;
    bool driftSel;
    sf::Sprite* getGlow();
    
    
private:
    float scale;
    bool trackPlayer;
    sf::Sprite glowSprite;
};

#endif /* dasherShot_hpp */

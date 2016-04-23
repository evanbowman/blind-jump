//
//  turret.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/19/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef turret_hpp
#define turret_hpp

#include <stdio.h>
#include "SFML/graphics.hpp"
#include "turret.hpp"
#include "effectsController.hpp"

class turret {
private:
    double xPos;
    double yPos;
    double xInit;
    double yInit;
    double playerPosX;
    double playerPosY;
    char imageIndex;
    char spriteIndex;
    short disableCountdown;
    bool visibility;
    sf::Sprite turretSprites[10];
    //Set the duration between animation frame transitions
    char animationCount;
    bool active;
    int activateTimer;
    short shotCountdown;
    short shotsFired;
    double xOffset;
    double yOffset;
    float hp;
    bool killFlag;
    char colorCount;
    bool isColored;
    
public:
    turret(sf::Sprite spr[10]);
    void setPosition(double, double);
    sf::Sprite* getShadow();
    sf::Sprite* getSprite();
    void updateShots(effectsController&, FontController&);
    double getXinit();
    double getYinit();
    bool getKillFlag();
    void setInitPosition(double, double);
    double getPlayerPosX();
    double getPlayerPosY();
    void setPlayerPos(double, double);
    double getXpos();
    double getYpos();
    bool colored();
};

#endif /* turret_hpp */

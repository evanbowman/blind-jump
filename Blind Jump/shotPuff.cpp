//
//  shotPoof.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/14/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "shotPuff.hpp"

shotPuff::shotPuff(sf::Sprite sprIn[4], float x, float y, char dir, int p) {
    xPos = x;
    yPos = y;
    //Store all of the sprites for later
    for (int i = 0; i < 4; i++) {
        sprPuff[i] = sprIn[i];
    }
    spriteIndex = 0;
    animationCounter = 3;
    //A variable to tell the effect controller when to pop the effect
    imFinished = 0;
    xInit = x;
    yInit = y;
    animationLength = 4;
}

//Updates the position of the effect
void shotPuff::update(float xOffset, float yOffset) {
    xPos = xInit + xOffset;
    yPos = yInit + yOffset;
}

sf::Sprite shotPuff::getSprite() {
    if (--animationCounter == 0) {
        animationCounter = 3;
        spriteIndex += 1;
        if (spriteIndex == animationLength) {
            spriteIndex = 3;
            imFinished = 1;
        }
    }
    sprPuff[spriteIndex].setPosition(round(xPos), round(yPos));
    return sprPuff[spriteIndex];
}

bool shotPuff::getKillFlag() {
    return imFinished;
}

float shotPuff::getYpos() {
    return yPos;
}
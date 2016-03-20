//
//  dashSmoke.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/18/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "dashSmoke.hpp"

DashSmoke::DashSmoke(sf::Sprite* sprs, float x, float y, int dir, int scale) {
    for (int i = 0; i < 8; i++) {
        sprites[i] = sprs[i];
        sprites[i].setRotation(dir);
        if (scale != 1) {
            sprites[i].setScale(scale, 1);
            sprites[i].setOrigin(0, 0);
        }
    }
    xInit = x;
    yInit = y;
    killFlag = false;
    frameIndex = 0;
    frameRate = 4;
}

void DashSmoke::update(float xOffset, float yOffset) {
    xPos = xInit + xOffset;
    yPos = yInit + yOffset;
    if (--frameRate == 0) {
        frameRate = 4;
        frameIndex++;
        if (frameIndex > 7) {
            frameIndex = 7;
            killFlag = true;
        }
    }
    
    sprites[frameIndex].setPosition(xPos, yPos);
}

sf::Sprite DashSmoke::getSprite() {
    return sprites[frameIndex];
}

bool DashSmoke::getKillFlag() {
    return killFlag;
}

float DashSmoke::getYpos() {
    return yPos;
}
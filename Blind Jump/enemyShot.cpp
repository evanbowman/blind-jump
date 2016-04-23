//
//  enemyShot.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/2/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "enemyShot.hpp"
#include <cmath>

Enemyshot::Enemyshot(sf::Sprite* inpsprs, sf::Sprite glow, float x, float y, float dir) {
    xPos = 0;
    yPos = 0;
    xInit = x;
    yInit = y;
    imageIndex = 0;
    glowSprite = glow;
    frameLength = 12;
    timeout = 65;
    for (int i = 0; i < 2; i++) {
        sprites[i] = inpsprs[i];
    }
    direction = (dir - 270) * (3.14 / 180);
    killFlag = false;
}

void Enemyshot::update(float xOffset, float yOffset) {
    xPos = xInit + xOffset + 4.4 * (65 - timeout) * (cos(direction));         // Note: timeout starts at 60, so 60 - timout grows linearly with time
    yPos = yInit + 11 + yOffset + 4.4 * (65 - timeout) * (sin(direction));
    for (int i = 0; i < 2; i++) {
        sprites[i].setPosition(xPos, yPos);
    }
    
    glowSprite.setPosition(xPos, yPos + 18);
    
    if (--frameLength == 0) {
        frameLength = 12;
        if (imageIndex == 0) {
            imageIndex = 1;
        }
        else {
            imageIndex = 0;
        }
    }
    
    if (--timeout == 0) {
        killFlag = true;
    }
    
    float offset = rand() % 20;
    glowSprite.setColor(sf::Color(230 + offset, 230 + offset, 230 + offset, 255));

}

sf::Sprite* Enemyshot::getGlow() {
    return &glowSprite;
}

sf::Sprite Enemyshot::getSprite() {
    return sprites[imageIndex];
}

bool Enemyshot::getKillFlag() {
    return killFlag;
}

void Enemyshot::setKillFlag() {
    killFlag = true;
}

float Enemyshot::getXpos() {
    return xPos;
}

float Enemyshot::getYpos() {
    return yPos;
}

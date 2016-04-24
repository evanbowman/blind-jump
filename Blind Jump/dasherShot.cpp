//
//  dasherShot.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/12/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "dasherShot.hpp"

#include <cmath>

DasherShot::DasherShot(sf::Sprite* sprite, sf::Sprite glow, float x, float y, float dir) {
    for (int i = 0; i < 2; i++) {
        sprs[i] = sprite[i];
        sprs[i].setOrigin(4, 4);
    }
    glowSprite = glow;
    xPos = 0;
    yPos = 0;
    xInit = x;
    yInit = y;
    imageIndex = 0;
    frameLength = 2;
    timeout = 50;
    int diff = pow(-1,rand() % 2) + rand() % 6 - 3;
    direction = (dir - 270 + diff) * (3.14 / 180);     // I added 270 previously to get the sprite to face in the right direction, so subract it
    //back out and convert back to radians
    killFlag = false;
    scale = 5.8 + (0.8 * (rand() % 3));
    trackPlayer = false;
    frameIndex = false;
    frameLength = 4;
    driftSel = rand() % 2;
}

void DasherShot::update(float xOffset, float yOffset, sf::Time &) {
    xPos = xInit + xOffset + scale * (50 - timeout) * (cos(direction));         // Note: timeout starts at 60, so 60 - timout grows linearly with time
    yPos = yInit + 11 + yOffset + scale * (50 - timeout) * (sin(direction));
    sprs[0].setPosition(xPos, yPos);
    sprs[1].setPosition(xPos, yPos);
    glowSprite.setPosition(xPos, yPos + 18);
    if (--timeout == 0) {
        killFlag = true;
    }
    // Alternate between frames
    if (--frameLength == 0) {
        frameIndex = !frameIndex;
        frameLength = 4;
    }
    if (driftSel) {
        direction += 0.002;
    }
    else {
        direction -= 0.002;
    }
    scale *= 0.993;
    if (timeout < 10) {
        sf::Color c = glowSprite.getColor();
        c.r -= 10;
        c.b -= 10;
        c.g -= 10;
        glowSprite.setColor(c);
    }
}

sf::Sprite DasherShot::getSprite() {
    return sprs[frameIndex];
}

sf::Sprite* DasherShot::getGlow() {
    return &glowSprite;
}

bool DasherShot::getKillFlag() {
    return killFlag;
}

void DasherShot::setKillFlag() {
    killFlag = true;
}

float DasherShot::getXpos() {
    return xPos;
}

float DasherShot::getYpos() {
    return yPos;
}

void DasherShot::speedFactor(float factor) {
    scale = factor;
}

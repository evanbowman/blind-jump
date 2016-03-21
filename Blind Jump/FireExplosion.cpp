//
//  FireExplosion.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/18/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "FireExplosion.hpp"

FireExplosion::FireExplosion(sf::Sprite* sprs, sf::Sprite glow, float x, float y) {
    for (int i = 0; i < 9; i++) {
        sprites[i] = sprs[i];
        sprites[i].setOrigin(29, 25);
    }
    this->glow = glow;
    this->glow.setColor(sf::Color(240, 240, 240));
    xInit = x;
    yInit = y;
    killFlag = false;
    frameIndex = 0;
    speed = 4;
    frameRate = speed;
    valid = true;
}

void FireExplosion::update(float xOffset, float yOffset) {
    xPos = xInit + xOffset;
    yPos = yInit + yOffset;
    if (--frameRate == 0) {
        frameRate = speed;
        frameIndex++;
        if (frameIndex > 8) {
            frameIndex = 8;
            killFlag = true;
        }
    }
    sf::Color c = glow.getColor();
    if (c.r > 8) {
        c.r -= 8;
        c.g -= 8;
        c.b -= 8;
        glow.setColor(c);
    }
    sprites[frameIndex].setPosition(xPos, yPos);
    glow.setPosition(xPos - 225, yPos - 225);
}

void FireExplosion::setOrigin(int x, int y) {
    for (int i = 0; i < 9; i++) {
        sprites[i].setOrigin(x, y);
    }
}

sf::Sprite* FireExplosion::getGlow() {
    return &glow;
}

sf::Sprite FireExplosion::getSprite() {
    return sprites[frameIndex];
}

bool FireExplosion::getKillFlag() {
    return killFlag;
}

float FireExplosion::getYpos() {
    return yPos;
}

float FireExplosion::getXpos() {
    return xPos;
}

bool FireExplosion::isValid() {
    return valid;
}

void FireExplosion::invalidate() {
    valid = false;
}

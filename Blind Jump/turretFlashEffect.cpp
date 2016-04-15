//
//  turretFlashEffect.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "turretFlashEffect.hpp"

turretFlashEffect::turretFlashEffect(sf::Sprite sprites[5], float x, float y) {
    //Take all of the input sprites and save them for alter
    for (int i = 0; i < 5; i++) {
        flashSprites[i] = sprites[i];
    }
    xPos = 0;
    yPos = 0;
    xInit = x;
    yInit = y;
    imageIndex = 0;
    frameLength = 2;
    timeout = 10;
    bool select = rand() % 2;
    if (select) {
        for (int i = 0; i < 5; i++) {
            flashSprites[i].setScale(-1,-1);
        }
        yInit += 18;
        xInit += 17;
    }
}

//Update the position of the image
void turretFlashEffect::update(float xOffset, float yOffset) {
    //Why call two seperate functions when we can decrement the effect's timeout variable right here?
    --frameLength;
    --timeout;
    if (frameLength == 0) {
        imageIndex += 1;
        frameLength = 2;
    }
    xPos = xInit + xOffset;
    yPos = yInit + 11 + yOffset;
    for (int i = 0; i < 5; i++) {
        flashSprites[i].setPosition(xPos, yPos);
    }
}

//A funtion to return the current sprite
sf::Sprite turretFlashEffect::getSprite() {
    return flashSprites[imageIndex];
}

float turretFlashEffect::getYpos() {
    return yPos;
}
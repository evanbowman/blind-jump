//
//  treasureChest.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 11/14/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "treasureChest.hpp"
#include <cmath>

#define CHOICES 6

TreasureChest::TreasureChest(float xStart, float yStart, sf::Sprite* sprs, int len, float width, float height, char contents) : detailParent(xStart, yStart, sprs, len, width, height) {
    for (int i = 0; i < len; i++) {
        chestSprites[i] = sprs[i];
    }
    isOpen = false;
    animationIsRunning = false;
    frameIndex = 0;
    // Place the input contents in the chest
    item = contents;
    valid = true;
    animationTimer = 0;
}

sf::Sprite* TreasureChest::getShadow() {
    return &chestSprites[6];
}

void TreasureChest::update(float xOffset, float yOffset, char playerSpriteIndex, InputController* input, sf::Time & elapsedTime) {
    xPos = xOffset + xInit;
    yPos = yOffset + yInit;
    
    chestSprites[6].setPosition(xPos, yPos + 15);
    
    if (!isOpen) {
        if (input->zPressed() && fabsf(xPos + 8 - windowCenterX / 2) < 12 && fabsf(yPos - windowCenterY / 2) < 10 && playerSpriteIndex == 1) {
            animationIsRunning = true;
        }
    }
    
    if (animationIsRunning) {
        animationTimer += elapsedTime.asMilliseconds();
        if (animationTimer > 50) {
            animationTimer -= 50;
            frameIndex++;
        }
        if (frameIndex > 5) {
            frameIndex = 4;
            animationIsRunning = false;
            isOpen = true;
        }
    }
}

sf::Sprite* TreasureChest::getSprite() {
    chestSprites[frameIndex].setPosition(xPos, yPos - 11);
    return &chestSprites[frameIndex];
}

float TreasureChest::getZY() {
    return yPos - 12;
}

char TreasureChest::getFrameIndex() {
    return frameIndex;
}

bool TreasureChest::isValid() {
    return valid;
}

char TreasureChest::getItem() {
    valid = false;
    return item;
}

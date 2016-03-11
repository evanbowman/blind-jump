//
//  teleporterSmoke.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/1/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "teleporterSmoke.hpp"

#define ANIMATION_LENGTH 6

TeleporterSmoke::TeleporterSmoke(sf::Sprite inputSprites[6], float x, float y) {
    xPos = x;
    xInit = x;
    yPos = y;
    yInit = y;
    for (int i = 0; i < 6; i++) {
        effectSprites[i] = inputSprites[i];
    }
    // Initialize the current frame of the animation to the first one
    currentFrame = 0;
    // Set the duration for which each frame draws to the screen before switching to the next one
    animationCount = 7;
    // Initially, the boolean varaible denoting the end of the animation of course must be 0
    imFinished = false;
    // The smoke hasn't begun moving up yet, so initialize the drift variable that keeps track of motion to 0
    yDrift = 0;
    // Initialize the depth to 0
    drawOrder = 0;
}

void TeleporterSmoke::update(float xOffset, float yOffset) {
    xPos = xInit + xOffset;
    yPos = yInit + yOffset - yDrift;
    // Increment the drift variable, so the smoke moves up relative to its current position on the next frame
    yDrift += 0.6;
}

sf::Sprite TeleporterSmoke::getSprite() {
    if (--animationCount == 0) {
        animationCount = 6;
        currentFrame += 1;
        if (currentFrame > 2) {
            drawOrder = 1;
        }
        
        if (currentFrame == ANIMATION_LENGTH) {
            currentFrame = 5;
            imFinished = true;
        }
    }
    // Better to just update the sprite position when we need it, rather than updating six frames ever time the update function gets called!
    effectSprites[currentFrame].setPosition(xPos, yPos);
    // Return the desired frame:
    return effectSprites[currentFrame];
}

bool TeleporterSmoke::getKillFlag() {
    return imFinished;
}

float TeleporterSmoke::getPosX() {
    return xPos;
}

float TeleporterSmoke::getPosY() {
    return yPos;
}

char TeleporterSmoke::getDrawOrder() {
    return drawOrder;
}

//
//  Pillar.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/15/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "IntroDoor.hpp"
#include <cmath>
#include "screenShakeController.hpp"


IntroDoor::IntroDoor(float xStart, float yStart, sf::Sprite* inpSpr, int len, float width, float height) : detailParent(xStart, yStart, inpSpr, len, width / 2, height / 2) {
    for (int i = 0; i < 4; i++)
        sprite[i] = inpSpr[i];
    
    frameIndex = 0;
    frameRate = 3;
    state = dormant;
}

void IntroDoor::update(float xOffset, float yOffset, InputController * pInput, ScreenShakeController * pscr) {
    switch (state) {
        case dormant:
            // If the player presses the button by the door, go to the opening state
            if (pInput->zPressed() && fabsf(windowCenterX - (xPos + 130)) < 6 && fabsf(windowCenterY - (yPos + 70)) < 10) {
                state = opening;
            }
            break;
            
        case opening:
            if (--frameRate == 0) {
                frameIndex++;
                frameRate = 3;
                if (frameIndex > 3) {
                    frameIndex = 3;
                    state = opened;
                    pscr->rumble();
                }
            }
            break;
            
        case opened:
            // Does nothing
            break;
            
        default:
            break;
    }
    
    xPos = xOffset + xInit;
    yPos = yOffset + yInit;
}

sf::Sprite * IntroDoor::getSprite() {
    sprite[frameIndex].setPosition(xPos, yPos);
    return &sprite[frameIndex];
}

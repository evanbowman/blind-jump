//
//  Caption.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 4/16/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "Caption.hpp"
#include <cmath>

Caption::Caption(float xInit, float yInit, sf::Font & font) {
    msgText.setFont(font);
    this->xInit = xInit;
    this->yInit = yInit;
    state = CLOSED;
    animationCounter = 4;
}

void Caption::setWindowCenter(float x, float y) {
    windowCenterX = x;
    windowCenterY = y;
}

void Caption::update(float xOffset, float yOffset) {
    xPos = xInit + xOffset;
    yPos = yInit + yOffset;
    
    switch (state) {
        case CLOSED:
            if (fabsf(xPos - windowCenterX) < windowCenterY * 0.65 && fabsf(yPos - windowCenterY) < windowCenterY * 0.65) {
                state = OPENING;
                // Tilt the text a little bit
                float rotationDir = (rand() % 2) ? -1 : 1;
                msgText.setRotation(rotationDir * (rand() % 4 + 4));
            }
            break;
            
        case OPENING:
            if (--animationCounter == 0) {
                animationCounter = 4;
                if (workingString.length() < msgString.length()) {
                    workingString.push_back(msgString[workingString.length()]);
                    std::string tempstr = msgHeader + workingString + msgFooter;
                    msgText.setString(tempstr.c_str());
                } else {
                    state = OPENED;
                }
            }
            break;
            
        case OPENED:
            if (fabsf(xPos - windowCenterX) > windowCenterY * 0.9 || fabsf(yPos - windowCenterY) > windowCenterY * 0.9) {
                state = CLOSING;
            }
            break;
            
        case CLOSING:
            if (--animationCounter == 0) {
                animationCounter = 3;
                if (workingString.length() > 0) {
                    workingString.pop_back();
                    std::string tempstr = msgHeader + workingString + msgFooter;
                    msgText.setString(tempstr.c_str());
                } else {
                    state = CLOSED;
                    animationCounter = 4;
                }
            }
            break;
            
        case FORCE_CLOSE:
            if (--animationCounter == 0) {
                animationCounter = 2;
                if (workingString.length() > 0) {
                    workingString.pop_back();
                    std::string tempstr = msgHeader + workingString + msgFooter;
                    msgText.setString(tempstr.c_str());
                } else {
                    state = LOCKED;
                    animationCounter = 4;
                }
            }
            break;
            
        case LOCKED:
            // Do nothing, locked down
            break;
            
        default:
            break;
    }
}

void Caption::setText(const char * cstrText) {
    msgString = cstrText;
    msgHeader = "( ";
    msgFooter = " )";
    std::string tempstr = msgHeader + msgFooter;
}

sf::Text * Caption::getText() {
    // Horizontally center the text over the target position and return it
    msgText.setPosition(xPos - msgText.getLocalBounds().width / 2, yPos - msgText.getLocalBounds().height / 2);
    return &msgText;
}

void Caption::forceClose() {
    if (state != LOCKED)
        state = FORCE_CLOSE;
}

bool Caption::isClosed() {
    return state == CLOSED || state == LOCKED;
}

void Caption::setCharacterSize(float size) {
    msgText.setCharacterSize(size);
}

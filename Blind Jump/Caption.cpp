//
//  Caption.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 4/16/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "Caption.hpp"
#include <cmath>

#define PI 3.1415926535

Caption::Caption(float xInit, float yInit, sf::Font & font) {
    msgText.setFont(font);
    //msgText.setColor(sf::Color(180, 180, 180));
    this->xInit = xInit;
    this->yInit = yInit;
    state = CLOSED;
    desiredDelay = 20;
    clock.restart();
    animationTimer.restart();
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
            if (fabsf(xPos - windowCenterX) < windowCenterY * 0.25 && fabsf(yPos - windowCenterY) < windowCenterY * 0.25) {
                state = OPENING;
                // Tilt the text a little bit
                float rotationDir = (rand() % 2) ? -1 : 1;
                msgText.setRotation(rotationDir * (rand() % 4 + 3));
                animationTimer.restart();
            }
            break;
            
        case OPENING:
            if (animationTimer.getElapsedTime().asMilliseconds() > desiredDelay) {
                animationTimer.restart();
                desiredDelay = static_cast<int>(30 * workingString.length() / msgString.length()) + 20;
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
            if (fabsf(xPos - windowCenterX) > windowCenterY * 0.35 || fabsf(yPos - windowCenterY) > windowCenterY * 0.35) {
                state = CLOSING;
            }
            break;
            
        case CLOSING:
            if (animationTimer.getElapsedTime().asMilliseconds() > desiredDelay) {
                animationTimer.restart();
                desiredDelay = static_cast<int>(30 * workingString.length() / msgString.length()) + 20;
                if (workingString.length() > 0) {
                    workingString.pop_back();
                    std::string tempstr = msgHeader + workingString + msgFooter;
                    msgText.setString(tempstr.c_str());
                } else {
                    state = CLOSED;
                }
            }
            break;
            
        case FORCE_CLOSE:
            if (animationTimer.getElapsedTime().asMilliseconds() > desiredDelay) {
                animationTimer.restart();
                desiredDelay = static_cast<int>(10 * workingString.length() / msgString.length()) + 20;
                if (workingString.length() > 0) {
                    workingString.pop_back();
                    std::string tempstr = msgHeader + workingString + msgFooter;
                    msgText.setString(tempstr.c_str());
                } else {
                    state = LOCKED;
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
    float offset = (2 * sinf(2 * PI * 0.001 * clock.getElapsedTime().asMilliseconds() + 180));
    msgText.setPosition(xPos - msgText.getLocalBounds().width / 2, yPos - msgText.getLocalBounds().height / 2 + offset);
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

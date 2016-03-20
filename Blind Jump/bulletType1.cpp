//
//  bulletType1.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/14/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "bulletType1.hpp"

#define TIME 14

bulletType1::bulletType1(sf::Sprite s, sf::Sprite s2, char dir, float x, float y) {
    //Initialize the starting x position to the player's x position
    xPos = x;
    yPos = y;
    xInit = x;
    yInit = y;
    direction = dir;
    bulletSprite[0] = s;
    bulletSprite[1] = s2;
    duration = TIME;
    killFlag = 0;
    canPoof = true;
}

//A function to return the bullet sprite
sf::Sprite bulletType1::getSprite() {
    return bulletSprite[0];
}

sf::Sprite* bulletType1::getGlow() {
    return &bulletSprite[1];
}

void bulletType1::update(float xOffset, float yOffset) {
    switch (direction) {
            //There's a lot of funny addition of numbers here. That's because the end of the gun sprite moves around based on which way the player faces,
            // so each case needs to set a specific origin for the shot object.
        case 0:
            xPos = xInit + xOffset + 6;
            yPos = yInit + 11 + yOffset + 18 + 9 * (TIME - duration); //'20 - duration' term grows with time, thus moving the bullet across the screen
            break;
        case 1:
            xPos = xInit + xOffset + 6;
            yPos = yInit + 11 + yOffset - 9 * (TIME - duration);
            break;
        case 2:
            xPos = xInit + xOffset - 13 - 9 * (TIME - duration);
            yPos = yInit + 11 + yOffset + 8;
            break;
        case 3:
            xPos = xInit + xOffset + 29 + 9 * (TIME - duration);
            yPos = yInit + 11 + yOffset + 8;
            break;
        case 4:
            xPos = xInit + xOffset + 6;
            yPos = yInit + 11 + yOffset + 18 + 9 * (TIME - duration);
            break;
        case 5:
            xPos = xInit + xOffset + 6;
            yPos = yInit + 11 + yOffset - 9 * (TIME - duration);
            break;
        case 6:
            xPos = xInit + xOffset - 13 - 9 * (TIME - duration);
            yPos = yInit + 11 + yOffset + 8;
            break;
        case 7:
            xPos = xInit + xOffset + 29 + 9 * (TIME - duration);
            yPos = yInit + 11 + yOffset + 8;
            break;
    }
    //Now that we've done all of that legwork, actually set the sprite's position
    bulletSprite[0].setPosition(xPos, yPos);
    bulletSprite[1].setPosition(xPos - 16, yPos - 1);
    --duration;
    if (duration == 0) {
        killFlag = true;
    }
    float offset = rand() % 20;
    bulletSprite[1].setColor(sf::Color(230 + offset, 230 + offset, 230 + offset, 255));
}

bool bulletType1::getKillFlag() {
    return killFlag;
}

void bulletType1::setKillFlag() {
    killFlag = 1;
}

void bulletType1::setPosition(float x, float y) {
    xPos = x;
    yPos = y;
}

float bulletType1::getPosX() {
    return xPos;
}

float bulletType1::getPosY() {
    return yPos;
}

char bulletType1::getDirection() {
    return direction;
}

bool bulletType1::checkCanPoof() {
    return canPoof;
}

void bulletType1::disablePuff() {
    canPoof = false;
}
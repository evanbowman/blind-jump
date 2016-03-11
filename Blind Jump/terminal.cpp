//
//  energyCube.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/28/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "terminal.hpp"

Terminal::Terminal(float xStart, float yStart, sf::Sprite* sprs, int len, float width, float height) : detailParent(xStart, yStart, sprs, len, width, height) {
    for (int i = 0; i < len; i++) {
        termSprites[i] = sprs[i];
    }
}

sf::Sprite* Terminal::getSprite() {
    currentframe = !currentframe;
    if (currentframe) {
        return &termSprites[0];
    }
    return &termSprites[1];
}

sf::Sprite* Terminal::getShadow() {
    return &termSprites[2];
}

void Terminal::update(float xOffset, float yOffset) {
    xPos = xOffset + xInit;
    yPos = yOffset + yInit;
    termSprites[0].setPosition(xPos, yPos - 16);
    termSprites[1].setPosition(xPos, yPos - 16);
    termSprites[2].setPosition(xPos, yPos + 14);
}
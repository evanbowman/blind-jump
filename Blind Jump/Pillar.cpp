//
//  Pillar.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/15/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "Pillar.hpp"

Pillar::Pillar(float xStart, float yStart, sf::Sprite* inpSpr, int len, float width, float height) : detailParent(xStart, yStart, inpSpr, len, width, height) {
    sprite = inpSpr[0];
}

void Pillar::update(float xOffset, float yOffset) {
    xPos = xOffset + xInit;
    yPos = yOffset + yInit;
}

sf::Sprite* Pillar::getSprite() {
    sprite.setPosition(xPos, yPos);
    return &sprite;
}

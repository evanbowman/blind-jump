
//
//  mapTower.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 11/7/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "Teleporter.hpp"

Teleporter::Teleporter(float xStart, float yStart, sf::Sprite* sprs, sf::Sprite glow, int len, float windowW, float windowH) : detailParent(xStart, yStart, sprs, len, windowW, windowH) {
    for (int i = 0; i < len; i++) {
        TeleporterSprites[i] = sprs[i];
    }
    glowSprite = glow;
    glowSprite.setOrigin(200, 200);
    smokeTimer = 0;
}

sf::Sprite* Teleporter::getShadow() {
    return &TeleporterSprites[1];
}

sf::Sprite* Teleporter::getSprite() {
    return &TeleporterSprites[0];
}

void Teleporter::update(float xOffset, float yOffset, sf::Time & elapsedTime) {
    smokeTimer += elapsedTime.asMilliseconds();
    xPos = xOffset + xInit;
    yPos = yOffset + yInit;
    glowSprite.setPosition(xPos + 16, yPos + 13);
    TeleporterSprites[0].setPosition(xPos - 3, yPos);
    TeleporterSprites[1].setPosition(xPos - 3, yPos + 4);
}

sf::Sprite* Teleporter::getGlow() {
    return &glowSprite;
}

bool Teleporter::smokeReady() {
    if (smokeTimer > 264) {
        smokeTimer -= 264;
        return true;
    }
    return false;
}
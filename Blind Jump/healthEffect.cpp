//
//  healthEffect.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/9/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "healthEffect.hpp"

#define EFFECT_DURATION 50

HealthEffect::HealthEffect(sf::Sprite spr, float xInit, float yInit) {
    this->spr = spr;
    this->xInit = xInit;
    this->yInit = yInit;
    lifeCounter = EFFECT_DURATION;
    killFlag = false;
    mode = 0;
    this->spr.setColor(sf::Color(255, 255, 255, 255));
}

sf::Sprite HealthEffect::getSprite() {
    return spr;
}

bool HealthEffect::getKillFlag() {
    return killFlag;
}

void HealthEffect::update(float xOffset, float yOffset) {
    if (--lifeCounter == 0 ) {
        killFlag = true;
    }
    // Move the effect up and fade out
    yInit -= 1;
    sf::Color c = spr.getColor();
    c.a -= 200 / EFFECT_DURATION;
    spr.setColor(c);
    if (mode == 0) {
        spr.setPosition(xInit + xOffset, yInit + yOffset);
    }
    else if (mode == 1) {
        spr.setPosition(spr.getPosition().x, spr.getPosition().y - 1);
    }
}

void HealthEffect::setMode(char mode, float x, float y) {
    spr.setPosition(x, y);
    this->mode = mode;
}

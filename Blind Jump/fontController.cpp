//
//  FontController.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/21/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//
//  This class is responsible for creating text for the current level and drawing it to the screen
//
//

#include "fontController.hpp"
#include "ResourcePath.hpp"

#define healthLimit 10

FontController::FontController(sf::View fontView) {
    // Store the view to use when drawing fonts
    this->fontView = fontView;

    
    for (int i = 0; i < 10; i++) {
        // Load in score number textures
        healthFull[i].setRadius(3);
        healthFull[i].setFillColor(sf::Color::White);
        healthFull[i].setOutlineColor(sf::Color::White);
        healthFull[i].setOutlineThickness(1);
        healthEmpty[i].setRadius(3);
        healthEmpty[i].setFillColor(sf::Color::Transparent);
        healthEmpty[i].setOutlineColor(sf::Color::White);
        healthEmpty[i].setOutlineThickness(1);
    }
    
    health = 4;
    maxHealth = 4;
    doRecolor = false;
    colorState = 'w';
    sf::Sprite tempSprite;
    score = 0;
}

void FontController::setWaypointText(int level, float w, float h) {
    // Put the health text in the right spot
    float initPos = w - maxHealth * 10 - 5;
    for (int i = 0; i < 10; i++) {
        healthFull[i].setPosition((i * 10) + initPos, 6);
        healthEmpty[i].setPosition((i * 10) + initPos, 6);
    }
    //sprHealthText.setPosition(initPos - 42, 2);
}

void FontController::setZoneText(char zone) {
    switch (zone) {
        case 0:
            //zoneTextSpr.setTexture(zoneTextTxtr[0]);
            break;
            
        case 1:
            //zoneTextSpr.setTexture(zoneTextTxtr[1]);
            break;
            
        default:
            break;
    }
}

void FontController::print(sf::RenderWindow& window) {
    for (int i = 0; i < maxHealth; i++) {
        if (health > i) {
            window.draw(healthFull[i]);
        }
        else {
            window.draw(healthEmpty[i]);
        }
    }
}

void FontController::updateHealth(char health) {
    // Set health equal to the input parameter or the max health, depending on which is lower
    this->health = std::min(health, maxHealth);
}


void FontController::updateMaxHealth(char health) {
    maxHealth = health;
    // Put the health in the right spot in the window
    float initPos = width - maxHealth * 10 - 5;
    for (int i = 0; i < 10; i++) {
        healthFull[i].setPosition((i * 10) + initPos, 6);
        healthEmpty[i].setPosition((i * 10) + initPos, 6);
    }
    //sprHealthText.setPosition(initPos - 42, 2);
}

char FontController::getMaxHealth() {
    return maxHealth;
}

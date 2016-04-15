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

FontController::FontController() {
    //Load in the texture for the text
    if (!texture.loadFromFile(resourcePath() + "waypointText.png")) {
        //return EXIT_FAILURE;
    }
    if (!healthText.loadFromFile(resourcePath() + "healthText.png")) {
        //return EXIT_FAILURE;
    }
    limiterText.loadFromFile(resourcePath() + "toTargetText.png");
    sprLimiterText.setTexture(limiterText);
    sprLimiterText.setPosition(414, -2);
    sprLimiterText.setColor(sf::Color(255,255,255,250));
    
    sprHealthText.setTexture(healthText);
    sprHealthText.setColor(sf::Color(255,255,255,250));
    //Set the alpha for drawing the text
    alpha = 250;
    
    zoneTextTxtr[0].loadFromFile(resourcePath() + "zoneTexts.png", sf::IntRect(0, 0, 112, 6));
    zoneTextTxtr[1].loadFromFile(resourcePath() + "zoneTexts.png", sf::IntRect(0, 6, 112, 6));
    zoneTextSpr.setTexture(zoneTextTxtr[0]);
    zoneTextSpr.setPosition(6, 27);
    
    //Load all of the texture for numbers 0-9
    const std::string numberFileExtensions[11] = {"num0.png", "num1.png", "num2.png", "num3.png", "num4.png", "num5.png", "num6.png", "num7.png", "num8.png", "num9.png", "numSpacer.png"};
    for (int i = 0; i < 11; i++) {
        if (!nums[i].loadFromFile(resourcePath() + numberFileExtensions[i])) {
            //return EXIT_FAILURE;
        }
    }
    
    for (int i = 0; i < 10; i++) {
        // Load in score number textures
        scoreNums[i].loadFromFile(resourcePath() + "scoreNums.png", sf::IntRect(i * 5, 0, 5, 7));
        healthFull[i].setRadius(3);
        healthFull[i].setFillColor(sf::Color::White);
        healthFull[i].setOutlineColor(sf::Color::White);
        healthFull[i].setOutlineThickness(1);
        healthEmpty[i].setRadius(3);
        healthEmpty[i].setFillColor(sf::Color::Transparent);
        healthEmpty[i].setOutlineColor(sf::Color::White);
        healthEmpty[i].setOutlineThickness(1);
    }
    
    // Load the textures for lives
    healthTexture[0].loadFromFile(resourcePath() + "hp.png");
    healthTexture[1].loadFromFile(resourcePath() + "hp_empty.png");
    // Apply the texture to each of the health sprites
    energyTxtr.loadFromFile(resourcePath() + "energyText.png");
    energySprite.setTexture(energyTxtr);
    
    health = 4;
    maxHealth = 4;
    doRecolor = false;
    colorState = 'w';
    sf::Sprite tempSprite;
    tempSprite.setTexture(scoreNums[0]);
    scoreString.push_back(tempSprite);
    score = 0;
}

void FontController::setWaypointText(int level, float w, float h) {
    int n[5];
    width = w;
    height = h;
    bool seenNumber = 0;
    char hasDrawn = 0;
    for (int i = 0; i < 5; i++) {
        n[i] = level % 10;
        level /= 10;
    }
    for (int i = 4; i > -1; i--) {
        if (seenNumber == 0) {
            if (n[i] != 0) {        //If we haven't hit a number greater than 0 and this one's 0, skip (drawing a bunch of leading zeros to the screen is sort of inelegant and wasteful)
                seenNumber = 1;
                hasDrawn += 1;
                sf::Sprite tempSprite;
                tempSprite.setTexture(nums[n[i]]);
                tempSprite.setPosition(/*(w / 2)*/ + 103 + 14 * hasDrawn, 3);
                textNums.push_back(tempSprite);
            }
        }
        else if (seenNumber) {  //If we have seen a number, of course draw the zeroes in
            hasDrawn += 1;
            sf::Sprite tempSprite;
            tempSprite.setTexture(nums[n[i]]);
            tempSprite.setPosition(/*(w / 2)*/ + 103 + 14 * hasDrawn, 3);
            textNums.push_back(tempSprite);
        }
    }
    //The main text 'Waypoint' does not change, so push it back once and all of the time
    sf::Sprite tempSprite2;
    tempSprite2.setTexture(texture);
    tempSprite2.setPosition(/*(w / 2)*/ 5, 3);
    textCharacters.push_back(tempSprite2);
    
    sf::Sprite tempSprite3;
    tempSprite3.setTexture(nums[10]);
    tempSprite3.setPosition(104, 3);
    textNums.push_back(tempSprite3);
    
    // Put the health text in the right spot
    float initPos = w - maxHealth * 9 - 5;
    for (int i = 0; i < 10; i++) {
        healthFull[i].setPosition((i * 9) + initPos, 6);
        healthEmpty[i].setPosition((i * 9) + initPos, 6);
    }
    sprHealthText.setPosition(initPos - 42, 2);
}

//Need a function to clear out the font controller, for when the level resets and new numbers get pushed back to the font vector
void FontController::clear() {
    textCharacters.clear();
    textNums.clear();
}

void FontController::setZoneText(char zone) {
    switch (zone) {
        case 0:
            zoneTextSpr.setTexture(zoneTextTxtr[0]);
            break;
            
        case 1:
            zoneTextSpr.setTexture(zoneTextTxtr[1]);
            break;
            
        default:
            break;
    }
}

void FontController::print(sf::RenderWindow& window) {
    // Draw the score to the screen
    //for (auto & element : scoreString) {
        //window.draw(element);
    //}
    
    if (!textCharacters.empty()) {
        for (auto & element : textCharacters) {
            window.draw(element);
        }
    }
    if (!textNums.empty()) {
        for (auto & element : textNums) {
            window.draw(element);
        }
    }
    window.draw(sprHealthText);
    //window.draw(energySprite);
    window.draw(zoneTextSpr);
    //window.draw(sprLimiterText);
    
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
    float initPos = width - maxHealth * 9 - 5;
    for (int i = 0; i < 10; i++) {
        healthFull[i].setPosition((i * 9) + initPos, 4);
        healthEmpty[i].setPosition((i * 9) + initPos, 4);
    }
    sprHealthText.setPosition(initPos - 42, 2);
}

void FontController::recolor(char colorState) {
    this->colorState = colorState;
    doRecolor = true;
}

void FontController::updateScore(int score) {
    // Clear the previous text out of the vector
    scoreString.clear();
    bool seenNumber = false;
    sf::Sprite tempSprite;
    this->score += score - this->score;
    int numArr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 10; i++) {
        numArr[i] = score % 10;
        score /= 10;
        
        if ((numArr[i] != 0) || (numArr[i] == 0 && !seenNumber)) {
            if (numArr[i] != 0)
                seenNumber = true;
            
            tempSprite.setTexture(scoreNums[numArr[i]]);
            tempSprite.setPosition(width - 16 - i * 6, 5);
            scoreString.push_back(tempSprite);
        }
    }
    energySprite.setPosition(scoreString.back().getPosition().x - 64, 4);


}

int FontController::getScore() {
    return score;
}

void FontController::zeroScore() {
    scoreString.clear();
    this->score = 0;
    sf::Sprite tempSprite;
    tempSprite.setTexture(scoreNums[0]);
    tempSprite.setPosition(width - 16, 5);
    scoreString.push_back(tempSprite);
    energySprite.setPosition(scoreString.back().getPosition().x - 64, 4);
}

char FontController::getMaxHealth() {
    return maxHealth;
}

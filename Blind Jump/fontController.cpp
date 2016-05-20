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

#define healthLimit 10
#define HEALTH_TEXT_FADE_SECONDS 3
#define SCORE_TEXT_FADE_SECONDS 3
#define WAYPOINT_TEXT_FADE_SECONDS 3

FontController::FontController(sf::View fontView, float x, float y) {
    // Store the view to use when drawing fonts
    this->fontView = fontView;
    
    windowCenterX = x;
    windowCenterY = y;

    // Load all of the game fonts into memory
    cornerstone.loadFromFile(resourcePath() + "Cornerstone.ttf");
    museo.loadFromFile(resourcePath() + "Museo_Slab_500_2.otf");
    //const_cast<sf::Texture&>(cornerstone.getTexture(12)).setSmooth(false);

    // Set the waypoint text
    waypointText.setFont(cornerstone);
    waypointText.setString("WAYPOINT-1");
    waypointText.setCharacterSize(0.055 * fontView.getSize().y);
    waypointText.setPosition(16, 0);
    
    
    healthText.setString("Health:");
    healthText.setCharacterSize(0.026 * fontView.getSize().y);
    healthText.setFont(cornerstone);
    
    scoreText.setString("Score: 0");
    scoreText.setCharacterSize(0.026 * fontView.getSize().y);
    scoreText.setFont(cornerstone);
    
    titleText.setString("Blind Jump");
    titleText.setCharacterSize(0.115 * fontView.getSize().y);
    titleText.setFont(cornerstone);
    titleText.setPosition(fontView.getSize().x / 2 - titleText.getLocalBounds().width / 2, fontView.getSize().y / 8 - titleText.getLocalBounds().height / 2);
    
    deathText.setCharacterSize(0.115 * fontView.getSize().y);
    deathText.setFont(cornerstone);
    deathText.setString("YOU DIED");
    deathText.setColor(sf::Color(231, 26, 83));
    deathText.setPosition(fontView.getSize().x / 2 - deathText.getLocalBounds().width / 2, fontView.getSize().y / 12 - deathText.getLocalBounds().height / 2);
    
    
    for (int i = 0; i < 10; i++) {
        // Load in score number textures
        healthFull[i].setRadius(0.009 * fontView.getSize().y);
        healthFull[i].setFillColor(sf::Color(255, 255, 255, 4));
        healthFull[i].setOutlineColor(sf::Color(255, 255, 255, 4));
        healthFull[i].setOutlineThickness(0.004 * fontView.getSize().y);
        healthEmpty[i].setRadius(0.009 * fontView.getSize().y);
        healthEmpty[i].setFillColor(sf::Color::Transparent);
        healthEmpty[i].setOutlineColor(sf::Color(255, 255, 255, 4));
        healthEmpty[i].setOutlineThickness(0.004 * fontView.getSize().y);
    }
    
    health = 4;
    maxHealth = 4;
    score = 0;
}

void FontController::setWaypointText(int level) {
    // Put the health text in the right spot
    float initPos = fontView.getSize().x - maxHealth * 0.030 * fontView.getSize().y - 12;
    float scrnSize = fontView.getSize().y;
    for (int i = 0; i < 10; i++) {
        healthFull[i].setPosition((i * 0.030 * scrnSize) + initPos, 0.0030 * scrnSize + healthFull[i].getRadius());
        healthEmpty[i].setPosition((i * 0.030 * scrnSize) + initPos, 0.0030 * scrnSize + healthFull[i].getRadius());
        healthFull[i].setFillColor(sf::Color(255, 255, 255, 4));
        healthFull[i].setOutlineColor(sf::Color(255, 255, 255, 4));
        healthEmpty[i].setFillColor(sf::Color::Transparent);
        healthEmpty[i].setOutlineColor(sf::Color(255, 255, 255, 4));
    }
    healthText.setPosition(initPos - healthText.getLocalBounds().width - 0.015 * scrnSize, 0.0032 * scrnSize + healthFull[0].getRadius() - healthText.getLocalBounds().height / 2);
    scoreText.setPosition(fontView.getSize().x - scoreText.getLocalBounds().width - fontView.getSize().x * 0.015, scoreText.getLocalBounds().height * 2.5);
    std::string str = "WAYPOINT-";
    str += std::to_string(level);
    waypointText.setString(str);
    // Reset the color, it will fade out
    waypointText.setColor(sf::Color::White);
    healthText.setColor(sf::Color(255, 255, 255, 4));
    scoreText.setColor(sf::Color(255, 255, 255, 4));
    wpTextDisplayTimer.restart();
    healthDisplayTimer.restart();
    scoreDisplayTimer.restart();
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
    // Set the correct view, so not to blur the fonts
    window.setView(fontView);
    // Slowly fade out the  waypoint text
    sf::Color c = waypointText.getColor();
    if (c.a > 5) {
        if (wpTextDisplayTimer.getElapsedTime().asSeconds() > WAYPOINT_TEXT_FADE_SECONDS) {
            c.a -= 4;
            waypointText.setColor(c);
        }
        window.draw(waypointText);
    }
    c = healthFull[0].getFillColor();
    
    if (c.a > 5) {
        if (healthDisplayTimer.getElapsedTime().asSeconds() > HEALTH_TEXT_FADE_SECONDS) {
            c.a -= 4;
            for (int i = 0; i < 10; i++) {
                healthFull[i].setFillColor(c);
                healthFull[i].setOutlineColor(c);
                healthEmpty[i].setOutlineColor(c);
            }
            healthText.setColor(c);
        }
        
        for (int i = 0; i < maxHealth; i++) {
            if (health > i) {
                window.draw(healthFull[i]);
            }
            else {
                window.draw(healthEmpty[i]);
            }
        }
    }
    window.draw(healthText);
    
    c = scoreText.getColor();
    if (c.a > 5) {
        if (scoreDisplayTimer.getElapsedTime().asSeconds() > SCORE_TEXT_FADE_SECONDS) {
            c.a -= 4;
            scoreText.setColor(c);
        }
        window.draw(scoreText);
    }
}

void FontController::resetWPText() {
    waypointText.setColor(sf::Color::White);
    wpTextDisplayTimer.restart();
}

void FontController::resetSCText() {
    scoreText.setColor(sf::Color::White);
    scoreDisplayTimer.restart();
}

void FontController::updateScore(int offset) {
    score += offset;
    std::string str = "Energy: ";
    str += std::to_string(score);
    scoreText.setString(str);
    scoreText.setPosition(fontView.getSize().x - scoreText.getLocalBounds().width - fontView.getSize().x * 0.015, scoreText.getLocalBounds().height * 2.5);
    resetSCText();
}

void FontController::resetHPText() {
    healthText.setColor(sf::Color::White);
    for (int i = 0; i < 10; i++) {
        healthFull[i].setFillColor(sf::Color::White);
        healthFull[i].setOutlineColor(sf::Color::White);
        healthEmpty[i].setOutlineColor(sf::Color::White);
    }
    healthDisplayTimer.restart();
}

void FontController::update(sf::RenderWindow & window, float xOffset, float yOffset) {
    window.setView(fontView);
}

void FontController::drawTitle(unsigned char alpha, sf::RenderWindow& window) {
    titleText.setColor(sf::Color(255, 255, 255, alpha));
    window.setView(fontView);
    window.draw(titleText);
}

void FontController::drawDeathText(unsigned char alpha, sf::RenderWindow & window) {
    deathText.setColor(sf::Color(231, 26, 83, alpha));
    window.setView(fontView);
    window.draw(deathText);
}

sf::Text* FontController::getTitle() {
    return &titleText;
}

void FontController::updateHealth(char health) {
    // Set health equal to the input parameter or the max health, depending on which is lower
    this->health = std::min(health, maxHealth);
}

void FontController::updateMaxHealth(char health) {
    maxHealth = health;
    // Put the health in the right spot in the window
    float initPos = fontView.getSize().x - maxHealth * 0.030 * fontView.getSize().y - 12;
    float scrnSize = fontView.getSize().y;
    for (int i = 0; i < 10; i++) {
        healthFull[i].setPosition((i * 0.030 * scrnSize) + initPos, 0.0030 * scrnSize + healthFull[i].getRadius());
        healthEmpty[i].setPosition((i * 0.030 * scrnSize) + initPos, 0.0030 * scrnSize + healthFull[i].getRadius());
    }
    healthText.setPosition(initPos - healthText.getLocalBounds().width - 0.015 * scrnSize, 0.0032 * scrnSize + healthFull[0].getRadius() - healthText.getLocalBounds().height / 2);
    resetHPText();
}

char FontController::getMaxHealth() const {
    return maxHealth;
}

sf::Text * FontController::getDeathText() {
    return &deathText;
}

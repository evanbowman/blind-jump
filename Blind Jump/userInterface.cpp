//
//  userInterface.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/22/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "userInterface.hpp"
#include <cmath>
#include "ResourcePath.hpp"
#include "Strings.h"
#include "player.hpp"

// Macros to make the state machine more easily readable
#define OPENING 'o'
#define OPEN 'O'
#define CLOSING 'c'
#define CLOSED 'C'

userInterface::userInterface() {
    visible = 0;
    xPos = 0;
    yPos = 0;
    blurAmount = 0.1;
    deathSeqComplete = false;
    textDisplacement = 0;
    canHeal = true;
    state = CLOSED;
    
    
    // Load textures in from a sprite sheet
    for (int i = 0; i < 29; i++) {
        letterTextures[i].loadFromFile(resourcePath() + "alphabetSheet.png", sf::IntRect(1 + i * 7, 0, 6, 9));
        inverseLetterTextures[i].loadFromFile(resourcePath() + "alphabetSheetInverse.png", sf::IntRect(i * 7, 0, 8, 9));
    }
    
    sf::Color c(255,255,255,2);
    
    
    
    deathShadowTxt.loadFromFile(resourcePath() + "deathShadow.png");
    deathShadowSpr.setTexture(deathShadowTxt);
    deathShadowSpr.setColor(c);
    
    // Load in all of the item textures
    for (int i = 0; i < 6; i++) {
        itemTextures[i].loadFromFile(resourcePath() + "items.png", sf::IntRect(i * 66, 0, 66, 34));
    }
    
    gunSprite.setTexture(itemTextures[0]);
    gunSprite.setScale(6, 6);
    gunSprite.setOrigin(gunSprite.getLocalBounds().width / 2, gunSprite.getLocalBounds().height / 2);
    
    txtShadowTexture.loadFromFile(resourcePath() + "overworldTextShadow.png");
    txtShadowSprite.setTexture(txtShadowTexture);
    selectorShadowTexture.loadFromFile(resourcePath() + "itemSelectorVignette.png");
    selectorShadowSprite.setTexture(selectorShadowTexture);
    deathSeq = false;
}

void userInterface::drawMenu(sf::RenderWindow& window, Player* player, unsigned char * detailStates, FontController& f, effectsController& ef, float xOffset, float yOffset, InputController* pInput, sf::Time& elapsed) {
    bool c = pInput->cPressed();
    /*bool left = pInput->leftPressed();
    bool right = pInput->rightPressed();
    bool up = pInput->upPressed();
    bool down = pInput->downPressed();
    bool z = pInput->zPressed();*/
    bool x = pInput->xPressed();
    
    switch (state) {
        case CLOSED:
            if (c) {
                state = OPENING;
                visible = true;
                player->deActivate();
            }
            break;
            
        case OPEN:
            if (c || x) {
                state = CLOSING;
                player->activate();
            }
            window.draw(gunSprite);
            //window.draw(column1, sf::BlendAdd);
            break;
            
        case OPENING:
            if (blurAmount < 0.99999f) {
                blurAmount *= 1.2f;
                if (blurAmount > 0.99999f) {
                    blurAmount = 0.99999f;
                    state = OPEN;
                }
            }
            break;
            
        case CLOSING:
            if (blurAmount > 0.1f) {
                blurAmount *= 0.92f;
                if (blurAmount < 0.1f) {
                    blurAmount = 0.1f;
                    state = CLOSED;
                    visible = false;
                }
            }
            break;
            
        default:
            // Shouldn't ever hit the default case
            break;
    }
    
    if (deathSeq) {
        // During the player death sequence apply a vignette effect across the window
        sf::Color c = deathShadowSpr.getColor();
        if (c.a < 246 && !deathSeqComplete) {
            c.a += 4;
            deathShadowSpr.setColor(c);
        }
        else {
            deathSeqComplete = true;
        }
        
        window.draw(deathShadowSpr);
        f.drawDeathText(c.a, window);
    }
    
    if (visible) {
        //window.draw(selectorShadowSprite);
        if (blurAmount == 0.99999f) {
            f.resetWPText();
            f.resetHPText();
            f.resetSCText();
        }
    }
}

void userInterface::setPosition(float x, float y) {
    xPos = x;
    yPos = y + 16;
    sf::Vector2f v1(x * 2 / 3, y * 1.6);
    
    // Set the size of the shadow gradient to draw when displaying text
    txtShadowSprite.setScale((2 * x) / 450, (2 * y) / 450);
    txtShadowSprite.setColor(sf::Color(255, 255, 255, 4));
    
    for (auto & element : textToDisplay) {
        element.setColor(sf::Color(255, 255, 255, 1));
    }
    
    gunSprite.setPosition(x, y);
    
    selectorShadowSprite.setColor(sf::Color(255,255,255,1));
    selectorShadowSprite.setScale((x * 2) / 450, (y * 2) / 450);
    deathShadowSpr.setScale((x * 2) / 450, (y * 2) / 450);
}

void userInterface::addItem(char newItem, effectsController& ef, float xStart, float yStart, FontController& fonts, Player& player) {
    if (newItem == 90) {
        fonts.updateMaxHealth(fonts.getMaxHealth() + 1);
    } else {
        
    }
}

void userInterface::dispDeathSeq() {
    deathSeq = true;
}

bool userInterface::isComplete() {
    return deathSeqComplete;
}

float userInterface::getBlurAmount() {
    return blurAmount;
}

void userInterface::reset() {
    deathSeq = false;
    deathSeqComplete = false;
    deathShadowSpr.setColor(sf::Color(255,255,255,2));
}

bool userInterface::isVisible() {
    return visible;
}

void userInterface::setEnemyValueCount(int count) {
    enemyValueCount = count;
}
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

userInterface::userInterface() {
    visible = 0;
    xPos = 0;
    yPos = 0;
    blurAmount = 0.1;
    deathSeqComplete = false;
    textDisplacement = 0;
    canHeal = true;
    state = State::closed;
    
    sf::Color c(255,255,255,2);
    
    deathShadowTxt.loadFromFile(resourcePath() + "deathShadow.png");
    deathShadowSpr.setTexture(deathShadowTxt);
    deathShadowSpr.setColor(c);

    
    // Load in all of the item textures
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            itemTextures[i][j].loadFromFile(resourcePath() + "items.png", sf::IntRect(j * 24, i * 34, 24, 34));
    
    for (int i = 0; i < 3; i++) {
        gunSprites[i].setTexture(itemTextures[0][i]);
        gunSprites[i].setScale(5, 5);
        gunSprites[i].setOrigin(gunSprites[i].getLocalBounds().width / 2, gunSprites[i].getLocalBounds().height / 2 + 5);
        rowIndices[i] = 0;
    }
    
    txtShadowTexture.loadFromFile(resourcePath() + "overworldTextShadow.png");
    txtShadowSprite.setTexture(txtShadowTexture);
    selectorShadowTexture.loadFromFile(resourcePath() + "itemSelectorVignette.png");
    selectorShadowSprite.setTexture(selectorShadowTexture);
    deathSeq = false;
    selectedColumn = 0;
    keyPressed = false;
}

void userInterface::drawMenu(sf::RenderWindow& window, Player* player, FontController& f, effectsController& ef, float xOffset, float yOffset, InputController* pInput, sf::Time& elapsed) {
    bool c = pInput->cPressed();
    bool left = pInput->leftPressed();
    bool right = pInput->rightPressed();
    bool up = pInput->upPressed();
    bool down = pInput->downPressed();
    bool z = pInput->zPressed();
    bool x = pInput->xPressed();
    
    switch (state) {
        case State::closed:
            if (c) {
                state = State::opening;
                visible = true;
                player->deActivate();
            }
            break;
            
        case State::open:
            if (c) {
                state = State::closing;
                player->activate();
            }
            
            for (int i = 0; i < 3; i++) {
                window.draw(gunSprites[i]);
            }
            
            if (left && selectedColumn > 0 && !keyPressed) {
                selectedColumn--;
            } else if (right && selectedColumn < 2 && !keyPressed) {
                selectedColumn++;
            } else if (up && rowIndices[selectedColumn] > 0 && !keyPressed) {
                rowIndices[selectedColumn]--;
                gunSprites[selectedColumn].setTexture(itemTextures[rowIndices[selectedColumn]][selectedColumn]);
            } else if (down && rowIndices[selectedColumn] < 2 && !keyPressed) {
                rowIndices[selectedColumn]++;
                gunSprites[selectedColumn].setTexture(itemTextures[rowIndices[selectedColumn]][selectedColumn]);
            }
            //window.draw(column1, sf::BlendAdd);
            break;
            
        case State::opening:
            if (blurAmount < 0.99999f) {
                blurAmount *= 1.2f;
                if (blurAmount > 0.99999f) {
                    blurAmount = 0.99999f;
                    state = State::open;
                }
            }
            if (weaponDispOffset > 1) {
                weaponDispOffset *= 0.8;
                if (weaponDispOffset < 1) {
                    weaponDispOffset = 1;
                }
            }
            
            gunSprites[0].setPosition(xPos - 120, yPos + weaponDispOffset);
            gunSprites[1].setPosition(xPos, yPos + weaponDispOffset);
            gunSprites[2].setPosition(xPos + 120, yPos + weaponDispOffset);
            for (int i = 0; i < 3; i++) {
                window.draw(gunSprites[i]);
            }
            break;
            
        case State::closing:
            if (blurAmount > 0.1f) {
                blurAmount *= 0.92f;
                if (blurAmount < 0.1f) {
                    blurAmount = 0.1f;
                    state = State::closed;
                    visible = false;
                }
            }
            
            if (weaponDispOffset < yPos * 2) {
                weaponDispOffset *= 1.2;
                if (weaponDispOffset > yPos * 2) {
                    weaponDispOffset = yPos * 2;
                }
            }
            gunSprites[0].setPosition(xPos - 120, yPos + weaponDispOffset);
            gunSprites[1].setPosition(xPos, yPos + weaponDispOffset);
            gunSprites[2].setPosition(xPos + 120, yPos + weaponDispOffset);
            for (int i = 0; i < 3; i++) {
                window.draw(gunSprites[i]);
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
    
    if (left || right || up || down) {
        keyPressed = true;
    } else {
        keyPressed = false;
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
    
    weaponDispOffset = y * 2;
    
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

bool userInterface::isOpen() {
    return state == State::open;
}

void userInterface::setEnemyValueCount(int count) {
    enemyValueCount = count;
}
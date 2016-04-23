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
    r = 1;
    r2 = 0.5;
    circle.setRadius(r);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color(sf::Color::White));
    circle.setPointCount(70);
    circle2.setPointCount(70);
    circle2.setRadius(r);
    circle2.setFillColor(sf::Color::Transparent);
    circle2.setOutlineThickness(4);
    circle2.setOutlineColor(sf::Color(sf::Color::White));
    xPos = 0;
    yPos = 0;
    rectAlpha = 2;
    overlayRect.setFillColor(sf::Color::White);
    selCircle1.setRadius(2);
    selCircle2.setRadius(2);
    selCircle3.setRadius(2);
    selCircle4.setRadius(2);
    selCircle1.setPointCount(40);
    selCircle2.setPointCount(40);
    selCircle3.setPointCount(40);
    selCircle4.setPointCount(40);
    selCircle1.setFillColor(sf::Color::White);
    selCircle2.setFillColor(sf::Color::White);
    selCircle3.setFillColor(sf::Color::White);
    selCircle4.setFillColor(sf::Color::White);
    selectedCircle.setOutlineColor(sf::Color(68, 172, 255, 255));
    selectedCircle.setOutlineThickness(3);
    selectedCircle.setFillColor(sf::Color::Transparent);
    selectedCircle.setRadius(33);
    itemCircle[0].setFillColor(sf::Color(44,57,83,240));
    itemCircle[1].setFillColor(sf::Color(44,57,83,240));
    itemCircle[2].setFillColor(sf::Color(44,57,83,240));
    itemCircle[3].setFillColor(sf::Color(44,57,83,240));
    weaponNameUnderscore.setFillColor(sf::Color(210, 210, 210));
    weaponNameUnderscore.setSize(sf::Vector2f(90, 1));
    blurAmount = 0.1;
    angle = 275;
    closing = 0;
    deathSeqComplete = false;
    textDisplacement = 0;
    canHeal = true;
    
    // Load textures in from a sprite sheet
    for (int i = 0; i < 29; i++) {
        letterTextures[i].loadFromFile(resourcePath() + "alphabetSheet.png", sf::IntRect(1 + i * 7, 0, 6, 9));
        inverseLetterTextures[i].loadFromFile(resourcePath() + "alphabetSheetInverse.png", sf::IntRect(i * 7, 0, 8, 9));
    }
    
    sf::Color c(255,255,255,2);
    deathTextTexture.loadFromFile(resourcePath() + "deathText.png");
    deathTextSprite.setTexture(deathTextTexture);
    deathTextSprite.setColor(c);
    
    deathShadowTxt.loadFromFile(resourcePath() + "deathShadow.png");
    deathShadowSpr.setTexture(deathShadowTxt);
    deathShadowSpr.setColor(c);
    
    // Load in all of the item textures
    for (int i = 0; i < 6; i++) {
        itemTextures[i].loadFromFile(resourcePath() + "items.png", sf::IntRect(i * 66, 0, 66, 34));
        items[i] = 0;
        weaponNames[i].loadFromFile(resourcePath() + "weaponNames.png", sf::IntRect(0, i * 6, 80, 6));
    }
    
    
    selected = 0;
    msgOpenSignal = false;
    msgOpened = false;
    msgVisible = false;
    txtShadowTexture.loadFromFile(resourcePath() + "overworldTextShadow.png");
    txtShadowSprite.setTexture(txtShadowTexture);
    selectorShadowTexture.loadFromFile(resourcePath() + "itemSelectorVignette.png");
    selectorShadowSprite.setTexture(selectorShadowTexture);
    deathSeq = false;
    weaponName.setTexture(weaponNames[0]);
    weaponName.setColor(sf::Color(210, 210, 210));
}

bool userInterface::drawMenu(sf::RenderWindow& window, Player* player, unsigned char * detailStates, FontController& f, effectsController& ef, float xOffset, float yOffset, InputController* pInput) {
    bool c = pInput->cPressed();
    bool left = pInput->leftPressed();
    bool right = pInput->rightPressed();
    bool up = pInput->upPressed();
    bool down = pInput->downPressed();
    
    if (detailStates[0] == 1 && !msgOpenSignal) {
        msgOpenSignal = true;
        msgVisible = true;
    }
    
    // Draw ui bubbles if there are any to draw
    if (!uiBubbles.empty()) {
        for (auto it = uiBubbles.begin(); it != uiBubbles.end();) {
            // If the bubble has timed out and should be removed
            if (it->getKillFlag()) {
                it = uiBubbles.erase(it);
            }
            
            else {
                it->update(window);
                ++it;
            }
        }
    }
    
    if (deathSeq) {
        // During the player death sequence apply a vignette effect across the window
        sf::Color c = deathShadowSpr.getColor();
        if (c.a < 246 && !deathSeqComplete) {
            c.a += 4;
            deathShadowSpr.setColor(c);
            deathTextSprite.setColor(c);
        }
        else {
            deathSeqComplete = true;
        }
        
        window.draw(deathShadowSpr);
        f.drawDeathText(c.a, window);
        //window.draw(deathTextSprite);
    }
    
    if (c && !closing && !msgVisible) {
        player->deActivate();
        visible = 1;
        closing = 0;
        if (r < 50) {
            r *= 1.3;
            r2 = r * 2;
            rectAlpha *= 1.3;
            if (r > 50) {
                r = 50;
            }
            
            if (r2 > 100) {
                r2 = 100;
            }
            
            if (rectAlpha > 125) {
                rectAlpha = 125;
            }
            
            blurAmount *= 1.2;
            if (blurAmount > 0.99999)
                blurAmount = 0.99999;
            
            circle.setRadius(r);
            circle.setPosition(xPos - r, yPos - r);
            circle2.setRadius(r2);
            circle2.setPosition(xPos - r2, yPos - r2);
            
            overlayRect.setFillColor(sf::Color(255 - blurAmount * 2, 255 - blurAmount * 2, 255 - blurAmount * 2));
            
            //if (selectorShadowSprite.getColor().a < 240)
            //    selectorShadowSprite.setColor(sf::Color(255,255,255,selectorShadowSprite.getColor().a + 14));

            selCircle1.setPosition(xPos + r2 / 1.3 - 2, yPos - 2);
            selCircle2.setPosition(xPos - r2 / 1.3 - 2, yPos - 2);
            selCircle3.setPosition(xPos - 2, yPos + r2 / 1.3 - 2);
            selCircle4.setPosition(xPos - 2, yPos - r2 / 1.3 - 2);
            
            itemCircle[0].setPosition(xPos - r / 1.5, yPos - r2 / 1.1 - r / 1.5);
            itemCircle[0].setRadius(r/1.5);
            
            itemCircle[1].setPosition(xPos + r2 / 1.1 - r / 1.5, yPos - r / 1.5);
            itemCircle[1].setRadius(r/1.5);
            
            itemCircle[3].setPosition(xPos - r2 / 1.1 - r / 1.5, yPos - r / 1.5);
            itemCircle[3].setRadius(r/1.5);
            
            itemCircle[2].setPosition(xPos - r / 1.5, yPos + r2 / 1.1 - r / 1.5);
            itemCircle[2].setRadius(r/1.5);
        }
        
        if (r > 35) {
            if (up && items[0] != 0) {
                selectedCircle.setPosition(xPos - 33, yPos - 124);
                weaponName.setTexture(weaponNames[items[0] - 1]);
                selected = 0;
            }
        
            if (down && items[2] != 0) {
                selectedCircle.setPosition(xPos - 33, yPos + 58);
                weaponName.setTexture(weaponNames[items[2] - 1]);
                selected = 2;
            }
        
            if (left && items[3] != 0) {
                selectedCircle.setPosition(xPos - 124, yPos - 33);
                weaponName.setTexture(weaponNames[items[3] - 1]);
                selected = 3;
            }
        
            if (right && items[1] != 0) {
                selectedCircle.setPosition(xPos + 58, yPos - 33);
                weaponName.setTexture(weaponNames[items[1] - 1]);
                selected = 1;
            }
        }
    }
    
    else {
        if (!msgOpenSignal) {
            player->activate();
        }
        if (r > 2) {
            closing = 1;
            r *= 0.87;
            r2 *= 0.85;
            rectAlpha *= 0.87;
            circle.setRadius(r);
            circle.setPosition(xPos - r, yPos - r);
            circle2.setRadius(r2);
            circle2.setPosition(xPos - r2, yPos - r2);
            overlayRect.setFillColor(sf::Color(255 - blurAmount * 2, 255 - blurAmount * 2, 255 - blurAmount * 2));
            selCircle1.setPosition(xPos + r2 / 1.3 - 2, yPos - 2);
            selCircle2.setPosition(xPos - r2 / 1.3 - 2, yPos - 2);
            selCircle3.setPosition(xPos - 2, yPos + r2 / 1.3 - 2);
            selCircle4.setPosition(xPos - 2, yPos - r2 / 1.3 - 2);
            
            blurAmount *= 0.92;
            if (blurAmount < 0.1)
                blurAmount = 0.1;
           
            itemCircle[0].setPosition(xPos - r / 1.5, yPos - r2 / 1.1 - r / 1.5);
            itemCircle[0].setRadius(r/1.5);
            
            itemCircle[1].setPosition(xPos + r2 / 1.1 - r / 1.5, yPos - r / 1.5);
            itemCircle[1].setRadius(r/1.5);
            
            itemCircle[3].setPosition(xPos - r2 / 1.1 - r / 1.5, yPos - r / 1.5);
            itemCircle[3].setRadius(r/1.5);
            
            itemCircle[2].setPosition(xPos - r / 1.5, yPos + r2 / 1.1 - r / 1.5);
            itemCircle[2].setRadius(r/1.5);
            
            //if (selectorShadowSprite.getColor().a > 15)
            //    selectorShadowSprite.setColor(sf::Color(255,255,255,selectorShadowSprite.getColor().a - 14));
            
        }
        else if (visible) {
            visible = 0;
            r = 1;
            r2 = 0.5;
            closing = 0;
            rectAlpha = 2;
            //selectorShadowSprite.setColor(sf::Color(255,255,255,1));
        }
    }
    
    if (visible) {
        //window.draw(overlayRect, sf::BlendMultiply);
        window.draw(selectorShadowSprite);
        window.draw(circle);
        window.draw(circle2);
        if (rectAlpha > 100) {
            window.draw(weaponName);
            window.draw(weaponNameUnderscore);
            f.resetWPText();
            f.resetHPText();
        }
        
        if (r > 35) {
            window.draw(selectedCircle);
        }
        
        if (items[0] == 0) {
            window.draw(selCircle4);
        } else {
            window.draw(itemCircle[0]);
            if (rectAlpha > 100) {
                window.draw(itemSprites[0]);
            }
        }
        
        if (items[1] == 0) {
            window.draw(selCircle1);
        } else {
            window.draw(itemCircle[1]);
            if (rectAlpha > 100) {
                window.draw(itemSprites[1]);
            }
        }
        
        if (items[3] == 0) {
            window.draw(selCircle2);
        } else {
            window.draw(itemCircle[3]);
            if (rectAlpha > 100) {
                window.draw(itemSprites[3]);
            }
        }
        
        if (items[2] == 0) {
            window.draw(selCircle3);
        } else {
            window.draw(itemCircle[2]);
            if (rectAlpha > 100) {
                window.draw(itemSprites[2]);
            }
        }
    }
    
    return (!closing && c) || closing;
}

void userInterface::setPosition(float x, float y) {
    weaponName.setPosition(x - 40, y - 130);
    weaponNameUnderscore.setPosition(x - 45, y - 122);
    circle.setPosition(x, y);
    xPos = x;
    yPos = y + 16;
    sf::Vector2f v1(x * 2,y * 2);
    overlayRect.setSize(v1);
    itemSprites[0].setPosition(x - 33, y - 90);
    itemSprites[1].setPosition(x + 58, y);
    itemSprites[3].setPosition(x - 126, y);
    itemSprites[2].setPosition(x - 33, y + 90);
    selectedCircle.setPosition(x - 33, y - 108);
    
    // Set the size of the shadow gradient to draw when displaying text
    txtShadowSprite.setScale((2 * x)/450, (2 * y)/450);
    txtShadowSprite.setColor(sf::Color(255,255,255,4));
    
    for (auto & element : textToDisplay) {
        element.setColor(sf::Color(255,255,255,1));
    }
    
    selectorShadowSprite.setColor(sf::Color(255,255,255,1));
    selectorShadowSprite.setScale((x * 2) / 450, (y * 2) / 450);
    deathTextSprite.setPosition(x - 239 / 2, 6);
    deathShadowSpr.setScale((x * 2) / 450, (y * 2) / 450);
}

void userInterface::addItem(char newItem, effectsController& ef, float xStart, float yStart, FontController& fonts, Player& player) {
    if (newItem == 90) {
        fonts.updateMaxHealth(fonts.getMaxHealth() + 1);
    } else {
        for (int i = 0; i < 4; i++) {
            if (items[i] == 0) {
                itemSprites[i].setTexture(itemTextures[newItem]);
                items[i] = newItem + 1;
                if (items[i] != 1) {
                    sf::Sprite tempSprite(itemTextures[newItem]);
                    UIBubble newBubble(xPos, yPos, &tempSprite);
                    uiBubbles.push_back(newBubble);
                }
                //ef.addNewItem(xStart, yStart, fonts);
                // Found an empty spot, exit loop
                break;
            } else if (items[i] == newItem + 1) {
                ef.addLvP30(xStart, yStart, fonts);
                break;
            }
        }
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
    items[0] = 1;
    for (int i = 1; i < 4; i++)
        items[i] = 0;
    
    weaponName.setTexture(weaponNames[items[0] - 1]);
    deathSeq = false;
    deathSeqComplete = false;
    deathShadowSpr.setColor(sf::Color(255,255,255,2));
    deathTextSprite.setColor(sf::Color(255,255,255,2));
}

bool userInterface::isVisible() {
    return visible;
}

void userInterface::setEnemyValueCount(int count) {
    enemyValueCount = count;
}

char userInterface::getCurrentItem() {
    // Return the current selected item
    return items[selected];
}

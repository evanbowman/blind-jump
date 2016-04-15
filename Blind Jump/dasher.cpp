//
//  dasher.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/11/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "dasher.hpp"
#include <cmath>
#include "angleFunction.hpp"
#include "wallinpath.hpp"

//// LOW LEVEL ENEMY, BUT NOT WEAK. ONLY A FEW PER EARLY MAPS

DasherBlur::DasherBlur(sf::Sprite* spr, float xInit, float yInit) {
    this->spr = *spr;
    this->xInit = xInit;
    this->yInit = yInit;
    killflag = false;
    sf::Color c = this->spr.getColor();
    c.a -= 90;
    c.r -= 30;
    c.g -= 30;
    c.b -= 10;
    this->spr.setColor(c);
}

sf::Sprite* DasherBlur::getSprite() {
    sf::Color c = spr.getColor();
    if (c.a > 20) {
        c.a -= 15;
        spr.setColor(c);
    }
    else {
        killflag = true;
    }
    return &spr;
}

bool DasherBlur::getKillFlag() {
    return killflag;
}

Dasher::Dasher(sf::Sprite* sprs) : EnemyParent(sprs) {
    for (int i = 0; i < 21; i++) {
        this->sprs[i] = sprs[i];
        this->sprs[i].setOrigin(14, 8);
    }
    // Don't want enemies' movements to be synchronized!
    int offset = rand() % 50 + 100;
    dashCnt = 150 + offset;
    isDashing = false;
    frameIndex = 0;
    hspeed = 0;
    vspeed = 0;
    blurCountDown = 3;
    health = 8;
    deathSeq = false;
    frameRate = 3;
}

sf::Sprite* Dasher::getSprite() {
    return &sprs[frameIndex];
}

void Dasher::checkBulletCollision(effectsController& ef, FontController& fonts) {
    if (!deathSeq) {
        //Check collisions with player's shots, but only if the shot vectors aren't empty
        if (!ef.getBulletLayer1().empty()) {
            for (auto & element : ef.getBulletLayer1()) {
                if (std::abs(element.getXpos() - (xPos - 6)) < 10 && std::abs(element.getYpos() - (yPos)) < 12 && !isColored) {
                    element.setKillFlag();           // Kill the bullet if there's a collision between the bullet and the enemy
                    // Tons of effects in one place is distracting, so don't draw another one if the enemy is about to explode
                    if (health == 1) {
                        element.disablePuff();
                    }
                    health -= 1;
                    isColored = true;
                    colorCount = 5;
                }
            }
        }

        if (!ef.getBulletLayer2().empty()) {
            for (auto & element : ef.getBulletLayer2()) {
                if (std::abs(element.getXpos() - (xPos - 6)) < 10 && std::abs(element.getYpos() - (yPos)) < 12 && !isColored) {
                    element.setKillFlag();
                    if (health == 1) {
                        element.disablePuff();
                    }
                    health -= 1;
                    isColored = 1;
                    colorCount = 5;
                }
            }
        }
    }
    
    if (isColored) {
        if (--colorCount == 0) {
            isColored = false;
        }
    }
    
    if (health == 0 && deathSeq == false) {
        // Play the character death sequence
        deathSeq = true;
        // Set the frame index to the start of the death animation
        frameIndex = 6;
        if ((rand() % 4) == 0) {
            ef.addHearts(xInit, yInit);
        }
        ef.addSmallExplosion(xInit, yInit);
        blurEffects.clear();
    }
}

void Dasher::update(float xOffset, float yOffset, std::vector<wall> walls, effectsController& ef, FontController& fonts) {
    // Update the object's position variables
    setPosition(xOffset, yOffset);
    checkBulletCollision(ef, fonts);
    // Update the sprite positions
    for (int i = 0; i < 21; i++) {
        sprs[i].setPosition(xPos + 4, yPos);
    }
    sprs[3].setPosition(xPos + 4, yPos + 2);
    
    if (!deathSeq) {
        if (!isDashing) {
            // Flip the sprite to face the player
            if (xPos > playerPosX) {
                sf::Vector2f scaleVec(1, 1);
                for (int i = 0; i < 21; i++) {
                    sprs[i].setScale(scaleVec);
                }
            }
            
            else {
                sf::Vector2f scaleVec(-1, 1);
                for (int i = 0; i < 21; i++) {
                    sprs[i].setScale(scaleVec);
                }
            }

            if (--dashCnt == 0) {
                dashCnt = 29;
                isDashing = true;
                frameIndex = 2;
                
                // Pick a random direction to move in, with 50% chance of moving toward the player
                float dir;
                
                if (std::abs(xPos - playerPosX) > 80 && std::abs(yPos - playerPosY) > 80) {
                    dir = atan((yPos - playerPosY) / (xPos - playerPosX));
                    if (!wallInPath(walls, dir, xPos, yPos)) {
                        hspeed = cos(dir) * 5;
                        vspeed = sin(dir) * 5;
                        if (xPos > playerPosX) {
                            hspeed = hspeed * -1;
                            vspeed = vspeed * -1;
                        }
                    }
                    
                    else {
                        dir = rand() % 359;
                        do {
                            dir += 12;
                        } while (wallInPath(walls, dir, xPos, yPos));
                        
                        hspeed = cos(dir) * 5;
                        vspeed = sin(dir) * 5;
                    }
                }
                
                else {
                    dir = rand() % 359;
                    do {
                        dir += 12;
                    } while (wallInPath(walls, dir, xPos, yPos));
                    
                    hspeed = cos(dir) * 5;
                    vspeed = sin(dir) * 5;
                }
            }
            
            // These next lines are for the purpose of animating the character
            if (dashCnt < 20 && dashCnt > 0) {
                frameIndex = 1;
            }
            
            if (dashCnt == 148) {
                if (rand() % 2) {
                    dashCnt = 10;
                }
            }
            
            if (dashCnt == 146) {
                frameIndex = 4;
            }
            
            else if (dashCnt == 145) {
                frameIndex = 5;
            }
            
            else if (dashCnt == 23) {
                frameIndex = 4;
            }
            
            else if (dashCnt == 120 || dashCnt == 118 || dashCnt == 116) {
                if (xPos > playerPosX) {
                    ef.addDasherShot(xInit - 12, yInit - 12, angleFunction(xPos + 18, yPos, playerPosX, playerPosY) + 15);
                    ef.addTurretFlash(xInit - 12, yInit - 12);
                }
                
                else {
                    ef.addDasherShot(xInit + 4, yInit - 12, angleFunction(xPos + 18, yPos, playerPosX, playerPosY) + 15);
                    ef.addTurretFlash(xInit + 4, yInit - 12);
                }
            }
            
            else if (dashCnt == 100 || dashCnt == 98 || dashCnt == 96) {
                if (xPos > playerPosX) {
                    ef.addDasherShot(xInit - 12, yInit - 12, angleFunction(xPos + 18, yPos, playerPosX, playerPosY) - 15);
                    ef.addTurretFlash(xInit - 12, yInit - 12);
                }
                
                else {
                    ef.addDasherShot(xInit + 4, yInit - 12, angleFunction(xPos + 18, yPos, playerPosX, playerPosY) - 15);
                    ef.addTurretFlash(xInit + 4, yInit - 12);
                }
            }
            
            else if (dashCnt == 80 || dashCnt == 78 || dashCnt == 76) {
                if (xPos > playerPosX) {
                    ef.addDasherShot(xInit - 12, yInit - 12, angleFunction(xPos + 18, yPos, playerPosX, playerPosY));
                    ef.addTurretFlash(xInit - 12, yInit - 12);
                }
                
                else {
                    ef.addDasherShot(xInit + 4, yInit - 12, angleFunction(xPos + 18, yPos, playerPosX, playerPosY));
                    ef.addTurretFlash(xInit + 4, yInit - 12);
                }
            }
        }

        else {
            // Check for collisions with walls, with a certain radius constraint
            bool foundCollision = ::checkWallCollision(walls, 48, xPos, yPos);
            // Redirect the enemy if a collision occurs with a wall
            if (foundCollision) {
                hspeed *= -1;
                vspeed *= -1;
            }
            
            // If counter reaches 0, switch state variable
            if (--dashCnt == 0) {
                dashCnt = 150;
                frameIndex = 0;
                isDashing = false;
            }
            
            if (dashCnt == 23 || dashCnt == 14) {
                hspeed *= 0.6;
                vspeed *= 0.6;
            }
            
            if (dashCnt > 20) {
                // Create motion blur
                if (--blurCountDown == 0) {
                    blurCountDown = 3;
                    DasherBlur b (&sprs[2], xInit + 4, yInit);
                    blurEffects.push_back(b);
                }
            }
            
            if (dashCnt < 15) {
                frameIndex = 1;
                hspeed = 0;
                vspeed = 0;
                blurCountDown = 3;
            }

            else {
                // Flip the enemy's sprites according to the direction it will be moving in
                if (hspeed > 0) {
                    sf::Vector2f scaleVec(-1, 1);
                    for (int i = 0; i < 21; i++) {
                        sprs[i].setScale(scaleVec);
                    }
                }
                
                else {
                    sf::Vector2f scaleVec(1, 1);
                    for (int i = 0; i < 21; i++) {
                        sprs[i].setScale(scaleVec);
                    }
                }
            }
        }

        if (!blurEffects.empty()) {
            for (std::vector<DasherBlur>::iterator it = blurEffects.begin(); it != blurEffects.end();) {
                if (it->getKillFlag()) {
                    it = blurEffects.erase(it);
                }
                
                else {
                    it->getSprite()->setPosition(it->xInit + xOffset, it->yInit + yOffset);
                    ++it;
                }
            }
        }

        // Move the object based on current speed
        xInit += hspeed;
        yInit += vspeed;
    }
    
    // If it's time to play the death sequence
    else {
        if (--frameRate == 0) {
            if (frameIndex < 16) {
                frameRate = 3;
                if (!::checkWallCollision(walls, 48, xPos, yPos))
                    xInit += 0.5 * sprs[frameIndex].getScale().x;
            }
            
            else {
                frameRate = 4;
                if (!::checkWallCollision(walls, 48, xPos, yPos))
                    xInit += 0.35 * sprs[frameIndex].getScale().x;
            }
            
            if (frameIndex == 20) {
                killFlag = true;
            }
            
            if (frameIndex < 20) {
                frameIndex++;
            }
        }
    }
}

void Dasher::softUpdate(float xOffset, float yOffset) {
    setPosition(xOffset, yOffset);
}

sf::Sprite* Dasher::getShadow() {
    return &sprs[3];
}

std::vector<DasherBlur>* Dasher::getBlurEffects() {
    return &blurEffects;
}

bool Dasher::shakeReady() {
    return (frameIndex == 6 and frameRate == 1);
}

bool Dasher::dying() {
    return deathSeq;
}

bool Dasher::scrapReady() {
    return (frameIndex == 19 and frameRate == 1);
}

bool Dasher::colored() {
    return isColored;
}


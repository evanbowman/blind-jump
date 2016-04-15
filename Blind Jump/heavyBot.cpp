//
//  heavyBot.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/10/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "heavyBot.hpp"
#include "tileController.hpp"
#include <cmath>

HeavyBot::HeavyBot(sf::Sprite* inpSprs, short map[61][61]) : EnemyParent(inpSprs) {
    for (int i = 0; i < 17; i++) {
        sprites[i] = inpSprs[i];
        sprites[i].setOrigin(20, 16);
    }
    frameIndex = 0;
    frameRate = 4;
    this->map = map;
    health = 18;
    state = DORMANT;
}

sf::Sprite* HeavyBot::getSprite() {
    switch (state) {
        case RUN:
            // Flip the sprite to face the player always do when running
            if (xPos > playerPosX) {
                sf::Vector2f scaleVec(1, 1);
                sprites[frameIndex].setScale(scaleVec);
                sprites[7].setScale(scaleVec);
            }
            else {
                sf::Vector2f scaleVec(-1, 1);
                sprites[frameIndex].setScale(scaleVec);
                sprites[7].setScale(scaleVec);
            }
            break;
            
        case SHOOT:
            if (runShootAnim) {
                if (xPos > playerPosX) {
                    sf::Vector2f scaleVec(1, 1);
                    sprites[frameIndex].setScale(scaleVec);
                    sprites[7].setScale(scaleVec);
                }
                else {
                    sf::Vector2f scaleVec(-1, 1);
                    sprites[frameIndex].setScale(scaleVec);
                    sprites[7].setScale(scaleVec);
                }
            }
            
        default:
            //
            break;
    }
    
    sprites[frameIndex].setPosition(xPos + 4, yPos);
    return &sprites[frameIndex];
}

sf::Sprite* HeavyBot::getShadow() {
    sprites[7].setPosition(xPos + 4, yPos + 4);
    return &sprites[7];
}

void HeavyBot::checkBulletCollision(effectsController& ef, FontController& font) {
    //Check collisions with player's shots, but only if the shot vectors aren't empty
    if (!ef.getBulletLayer1().empty()) {
        for (auto & element : ef.getBulletLayer1()) {
            if (std::abs(element.getXpos() - (xPos)) < 12 && std::abs(element.getYpos() - (yPos - 8)) < 12 && !isColored) {
                element.setKillFlag();           // Kill the bullet if there's a collision between the bullet and the enemy
                // Tons of effects in one place is distracting, so don't draw another one if the enemy is about to explode
                if (health == 1) {
                    element.disablePuff();
                }
                health -= 1;
                isColored = true;
                colorCount = 7;
            }
        }
    }
    if (!ef.getBulletLayer2().empty()) {
        for (auto & element : ef.getBulletLayer2()) {
            if (std::abs(element.getXpos() - (xPos - 4)) < 8 && std::abs(element.getYpos() - (yPos - 8)) < 8 && !isColored) {
                element.setKillFlag();
                if (health == 1) {
                    element.disablePuff();
                }
                health -= 1;
                isColored = true;
                colorCount = 7;
            }
        }
    }
    
    if (isColored) {
        if (--colorCount == 0) {
            isColored = false;
        }
    }
    
    if (health == 0) {
        killFlag = 1;
        ef.addLvP10(playerPosX - xOffset - 6, playerPosY - yOffset, font);
        ef.addExplosion(xInit - 16, yInit - 16);
    }
}

void HeavyBot::update(float xOffset, float yOffset, effectsController& ef, FontController& fonts, tileController* pTiles) {
    setPosition(xOffset, yOffset);
    checkBulletCollision(ef, fonts);
    switch (state) {
        case DORMANT:
            if (fabsf(xPos - playerPosX) < 150 && fabsf(yPos - playerPosY) < 150) {
                state = RUN;
                frameIndex = 1;
                frameRate = 4;
            }
            break;
            
        case RUN:
            if (--frameRate == 0) {
                frameIndex++;
                frameRate = 4;
                if (frameIndex > 6) {
                    frameIndex = 1;
                }
            }
            
            if (path.empty() || recalc == 0) {
                recalc = 32;
                
                aStrCoordinate origin, target;
                origin.x = (xPos - pTiles->posX - xOffset) / 32;
                origin.y = (yPos - pTiles->posY - yOffset) / 26;
                target.x = (pTiles->posX - playerPosX + xOffset) / -32;
                target.y = (pTiles->posY - playerPosY - 26 + yOffset) / -26;
                if (map[target.x][target.y] == 3 || map[target.x][target.y] == 4 || map[target.x][target.y] == 5 || map[target.x][target.y] == 11 || map[target.x][target.y] == 8) {
                    path = astar_path(target, origin, map);
                    previous = path.back();
                    path.pop_back();
                    xInit = ((xPos - pTiles->posX - xOffset) / 32) * 32 + pTiles->posX;
                    yInit = ((yPos - pTiles->posY - yOffset) / 26) * 26 + pTiles->posY;
                    // Calculate the direction to move in, based on the coordinate of the previous location and the coordinate of the next location
                    currentDir = atan2(yInit - (((path.back().y * 26) + 4 + pTiles->posY)), xInit - (((path.back().x * 32) + 4 + pTiles->posX)));
                }
            }
            
            // If the path is not empty
            else {
                // Add each component of the direction vector to the enemy's position datafields
                xInit -= 3.0 * cos(currentDir);
                yInit -= 3.0 * sin(currentDir);
                // If the enemy is sufficiently close to the target point, pop it and work on the next one
                if (fabs(xInit - (((path.back().x * 32) + 4 + pTiles->posX))) < 8 && fabs(yInit - (((path.back().y * 26) + 4 + pTiles->posY))) < 8) {
                    // If the enemy is close to the player, do a beam attack
                    if (fabsf(xPos - playerPosX) < 120 && fabsf(yPos - playerPosY) < 120) {
                        state = SHOOT;
                        runShootAnim = true;
                        frameIndex = 8;
                        frameRate = 4;
                        path.clear();
                        break;
                    }
                    recalc--;
                    previous = path.back();
                    path.pop_back();
                    // Calculate the direction to move in
                    currentDir = atan2(yInit - (((path.back().y * 26) + 4 + pTiles->posY)), xInit - (((path.back().x * 32) + 4 + pTiles->posX)));
                }
            }
            
            break;
            
        case SHOOT:
            if (runShootAnim) {
                if (--frameRate == 0) {
                    frameRate = 4;
                    frameIndex++;
                    
                    if (frameIndex > 16) {
                        frameIndex = 16;
                        runShootAnim = false;
                        frameRate = 51;
                    }
                }
            }
            
            else {
                if (frameRate == 50) {
                    shotDir = atan2f(playerPosY + 26 - (yPos + 3), playerPosX - 3 - (xPos + 6.5)) * 180 / 3.141592;
                    shotLen = sqrtf(powf(playerPosY + 16 - yPos, 2) + powf(playerPosX - xPos, 2));
                    if (sprites[frameIndex].getScale().x == 1) {
                        ef.addEnergyBeam(xInit + 0.5, yInit + 2.5, shotDir, shotLen);
                    }
                    
                    else {
                        ef.addEnergyBeam(xInit + 6.5, yInit + 3, shotDir, shotLen);
                    }
                }
                
                if (--frameRate == 0) {
                    state = OVERHEAT;
                    frameRate = 40;
                }
            }
            break;
            
        case OVERHEAT:
            if (--frameRate == 0) {
                state = RUN;
                frameRate = 4;
                frameIndex = 1;
            }
            break;
            
        default:
            break;
    }
}
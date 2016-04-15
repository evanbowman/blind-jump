//
//  scoot.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/21/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "scoot.hpp"
#include <cmath>
#include "angleFunction.hpp"

#define PI 3.14159265

//// EASY LOW LEVEL ENEMY

Scoot::Scoot(sf::Sprite* inpSpr) : EnemyParent(inpSpr) {
    // Store all of the input sprites
    for (auto i = 0; i < 3; i++) {
        sprites[i] = inpSpr[i];
        sprites[i].setOrigin(6, 6);
    }
    frameCountdown = 10 + rand() % 30;
    frameIndex = rand() % 2;
    // Start the enemy moving in a random direction
    float dir = rand() % 359;
    hSpeed = cos(dir) * 0.5;
    vSpeed = sin(dir) * 0.5;
    // Offset each enemy object so they don't all do the same thing at once
    unsigned char offset = (unsigned char) rand() % 240;
    changeDirCounter = offset;
    shotCountdown = 80 + offset;
    health = 2;
}

void Scoot::randDir() {
    float dir = rand() % 359;
    hSpeed = cos(dir) * 0.5;
    vSpeed = sin(dir) * 0.5;
}

void Scoot::checkBulletCollision(effectsController& ef, FontController& font) {
    //Check collisions with player's shots, but only if the shot vectors aren't empty
    if (!ef.getBulletLayer1().empty()) {
        for (auto & element : ef.getBulletLayer1()) {
            if (std::abs(element.getXpos() - (xPos - 6)) < 6 && std::abs(element.getYpos() - (yPos - 6)) < 6 && !isColored) {
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
            if (std::abs(element.getXpos() - (xPos - 6)) < 6 && std::abs(element.getYpos() - (yPos - 6)) < 6 && !isColored) {
                element.setKillFlag();
                if (health == 1) {
                    element.disablePuff();
                }
                health -= 1;
                isColored = true;
                colorCount = 5;
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
        if ((rand() % 5) == 0) {
            ef.addHearts(xInit, yInit);
        }
        ef.addFireExplosion(xInit, yInit - 2);
    }
}

void Scoot::update(float xOffset, float yOffset, std::vector<wall> w, effectsController & ef, FontController& font) {
    // Update the enemy's position
    setPosition(xOffset, yOffset);
    checkBulletCollision(ef, font);
    for (auto i = 0; i < 2; i++) {
        sprites[i].setPosition(xPos, yPos);
    }
    sprites[2].setPosition(xPos, yPos + 10);
    // Check for collisions with walls, with a certain radius constraint
    bool foundCollision = checkCollisionWall(w, 48);
    // Redirect the enemy if a collision occurs with a wall
    if (foundCollision) {
        hSpeed *= -1;
        vSpeed *= -1;
    }
    
    // Flip the sprite to face the player
    if (xPos > playerPosX) {
        sf::Vector2f scaleVec(1, 1);
        sprites[0].setScale(scaleVec);
        sprites[1].setScale(scaleVec);
    }
    else {
        sf::Vector2f scaleVec(-1, 1);
        sprites[0].setScale(scaleVec);
        sprites[1].setScale(scaleVec);
    }
    xInit += hSpeed;
    yInit += vSpeed;
    
    if (--changeDirCounter == 0) {
        changeDirCounter = 80;
        if (rand() % 2) {
            float dir = rand() % 359;
            hSpeed = cos(dir) * 0.5;
            vSpeed = sin(dir) * 0.5;
        }
        else {
            float dir = atan((yPos - playerPosY) / (xPos - playerPosX));
            hSpeed = cos(dir) * 0.5;
            vSpeed = sin(dir) * 0.5;
            // To correct for negative sine and cosine function outputs
            if (xPos > playerPosX) {
                hSpeed *= -1;
                vSpeed *= -1;
            }
        }
    }
    if (changeDirCounter == 30) {
        hSpeed *= 0.5;
        vSpeed *= 0.5;
    }
    
    if (--shotCountdown == 0) {
        shotCountdown = 240;
        // Push back away from the player and shoot some lasers
        ef.addTurretFlash(xInit - 8, yInit - 12);
        ef.addScootShot(xInit - 8, yInit - 12, angleFunction(xPos -8, yPos - 8, playerPosX, playerPosY), playerPosX, playerPosY);
        ef.addScootShot(xInit - 8, yInit - 12, angleFunction(xPos -8, yPos - 8, playerPosX, playerPosY) + 28, playerPosX, playerPosY);
        ef.addScootShot(xInit - 8, yInit - 12, angleFunction(xPos -8, yPos - 8, playerPosX, playerPosY) - 28, playerPosX, playerPosY);
        float dir = atan((yPos - playerPosY) / (xPos - playerPosX));
        hSpeed = -cos(dir) * 3.0;
        vSpeed = -sin(dir) * 3.0;
        // To correct for negative sine and cosine function outputs
        if (xPos > playerPosX) {
            hSpeed *= -1;
            vSpeed *= -1;
        }
    }
    // Slow down the enemy as it recoils from shooting
    if (shotCountdown == 238 || shotCountdown == 236 || shotCountdown == 234 || shotCountdown == 232) {
        hSpeed *= 0.75;
        vSpeed *= 0.75;
    }
}

void Scoot::softUpdate(float xOffset, float yOffset) {
    // Update the enemy's position
    setPosition(xOffset, yOffset);
    for (auto i = 0; i < 2; i++) {
        sprites[i].setPosition(floorf(xPos), floorf(yPos));
    }
}

sf::Sprite* Scoot::getSprite() {
    // Step through the frames of the animation
    if (--frameCountdown == 0) {
        frameCountdown = 5;
        if (frameIndex == 0) {
            frameIndex = 1;
        }
        else {
            frameIndex = 0;
        }
    }
    return &sprites[frameIndex];
}

sf::Sprite* Scoot::getShadow() {
    return &sprites[2];
}

bool Scoot::colored() {
    return isColored;
}

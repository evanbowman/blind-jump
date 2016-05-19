//
//  energyBeam.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/10/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "energyBeam.hpp"

EnergyBeam::EnergyBeam(float xInit, float yInit, sf::Sprite* inpSprs, float dir, float length) {
    this->xInit = xInit;
    this->yInit = yInit;
    for (int i = 0; i < 6; i++) {
        sprites[i] = inpSprs[i];
        sprites[i].setRotation(dir);
        sprites[i].setOrigin(0, 16);
    }
    beamShape.setRotation(dir);
    beamShape.setSize(sf::Vector2f(length, 2));
    beamShape.setOrigin(0, 1);
    beamShape.setFillColor(sf::Color(104, 255, 229));
    beamShape.setOutlineColor(sf::Color(104, 255, 229));
    beamShape.setOutlineThickness(0);
    frameIndex = 0;
    frameRate = 2;
    valid = false;
    state = entering;
    if (rand() % 2) {
        rotationDir = -1;
    }
    else {
        rotationDir = 1;
    }
}

void EnergyBeam::update(float xOffset, float yOffset) {
    xPos = xInit + xOffset;
    yPos = yInit + yOffset;
    
    switch (state) {
        case entering:
            if (--frameRate == 0) {
                frameRate = 2;
                frameIndex++;
                if (frameIndex > 2) {
                    state = running;
                    frameRate = 6;
                    valid = true;
                }
            }
            break;
            
        case running:
            // Make the beam pulse by adjusting its border thickness
            if (rand() % 2) {
                beamShape.setOutlineThickness(1);
            }
            
            else {
                beamShape.setOutlineThickness(0);
            }
            
            
            if (--frameRate == 0) {
                frameRate = 4;
                state = leaving;
            }
            break;
            
        case leaving:
            if (--frameRate == 0) {
                frameRate = 4;
                frameIndex++;
                if (frameIndex > 5) {
                    frameIndex = 5;
                    killFlag = true;
                }
            }
            
        default:
            // Control flow should never hit here...
            break;
    }
}

void EnergyBeam::draw(sf::RenderTexture& window) {
    switch (state) {
        case entering:
            sprites[frameIndex].setPosition(xPos, yPos);
            window.draw(sprites[frameIndex]);
            break;
            
        case running:
            beamShape.setPosition(xPos, yPos);
            window.draw(beamShape);
            break;
            
        case leaving:
            sprites[frameIndex].setPosition(xPos, yPos);
            window.draw(sprites[frameIndex]);
            break;
            
        default:
            break;
    }
}

bool EnergyBeam::getKillFlag() {
    return killFlag;
}

float EnergyBeam::getX1() {
    return xPos;
}

float EnergyBeam::getY1() {
    return yPos;
}

float EnergyBeam::getX2() {
    float x2 = xPos + beamShape.getSize().x * cosf(beamShape.getRotation() * 3.14159 / 180);
    return x2;
}

float EnergyBeam::getY2() {
    float y2 = yPos + beamShape.getSize().x * sinf(beamShape.getRotation() * 3.14159 / 180);
    return y2;
}

bool EnergyBeam::isValid() {
    return valid;
}

void EnergyBeam::invalidate() {
    valid = false;
}

float EnergyBeam::getDir() {
    return beamShape.getRotation();
}

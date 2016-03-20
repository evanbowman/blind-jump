//
//  energyBeam.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/10/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "energyBeam.hpp"

EnergyBeam::EnergyBeam(float xInit, float yInit, sf::Sprite* inpSprs, float dir) {
    this->xInit = xInit;
    this->yInit = yInit;
    for (int i = 0; i < 6; i++) {
        sprites[i] = inpSprs[i];
        sprites[i].setRotation(dir);
        sprites[i].setOrigin(0, 16);
    }
    beamShape.setRotation(dir);
    beamShape.setSize(sf::Vector2f(800, 2));
    beamShape.setOrigin(0, 2);
    beamShape.setFillColor(sf::Color(104, 255, 229));
    beamShape.setOutlineColor(sf::Color(104, 255, 229));
    beamShape.setOutlineThickness(0);
    frameIndex = 0;
    frameRate = 4;
    state = ENTERING;
}

void EnergyBeam::update(float xOffset, float yOffset) {
    xPos = xInit + xOffset;
    yPos = yInit + yOffset;
    
    switch (state) {
        case ENTERING:
            if (--frameRate == 0) {
                frameRate = 2;
                frameIndex++;
                if (frameIndex > 2) {
                    state = RUNNING;
                    frameRate = 30;
                }
            }
            break;
            
        case RUNNING:
            // Make the beam pulse by adjusting its border thickness
            if (rand() % 2) {
                beamShape.setOutlineThickness(1);
            }
            
            else {
                beamShape.setOutlineThickness(0);
            }
            
            if (--frameRate == 0) {
                frameRate = 4;
                state = LEAVING;
            }
            break;
            
        case LEAVING:
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

void EnergyBeam::draw(sf::RenderWindow& window) {
    switch (state) {
        case ENTERING:
            sprites[frameIndex].setPosition(xPos, yPos);
            window.draw(sprites[frameIndex]);
            break;
            
        case RUNNING:
            beamShape.setPosition(xPos, yPos);
            window.draw(beamShape);
            break;
            
        case LEAVING:
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

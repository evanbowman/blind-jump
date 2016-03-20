//
//  building.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/25/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "building.hpp"
#include "tileController.hpp"

Building::Building(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

sf::Sprite* Building::getLight() {
    spotlight.setPosition(xPos + width / 2 - 32, yPos + height / 2 - 48);
    return &spotlight;
}

sf::Sprite* Building::getGlow() {
    glow.setPosition(xPos + width / 2 - 250, yPos + height / 2 - 250 + 24);
    return &glow;
}

void Building::init(float xposition, float yposition, sf::Sprite& spotlight, sf::Sprite& glow) {
    xInit = x * 32 + xposition;
    yInit = y * 26 + yposition;
    width = w * 32;
    height = h * 26;
    xInit += width;
    yInit += height;
    // Store the sprite
    this->spotlight = spotlight;
    this->spotlight.setColor(sf::Color(120, 120, 120));
    this->glow = glow;
    mask.setSize(sf::Vector2f(width, height + 52));
    mask.setFillColor(sf::Color(255, 255, 255, 255));
    int H = h + 2;
    // Create the building framework, start with a matrix of the proper size
    int framework[w * H], floor[w * H];
    // Now loop through the matrix and assign the correct values
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < w; j++) {
            if (i < 2) {
                floor[i * w + j] = 0;
            }
            
            else {
                floor[i * w + j] = 1;
            }
            
            // Corners of framework on left side
            if (j == 0) {
                if (i == 0)
                    framework[i * w + j] = 4;
                    
                else if (i == H - 3)
                    framework[i * w + j] = 2;
                
                else if (i == H - 2)
                    framework[i * w + j] = 0;
                
                else if (i == H - 1)
                    framework[i * w + j] = 6;
                
                else
                    framework[i * w + j] = 9;
            }
            
            // Corners of framework on right side
            else if (j == w - 1) {
                if (i == 0)
                    framework[i * w + j] = 5;
                
                else if (i == H - 3)
                    framework[i * w + j] = 3;
                
                else if (i == H - 2)
                    framework[i * w + j] = 1;
                
                else if (i == H - 1)
                    framework[i * w + j] = 7;
                
                else
                    framework[i * w + j] = 11;
            }
            
            else {
                if (i == 0)
                    framework[i * w + j] = 10;
                
                else
                    framework[i * w + j] = 13;
            }
        }
    }
    
    this->framework.load("houseFrameSheet.png", sf::Vector2u(32, 26), framework, w, H);
    this->floor.load("houseFloor.png", sf::Vector2u(32, 26), floor, w, H);
}

void Building::drawFramework(sf::RenderTexture &target) {
    framework.setPosition(xPos, yPos - 52);
    target.draw(framework);
}

void Building::drawFloor(sf::RenderTexture &target) {
    floor.setPosition(xPos, yPos - 52);
    target.draw(floor);
}

sf::RectangleShape Building::getMask() {
    mask.setPosition(xPos, yPos - 52);
    return mask;
}

void Building::update(float xOffset, float yOffset) {
    xPos = xInit + xOffset;
    yPos = yInit + yOffset;
}

float Building::getXpos() {
    return xPos;
}

float Building::getYpos() {
    return yPos;
}

float Building::getWidth() {
    return width;
}

float Building::getHeight() {
    return height;
}

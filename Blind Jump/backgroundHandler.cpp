//
//  backgroundHandler.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/11/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "backgroundHandler.hpp"
#include "ResourcePath.hpp"

backgroundHandler::backgroundHandler() {
    xOffset = 0;
    yOffset = 0;
    posY = 0;
    //Load in the textures for the background. There are two layer, a gradient that stays in place and a bunch of stars
    // that do a paralax scrolling thing
    if (!bkgLayer[0].loadFromFile(resourcePath() + "bkg_orbit.png")) {
        //return EXIT_FAILURE;
    }
    if (!bkgStars.loadFromFile(resourcePath() + "bkg_stars.png")) {
        //return EXIT_FAILURE;
    }
    bkgLayer[2].loadFromFile(resourcePath() + "bkg_orbit2.png");
    bkgLayer[1].loadFromFile(resourcePath() + "bkg3.png");
    //Apply textures to an array to create a bunch of stars
    bkgSprite[0].setTexture(bkgLayer[0]);
    bkgSprite[1].setTexture(bkgLayer[2]);
    bkgSprite[2].setTexture(bkgLayer[1]);
    for (int i = 0; i < 81; i++) {
        stars[i].setTexture(bkgStars);
    }
    // The starting working tile set is initialized to 0
    workingSet = 1;
}

void backgroundHandler::drawBackground(sf::RenderWindow& window) {
    switch (workingSet) {
        case 0:
            window.draw(bkgSprite[0]);
            break;
            
        case 1:
            window.draw(bkgSprite[1]);
            break;
            
        case 2:
            window.draw(bkgSprite[2]);
            break;
            
        default:
            window.draw(bkgSprite[0]);
            break;
    }
    
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            stars[i + (j * 9)].setPosition((i * 128) + (xOffset / 2) + posX - 168, (j * 128) + (yOffset / 2) + posY);
            //Don't draw the ones outside the window? Could be choppy with 128x128 sprites...
            if (stars[i + (j * 9)].getPosition().x < windowW * 2 + 128 && stars[i + (j * 9)].getPosition().x > -128 && stars[i + (j * 9)].getPosition().y < windowH * 2 + 128 && stars[i + (j * 9)].getPosition().y > -128) {
                window.draw(stars[i + (j * 9)]);
            }
        }
    }
}

void backgroundHandler::setOffset(float x, float y) {
    xOffset = x;
    yOffset = y;
}

void backgroundHandler::setPosition(float x, float y) {
    posX = x;
    posY = y;
}

void backgroundHandler::giveWindowSize(float x, float y) {
    windowW = x;
    windowH = y;
    for (auto i = 0; i < 3; i++) {
        // Scale the background sprites based on the window size, that way they always fill the game window
        bkgSprite[i].setScale(x/450, y/450);
    }
}

void backgroundHandler::setBkg(unsigned char workingSet) {
    this->workingSet = workingSet;
}

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
    xOffPrev = 0;
    yOffPrev = 0;
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
    bkgStarsFar.loadFromFile(resourcePath() + "bkg_stars_distant.png");
    
    for (int i = 0; i < STARMAP_SIZE; i++) {
        for (int j = 0; j < STARMAP_SIZE; j++) {
            starsFar[i][j].setTexture(bkgStarsFar);
            starsFar[i][j].setPosition(i * 128, j * 128);
            stars[i][j].setTexture(bkgStars);
            stars[i][j].setPosition(i * 128, j * 128);
            
        }
    }
    
    foregroundTreesTxtr.loadFromFile(resourcePath() + "introLevelMask.png");
    foregroundTreesSpr.setTexture(foregroundTreesTxtr);
    
    
    solidBkg.setFillColor(sf::Color(17, 45, 50));
    
    // The starting working tile set is initialized to 0
    workingSet = 1;
}

void backgroundHandler::reset() {
    
}

void backgroundHandler::drawForeground(sf::RenderTexture & window) {
    switch (workingSet) {
        case 0:
            window.draw(foregroundTreesSpr);
            break;
            
        default:
            break;
    }
}

void backgroundHandler::drawBackground(sf::RenderTexture& window) {
    switch (workingSet) {
        case 0:
            foregroundTreesSpr.setPosition(foregroundTreesSpr.getPosition().x - (xOffPrev - xOffset), foregroundTreesSpr.getPosition().y - (yOffPrev - yOffset));
            window.draw(solidBkg);
            break;
            
        case 1:
            window.draw(bkgSprite[1]);
            break;
            
        case 2:
            window.draw(bkgSprite[0]);
            break;
            
        default:
            window.draw(bkgSprite[0]);
            break;
    }
    
    if (workingSet != 0) {
        for (int i = 0; i < STARMAP_SIZE; i++) {
            for (int j = 0; j < STARMAP_SIZE; j++) {
                if (stars[i][j].getPosition().x < -128) {
                    stars[i][j].setPosition(stars[i][j].getPosition().x + 128 * STARMAP_SIZE, stars[i][j].getPosition().y);
                }
                
                if (stars[i][j].getPosition().x > windowW + 128) {
                    stars[i][j].setPosition(stars[i][j].getPosition().x - 128 * STARMAP_SIZE, stars[i][j].getPosition().y);
                }
                
                if (stars[i][j].getPosition().y > windowH + 128) {
                    stars[i][j].setPosition(stars[i][j].getPosition().x, stars[i][j].getPosition().y - 128 * STARMAP_SIZE);
                }
                
                if (stars[i][j].getPosition().y < -128) {
                    stars[i][j].setPosition(stars[i][j].getPosition().x, stars[i][j].getPosition().y + 128 * STARMAP_SIZE);
                }
                
                if (starsFar[i][j].getPosition().x < -128) {
                    starsFar[i][j].setPosition(starsFar[i][j].getPosition().x + 128 * STARMAP_SIZE, starsFar[i][j].getPosition().y);
                }
                
                if (starsFar[i][j].getPosition().x > windowW + 128) {
                    starsFar[i][j].setPosition(starsFar[i][j].getPosition().x - 128 * STARMAP_SIZE, starsFar[i][j].getPosition().y);
                }
                
                if (starsFar[i][j].getPosition().y > windowH + 128) {
                    starsFar[i][j].setPosition(starsFar[i][j].getPosition().x, starsFar[i][j].getPosition().y - 128 * STARMAP_SIZE);
                }
                
                if (starsFar[i][j].getPosition().y < -128) {
                    starsFar[i][j].setPosition(starsFar[i][j].getPosition().x, starsFar[i][j].getPosition().y + 128 * STARMAP_SIZE);
                }
                
                starsFar[i][j].setPosition(starsFar[i][j].getPosition().x - (xOffPrev - xOffset)/3.5, starsFar[i][j].getPosition().y - (yOffPrev - yOffset)/3.5);
                stars[i][j].setPosition(stars[i][j].getPosition().x - (xOffPrev - xOffset)/3, stars[i][j].getPosition().y - (yOffPrev - yOffset)/3);
                window.draw(starsFar[i][j]);
                window.draw(stars[i][j]);
            }
        }
    }
    
    xOffPrev = xOffset;
    yOffPrev = yOffset;
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
        bkgSprite[i].setScale(x / 450, y / 450);
    }
    
    solidBkg.setSize(sf::Vector2f(x, y));
    // Based on initial position for first room (the only place this sprite shows up in the game
    foregroundTreesSpr.setPosition(x / 2 - x / 16 - 72, y / 2 - y / 18 - 476);
}

void backgroundHandler::setBkg(unsigned char workingSet) {
    this->workingSet = workingSet;
}

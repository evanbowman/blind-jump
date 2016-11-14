//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once
#include "camera.hpp"
#include "resourceHandler.hpp"
#include <SFML/Graphics.hpp>

#define STARMAP_SIZE 7

class backgroundHandler {
private:
    sf::Texture foregroundTreesTxtr;
    framework::Sprite foregroundTreesSpr;
    sf::Texture bkgStars;
    sf::Texture bkgStarsFar;
    framework::Sprite bkgSprite;
    framework::Sprite stars[STARMAP_SIZE][STARMAP_SIZE];
    framework::Sprite starsFar[STARMAP_SIZE][STARMAP_SIZE];
    sf::CircleShape planet[2];
    sf::RectangleShape solidBkg;
    float xOffset, xOffPrev;
    float yOffset, yOffPrev;
    float posX;
    float posY;
    float windowW;
    float windowH;
    unsigned char workingSet;
    sf::RenderTexture rt;

public:
    backgroundHandler();
    void drawBackground(sf::RenderTexture &, const sf::View &, const Camera &);
    void drawForeground(sf::RenderTexture &);
    void setOffset(float, float);
    void setPosition(float, float);
    void giveWindowSize(float, float);
    void setBkg(unsigned char);
};

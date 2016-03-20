//
//  building.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/25/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef building_hpp
#define building_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include "tilemap.hpp"

class tileController;

class Building {
public:
    Building(float, float, int, int);
    Building(int, int, int, int);
    float getXpos();
    float getYpos();
    float getWidth();
    float getHeight();
    void update(float, float);
    void init(float, float, sf::Sprite&, sf::Sprite&);
    void drawFramework(sf::RenderTexture&);
    void drawFloor(sf::RenderTexture&);
    sf::RectangleShape getMask();
    // For drawing the lights
    sf::Sprite* getLight();
    sf::Sprite* getGlow();
    
private:
    // The way my code works, the map is initialized before it's position is set, so store the indices and initialize position later
    int x, y, w, h;
    float xInit, yInit, xPos, yPos, width, height;
    // Store a tilemap for the building framework, floor, etc
    TileMap framework, floor;
    // Mask for the building
    sf::RectangleShape mask;
    // Overhead light for the building, and the glow that it casts
    sf::Sprite spotlight, glow;
};

#endif /* building_hpp */

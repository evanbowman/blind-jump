#pragma once

#include "camera.hpp"
#include "coordinate.hpp"
#include "resourceHandler.hpp"
#include "wall.hpp"
#include <SFML/Graphics.hpp>
#include <queue>
#include <stack>

class tileController {
public:
    enum class Tileset { intro, regular };
    sf::Sprite transitionLvSpr;
    sf::Image tileImg[2];
    sf::Image grassSet[2];
    sf::Image grassSetEdge[2];
    tileController();
    void update();
    void draw(sf::RenderTexture &, std::vector<sf::Sprite> *,
              const sf::View &, const sf::View &);
    float posX;
    float posY;
    void setPosition(float, float);
    sf::RectangleShape shadow;
    sf::Texture mapTexture[2];
    sf::Sprite mapSprite1, mapSprite2;
    sf::RenderTexture rt, re;
    uint8_t mapArray[61][61];
    std::vector<wall> walls;
    std::vector<Coordinate> emptyMapLocations;
    Coordinate teleporterLocation;
    Coordinate getTeleporterLoc();
    float windowH;
    float windowW;
    void clear();
    // Draw a different overworld based on choice of current working set of
    // tiles
    unsigned char workingSet;
    // A function to rebuild map vectors
    void rebuild(Tileset);
    // Initial build is a flat plane
    void init();
    // Return the working set of tiles background controller access
    unsigned char getWorkingSet();
    std::vector<Coordinate> * getEmptyLocations();
    float getPosX() const;
    float getPosY() const;
    void setWindowSize(float, float);
    void reset();
};

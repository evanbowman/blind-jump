#pragma once

#include "camera.hpp"
#include "coordinate.hpp"
#include "enemyController.hpp"
#include "mappingFunctions.hpp"
#include "resourceHandler.hpp"
#include "wall.hpp"
#include <SFML/Graphics.hpp>
#include <queue>
#include <stack>

class tileController {
public:
    enum class Tileset { intro, regular };
    sf::Sprite transitionLvSpr;
    tileController();
    void update();
    void draw(sf::RenderTexture &, std::vector<sf::Sprite> *, int level,
              const sf::View &, const sf::View &);
    float posX;
    float posY;
    void setPosition(float, float);
    sf::RectangleShape shadow;
    sf::Texture mapTexture[2];
    sf::Sprite mapSprite1, mapSprite2;
    sf::RenderTexture rt, re;
    Tile mapArray[61][61];
    std::vector<wall> walls;
    std::vector<Coordinate> emptyMapLocations;
    Coordinate teleporterLocation;
    Coordinate getTeleporterLoc();
    void clear();
    // A function to rebuild map vectors
    void rebuild(Tileset);
    std::vector<Coordinate> * getEmptyLocations();
    float getPosX() const;
    float getPosY() const;
    void setWindowSize(float, float);
    void reset();
};

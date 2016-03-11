//
//  tileController.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/11/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "tileController.hpp"
#include "ResourcePath.hpp"
#include "mappingFunctions.hpp"
#include "turret.hpp"
#include "initMapVectors.hpp"
#include <random>

// Define expressions to represent the number values for the tilesets (makes the code easier to follow)
#define SAND_TILESET 0
#define DIRT_TILESET 1
#define GRASS_TILESET 2
#define METEOR_TILESET 3


// A function to put values onto the vector of map data when it runs out
// Important to have the shuffled vector to avoid running into the same maps over again
void initMapStack(std::vector<unsigned char> &mps) {
    
    const unsigned char tilesets[1] = {DIRT_TILESET};
    for (auto i = 0; i < 1; i++) {
        // Fill the map vector with all the available sets
        mps.push_back(tilesets[i]);
    }
    // Randomly shuffle the stack of maps with an stl function
    std::mt19937 gen(static_cast<uint32_t>(time(0)));
    shuffle(mps.begin(), mps.end(), gen);
}

void drawPixels(sf::Image& tileMap, sf::Image& tileImage, int xIndex, int yIndex, int xoffset, int yoffset) {
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 26; j++) {
            // If the pixel color is not transparent
            if (tileImage.getPixel(i + xoffset, j).a != 0)
                tileMap.setPixel(xIndex * 32 + i, yIndex * 26 + j, tileImage.getPixel(i + xoffset, j + yoffset));
        }
    }
}

void createMapImage(sf::Image* tileImage, short mapArray[61][61], sf::Texture tx[2], sf::Image* grassSet, sf::Image* grassSetEdge) {
    // Loop through the entire image and create a tilemap for drawing grass
    short mapTemp[61][61], bitMask[61][61], gratePositions[61][61];
    // Begin by initializing the whole map to zero
    for (int i = 0; i < 61; i++) {
        for (int j = 0; j < 61; j++) {
            mapTemp[i][j] = 0;
            bitMask[i][j] = 0;
            gratePositions[i][j] = 0;
            if (mapArray[i][j] == 5 && !(rand() % 11)) {
                gratePositions[i][j] = 1;
            }
        }
    }
    
    // Now smooth the grate positions
    int count;
    // Run 2 repetitions of smoothing
    for (int rep = 2; rep > 0; rep--)
        for (int i = 1; i < 60; i++) {
            for (int j = 1; j < 60; j++) {
                count = gratePositions[i - 1][j] + gratePositions[i + 1][j] + gratePositions[i][j - 1] + gratePositions[i][j + 1];
                if (count && !(rand() % 3)) {
                    gratePositions[i][j] = 1;
                }
            }
        }
    
    // Now if the map array contains a grass tile, set the temporary map value to 1
    for (int i = 0; i < 61; i++) {
        for (int j = 0; j < 61; j++) {
            if (mapArray[i][j] == 8 || mapArray[i][j] == 11 || mapArray[i][j] == 10 || mapArray[i][j] == 9) {
                mapTemp[i][j] = 1;
            }
        }
    }
    // Now loop through each index of the temporary map and set the value of the bit mask according to nearby element values
    for (int i = 0; i < 61; i++) {
        for (int j = 0; j < 61; j++) {
            if (mapTemp[i][j] == 1) {
                bitMask[i][j] += 1 * mapTemp[i][j - 1];
                
                if (mapArray[i + 1][j] != 10 && mapArray[i + 1][j] != 9)
                    bitMask[i][j] += 2 * mapTemp[i + 1][j];
                
                bitMask[i][j] += 4 * mapTemp[i][j + 1];
                
                if (mapArray[i - 1][j] != 10 && mapArray[i - 1][j] != 9)
                    bitMask[i][j] += 8 * mapTemp[i - 1][j];
            }
        }
    }
    // At this point the bitmap hash values are ready for the map image generation code to interpret them
    
    sf::Image tileMap, tileMapEdge;
    // Create an image of the size 61 * tileWidth (32), by 61 * tile height (26)
    tileMap.create(1952, 1586, sf::Color::Transparent);
    tileMapEdge.create(1952, 1586, sf::Color::Transparent);
    // Loop through all indices of the map array and copy the corresponding pixels from the tileset to the image
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 60; j++) {
            int select = rand() % 3;
            switch (mapArray[i][j]) {
                case 5:
                    if (gratePositions[i][j] != 1) {
                        drawPixels(tileMap, *tileImage, i, j, 0, 0);
                    }
                    
                    else {
                        drawPixels(tileMap, *tileImage, i, j, 256, 0);
                    }
                    
                    break;
                    
                case 3:
                    drawPixels(tileMap, *tileImage, i, j, 32, 0);
                    break;
                    
                case 4:
                    drawPixels(tileMap, *tileImage, i, j, 64, 0);
                    break;
                    
                case 2:
                    if (select == 2)
                        drawPixels(tileMapEdge, *tileImage, i, j, 96, 0);
                    
                    else if (select == 1)
                        drawPixels(tileMapEdge, *tileImage, i, j, 288, 0);
                    
                    else
                        drawPixels(tileMapEdge, *tileImage, i, j, 320, 0);
                    
                    break;
                    
                case 6:
                    drawPixels(tileMap, *tileImage, i, j, 128, 0);
                    break;
                    
                case 8:
                    drawPixels(tileMap, *tileImage, i, j, 0, 0);
                    if (select != 2)
                        drawPixels(tileMap, *grassSetEdge, i, j, bitMask[i][j] * 32, 0);
                    
                    else
                        drawPixels(tileMap, *grassSet, i, j, bitMask[i][j] * 32, 0);

                    break;
                    
                case 11:
                    drawPixels(tileMap, *tileImage, i, j, 32, 0);
                    if (select != 2)
                        drawPixels(tileMap, *grassSetEdge, i, j, bitMask[i][j] * 32, 0);
                    
                    else
                        drawPixels(tileMap, *grassSet, i, j, bitMask[i][j] * 32, 0);
                    
                    break;
                    
                case 9:
                    if (select != 2)
                        drawPixels(tileMapEdge, *tileImage, i, j, 192, 0);
                    
                    else
                        drawPixels(tileMapEdge, *tileImage, i, j, 160, 0);
                    
                    break;
                    
                case 10:
                    drawPixels(tileMap, *tileImage, i, j, 224, 0);
                    break;
                    
                case 13:
                    drawPixels(tileMap, *tileImage, i, j, 256, 0);
                    break;
                    
                default:
                    break;
            }
        }
    }
    
    tx[0].loadFromImage(tileMap);
    tx[1].loadFromImage(tileMapEdge);
    //tileMap.saveToFile("TEST_MAP.png");
    //tileMapEdge.saveToFile("TEST_MAP_EDGE.png");
}

tileController::tileController() {
    //Set the random seed and initialize the offset for drawing tiles to 0.
    //Offsets move the background, givig the illusion that the stationary player is walking
    xOffset = 0;
    yOffset = 0;
    posX = 0;
    posY = 0;
    windowH = 0;
    windowW = 0;
    tempX = 0;
    tempY = 0;
    
    //First load the all the textures for the overworld sprites
    const std::string fileExts3[5] = {"moon_edge_tile.png", "field_tile.png", "field_tile_shrub.png", "orbit_edge_tile3.png", "orbit_edge_top.png"};
    const std::string fileExts4[5] = {"regolith_border_tile.png", "regolith_tile.png", "regolith_tile_alt.png", "orbit_edge_tile4.png", "orbit_edge_top.png"};
    
    tileImg[0].loadFromFile(resourcePath() + "soilTileset.png");
    tileImg[1].loadFromFile(resourcePath() + "sandTileset.png");
    grassSet.loadFromFile(resourcePath() + "grassSet.png");
    grassSetEdge.loadFromFile(resourcePath() + "grassSetEdge.png");
    redSet.loadFromFile(resourcePath() + "damageSet.png");
    redSetFlowers.loadFromFile(resourcePath() + "redSetFlowers.png");
    
    for (int i = 0; i < 5; i++) {
        tileTexture3[i].loadFromFile(resourcePath() + fileExts3[i]);
        tileTexture4[i].loadFromFile(resourcePath() + fileExts4[i]);
    }
    //std::cout << tileTexture[0].getMaximumSize();
    
    //Call the mapping function to transform the array into something useful
    int count = mappingFunction(mapArray);
    // Yikes a while loop! I try to avoid them, but... This loop repeats until it yields a large enough map
    while (count < 300) {
        count = mappingFunction(mapArray);
    }
    
    //Now call another function to read the map and store empty locations for enemy placement
    initMapVectors(mapArray, w, walls, posX, posY, emptyMapLocations, largeEmptyLocations, edgeLocations, primeChestLocations, teleporterLocation);
    // Initialize the tileset to use for the first waypoint (currently set to a constant value)
    workingSet = SAND_TILESET;
    // Fill the container of maps with values
    initMapStack(maps);
    
    createMapImage(&tileImg[0], mapArray, mapTexture, &grassSet, &grassSetEdge);
    mapSprite[0].setTexture(mapTexture[0]);
    mapSprite[1].setTexture(mapTexture[1]);
    
    txt.loadFromFile(resourcePath() + "whiteFloorGlow.png");
    spr.setTexture(txt);
    shadow.setFillColor(sf::Color(183, 183, 190, 255));
}

void tileController::drawTiles(sf::RenderWindow& window, std::vector<sf::Sprite*>* glowSprites, std::vector<sf::Sprite*>* glowSprites2) {
    if (!walls.empty()) {
        for (int i = 0; i < walls.size(); i++) {
            //Also move the walls with the same offset
            walls[i].setPosition(walls[i].getXinit() + xOffset + posX, walls[i].getYinit() + yOffset + posY);
        }
    }
    spr.setPosition(windowW / 2 + 20, windowH / 2);
    mapSprite[0].setPosition(posX + xOffset, posY + yOffset);
    mapSprite[1].setPosition(posX + xOffset, posY + yOffset);
    
    // Clear out the RenderTexture
    rt.clear(sf::Color::Transparent);
    // Draw the map sprite to the texture
    rt.draw(mapSprite[0]);
    // Draw a shadow over everything
    rt.draw(shadow, sf::BlendMultiply);
    // Draw glow sprites
    for (auto & element : *glowSprites) {
        rt.draw(*element, sf::BlendMode(sf::BlendMode(sf::BlendMode::SrcAlpha, sf::BlendMode::One, sf::BlendMode::Add, sf::BlendMode::DstAlpha, sf::BlendMode::Zero, sf::BlendMode::Add)));
    }
    for (auto & element : *glowSprites2) {
        rt.draw(*element, sf::BlendMode(sf::BlendMode(sf::BlendMode::SrcAlpha, sf::BlendMode::One, sf::BlendMode::Add, sf::BlendMode::DstAlpha, sf::BlendMode::Zero, sf::BlendMode::Add)));
    }
    // Set the render texture to display
    rt.display();
    
    re.clear(sf::Color::Transparent);
    re.draw(mapSprite[1]);
    re.draw(shadow, sf::BlendMultiply);
    
    re.display();
    
    // Construct a sprite from the new texture
    sf::Sprite sprite(rt.getTexture());
    sf::Sprite sprite2(re.getTexture());
    // Draw the whole thing to the window
    window.draw(sprite);
    window.draw(sprite2);
    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        int playerx = (posX - windowW + xOffset) / -32;
        int playery = (posY - windowH + yOffset) / -26;
        std::cout << playerx << "  " << playery << std::endl;
    }*/
}

void tileController::drawTiles(sf::RenderWindow& window) {
    mapSprite[0].setPosition(posX + xOffset, posY + yOffset);
    mapSprite[1].setPosition(posX + xOffset, posY + yOffset);
    window.draw(mapSprite[0]);
    window.draw(mapSprite[1]);
}

//A function for setting the offset for the overworld
void tileController::setOffset(float x, float y) {
    xOffset = x;
    yOffset = y;
}

//Set the center position according to the window width and height
void tileController::setPosition(float X, float Y) {
    posX += X;
    windowW = X;
    posY += Y;
    windowH = Y;
}

// Empty all of the containers to prepare for pushing back a new map set
void tileController::clear() {
    walls.clear();
    primeChestLocations.clear();
    emptyMapLocations.clear();
    edgeLocations.clear();
    largeEmptyLocations.clear();
}

// A function to build a new world with a random tileset
void tileController::rebuild() {
    // If the vector of map data contains values
    if (maps.size() > 0) {
        workingSet = maps[maps.size() - 1];
        maps.pop_back();
    }
    // If not, re-initialize and do the same thing
    else {
        initMapStack(maps);
        workingSet = maps[maps.size() - 1];
        maps.pop_back();
    }
    
    createMapImage(&tileImg[0], mapArray, mapTexture, &grassSet, &grassSetEdge);
    mapSprite[0].setTexture(mapTexture[0]);
    mapSprite[1].setTexture(mapTexture[1]);
    
    // Draw tiles based on the current working tileset delivered by the map playlist vector
    switch (workingSet) {
        case 0:
            createMapImage(&tileImg[1], mapArray, mapTexture, &redSetFlowers, &redSet);
            break;
            
        case 1:
            createMapImage(&tileImg[0], mapArray, mapTexture, &grassSet, &grassSetEdge);
            break;
            
        default:
            break;
    }
    initMapVectors(mapArray, w, walls, posX, posY, emptyMapLocations, largeEmptyLocations, edgeLocations, primeChestLocations, teleporterLocation);
}

void tileController::init() {
    short initMap[61][61];
    for (int i = 0; i < 61; i++) {
        for (int j = 0; j < 61; j++) {
            initMap[i][j] = 3;
        }
    }
    createMapImage(&tileImg[1], initMap, mapTexture, &redSet, &redSet);
}

unsigned char tileController::getWorkingSet() {
    return workingSet;
}

void tileController::setWindowSize(float w, float h) {
    rt.create(w, h);
    re.create(w, h);
    sf::Vector2f v;
    v.x = w;
    v.y = h;
    shadow.setSize(v);
}


Coordinate tileController::getTeleporterLoc() {
    return teleporterLocation;
}

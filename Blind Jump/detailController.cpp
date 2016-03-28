//
//  detailController.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/29/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "detailController.hpp"
#include "resourcepath.hpp"
#include <iostream>
#include <cmath>

#define NUM_ROCK_IMAGES 4

detailController::detailController() {
    const std::string numberFileExtensions[1] = {"brokenTurret.png"};
    for (int i = 0; i < 1; i++) {
        if (!textures[i].loadFromFile(resourcePath() + numberFileExtensions[i])) {
            //return EXIT_FAILURE;
        }
    }
    teleporterTexture[0].loadFromFile(resourcePath() + "teleporter.png");
    teleporterTexture[1].loadFromFile(resourcePath() + "teleporterShadow.png");
    for (int i = 0; i < 6; i++) {
        chestTextures[i].loadFromFile(resourcePath() + "treasureChest.png", sf::IntRect(16 * i, 0, 16, 30));
    }
                               
    termTexture[0].loadFromFile(resourcePath() + "terminal.png");
    termTexture[1].loadFromFile(resourcePath() + "terminalFlicker.png");
    chestShadow.loadFromFile(resourcePath() + "chestShadow.png");
    miscTextures32x26.loadFromFile(resourcePath() + "warpImpact.png");
    enemyScraps[0].loadFromFile(resourcePath() + "enemyScraps.png");
    dasherScraps.loadFromFile(resourcePath() + "dasherDead.png");
    teleporterGlow.loadFromFile(resourcePath() + "teleporterGlow.png");
    
    for (int i = 0; i < 4; i++) {
        doorTextures[i].loadFromFile(resourcePath() + "introWall.png", sf::IntRect(0, i * 95, 200, 95));
    }
    
    for (int i = 0; i < 2; i++) {
        damagedRobotTexture[i].loadFromFile(resourcePath() + "damagedRobotSheet.png", sf::IntRect(i * 40, 0, 40, 43));
    }
    
    for (int i = 0; i < NUM_ROCK_IMAGES; i++) {
        rockTextures[i].loadFromFile(resourcePath() + "boulderSheet.png", sf::IntRect(i * 32, 0, 32, 64));
    }
    
    UIStates[0] = 0;
    lampGlow.loadFromFile(resourcePath() + "lampLight.png");
    for (int i = 0; i < 3; i++) {
        lampTextures[i].loadFromFile(resourcePath() + "lamp.png", sf::IntRect(i * 32, 0, 32, 32));
    }
    
}

Coordinate pickLocation(std::vector<Coordinate>& emptyLocations) {
    // Randomly pick an available empty location
    int locationSelect = rand() % emptyLocations.size();
    Coordinate c = emptyLocations[locationSelect];
    // Don't want to place two objects in the same position, so remove coordinate from the vector if used
    emptyLocations[locationSelect] = emptyLocations.back();
    emptyLocations.pop_back();
    return c;
    
}

Coordinate pickLocationGrass(std::vector<Coordinate>& emptyLocations, short mapArray[61][61]) {
    // Randomly pick an available empty location
    Coordinate c;
    int locationSelect;
    // Keep track of loop iterations (in case there actually aren't any open grass tiles left)
    int count = 0;
    do {
        count++;
        locationSelect = rand() % emptyLocations.size();
        c = emptyLocations[locationSelect];
        if (count > 500/*On average there are 300 open spaces on a map*/) {
            throw "Maximum tries exceeded.";
        }
    } while (mapArray[c.x][c.y] != 8  && mapArray[c.x][c.y] != 11);
    // Don't want to place two objects in the same position, so remove coordinate from the vector if used
    emptyLocations[locationSelect] = emptyLocations.back();
    emptyLocations.pop_back();
    return c;
}

Coordinate pickLocationSand(std::vector<Coordinate>& emptyLocations, short mapArray[61][61]) {
    // Randomly pick an available empty location
    Coordinate c;
    int locationSelect;
    // Keep track of loop iterations (in case there actually aren't any open grass tiles left)
    int count = 0;
    do {
        count++;
        locationSelect = rand() % emptyLocations.size();
        c = emptyLocations[locationSelect];
        if (count > 500/*On average there are 300 open spaces on a map*/) {
            throw "Maximum tries exceeded.";
        }
    } while (mapArray[c.x][c.y] != 3);
    // Don't want to place two objects in the same position, so remove coordinate from the vector if used
    emptyLocations[locationSelect] = emptyLocations.back();
    emptyLocations.pop_back();
    return c;
}

Coordinate pickLocation2(std::vector<Coordinate>& emptyLocations) {
    // Randomly pick an available empty location
    int locationSelect = rand() % emptyLocations.size();
    Coordinate c = emptyLocations[locationSelect];
    return c;
}

void detailController::addWarpImpact(float posX, float posY) {
    sf::Sprite tempSprite;
    tempSprite.setTexture(miscTextures32x26);
    GeneralDetail d(posX, posY, &tempSprite, 1, 0, 0);
    misc32x26.push_back(d);
}

void detailController::addLamplight(tileController& t, float posX, float posY, int i, int j, float width, float height) {
    sf::Sprite tempSprites[2];
    tempSprites[0].setTexture(lampTextures[0]);
    tempSprites[1].setTexture(lampGlow);
    LampLight lmp((i * 32) + posX, (j * 26) + posY, tempSprites[0], tempSprites[1], 2, width, height);
    lamps.push_back(lmp);
}

void detailController::addRock(tileController& t, float posX, float posY, int i, int j) {
    sf::Sprite tempSprite;
    tempSprite.setTexture(rockTextures[rand() % NUM_ROCK_IMAGES]);
    float placementXoffset = 0;
    if (rand() % 2) {
        tempSprite.setScale(-1, 1);
        placementXoffset += 32;
    }
    Rock r((i * 32) + posX + placementXoffset, (j * 26) + posY, &tempSprite, 2, 0, 0);
    rocks.push_back(r);
}

void detailController::addChest(tileController& t, float posX, float posY, float width, float height, char chestContents) {
    Coordinate c = pickLocation(t.emptyMapLocations);
    sf::Sprite tempSprites[7];
    tempSprites[6].setTexture(chestShadow);
    for (int i = 0; i < 6; i++) {
        tempSprites[i].setTexture(chestTextures[i]);
    }
    float placeOffsetX = 0;
    placeOffsetX = (rand() % 6) - 3;
    TreasureChest tr((c.x * 32) + posX + 8 + placeOffsetX, (c.y * 26) + posY - 3, tempSprites, 7, width, height, chestContents);
    chests.push_back(tr);
}

void detailController::addEnemyScrap(tileController& t, float posX, float posY, float width, float height) {
    sf::Sprite tempSprite;
    tempSprite.setTexture(enemyScraps[0]);
    GeneralDetail scrap(posX - 6, posY - 2, &tempSprite, 0, width, height);
    misc32x26.push_back(scrap);
}

void detailController::addDamagedRobots(tileController& t, float posX, float posY) {
    if (rand() % 2) {
        Coordinate c;
        bool choice = rand() % 2;
        float placeOffsetX = 0;
        sf::Sprite tempSprite;
        try {
            c = pickLocationGrass(t.emptyMapLocations, t.mapArray);
            tempSprite.setTexture(damagedRobotTexture[choice]);
            placeOffsetX = (rand() % 6) - 3;
            if (rand() % 2) {
                tempSprite.setScale(-1, 1);
                placeOffsetX += 32;
            }
            DamagedRobot dr((c.x * 32) + posX + placeOffsetX - 20, (c.y * 26) + posY - 20, &tempSprite, 0, 0, 0);
            damagedRobots.push_back(dr);
        }
        
        catch(const char* e) {
            std::cout << e << std::endl;
        }
        

        if (rand() % 2) {
            try {
                c = pickLocationGrass(t.emptyMapLocations, t.mapArray);
                tempSprite.setTexture(damagedRobotTexture[!choice]);
                DamagedRobot dr((c.x * 32) + posX + placeOffsetX - 20, (c.y * 26) + posY - 20, &tempSprite, 0, 0, 0);
                damagedRobots.push_back(dr);
            }
            
            catch(const char* e) {
                std::cout << e << std::endl;
            }
        }
        
        if (rand() % 2) {
            try {
                c = pickLocationGrass(t.emptyMapLocations, t.mapArray);
                tempSprite.setTexture(damagedRobotTexture[choice]);
                if (tempSprite.getScale().x == -1) {
                    tempSprite.setScale(1, 1);
                    placeOffsetX -= 32;
                }
                
                else {
                    tempSprite.setScale(-1, 1);
                    placeOffsetX += 32;
                }
                
                DamagedRobot dr((c.x * 32) + posX + placeOffsetX - 20, (c.y * 26) + posY - 20, &tempSprite, 0, 0, 0);
                damagedRobots.push_back(dr);
            }
            
            catch(const char* e) {
                std::cout << e << std::endl;
            }
        }
    }
}

void detailController::addDasherScrap(tileController& t, float posX, float posY, int scale) {
    if (scale == -1) {
        posX += -14;
    }
    sf::Sprite tempSprite;
    tempSprite.setScale((float) scale, 1);
    tempSprite.setTexture(dasherScraps);
    tempSprite.setOrigin(14, 8);
    GeneralDetail dScrap(posX, posY, &tempSprite, 0, 0, 0);
    misc32x26.push_back(dScrap);
}

void detailController::addDoor(float xpos, float ypos, int x, int y, float w, float h) {
    sf::Sprite tempSprite[4];
    for (int i = 0; i < 4; i++) {
        tempSprite[i].setTexture(doorTextures[i]);
    }
    IntroDoor d(xpos + x * 32, ypos + y * 26, tempSprite, 0, w, h);
    doors.push_back(d);
}

void detailController::addTeleporter(tileController& t, float posX, float posY, float width, float height) {
    Coordinate c = t.getTeleporterLoc();
    sf::Sprite tempSprites[2];
    tempSprites[0].setTexture(teleporterTexture[0]);
    tempSprites[1].setTexture(teleporterTexture[1]);
    // Want the overworld to look organic, so randomly offset the teleporter location
    //float placeOffsetX = 0;
    
    //placeOffsetX = (rand() % 6) - 3;
    
    sf::Sprite glow;
    glow.setTexture(teleporterGlow);
    
    Teleporter T((c.x * 32) + posX + 2/* + placeOffsetX*/, (c.y * 26) + posY - 4, tempSprites, glow, 2, width, height);
    // Initialize the teleporter countdown to 5
    T.initCountdown();
    teleporters.push_back(T);
}

void detailController::addTerminal(tileController & t, float posX, float posY, float width, float height) {
    Coordinate c = pickLocation(t.emptyMapLocations);
    sf::Sprite tempSprites[3];
    tempSprites[0].setTexture(termTexture[0]);
    tempSprites[1].setTexture(termTexture[1]);
    tempSprites[2].setTexture(chestShadow);
    Terminal term((c.x * 32) + posX + 8, (c.y * 26) + posY - 4, tempSprites, 3, width, height);
    terminals.push_back(term);
}

void detailController::update(float xOffset, float yOffset, effectsController& ef, char PlayerSprIndex, std::vector<wall>& walls, std::vector<sf::Sprite*>* glow1, std::vector<sf::Sprite*>* glow2, userInterface& ui, FontController& fonts, Player& player, InputController* pInput, ScreenShakeController * pscr) {
    UIStates[0] = 0;
    if (!teleporters.empty()) {
        for (auto & element : teleporters) {
            element.update(xOffset, yOffset);
            if (element.getCountdown() == 5) {
                ef.addWarpEffect(element.getxPos() - xOffset + 4 + (rand() % 6), element.getyPos() - yOffset + 2);
            }
            glow1->push_back(element.getGlow());
            glow2->push_back(element.getGlow());
        }
    }
    
    
    if (!lamps.empty()) {
        for (auto & element : lamps) {
            element.update(xOffset, yOffset);
            // Push the light effects back
            float xPos = element.getxPos();
            float yPos = element.getyPos();
            if (xPos < element.getWindowCenterX() + 150 && xPos > -150 && yPos < element.getWindowCenterY() + 150 && yPos > -150) {
                glow1->push_back(element.getGlow());
                glow2->push_back(element.getGlow());
            }
        }
    }
    
    if (!chests.empty()) {
        for (int i = 0; i < chests.size(); i++) {
            chests[i].update(xOffset, yOffset, PlayerSprIndex, pInput);
            // If the user opened a chest, put it's item into the UI menu
            if (chests[i].getFrameIndex() == 3) {
                ui.addItem(chests[i].getItem(), ef, chests[i].getxPos() - xOffset, chests[i].getyPos() - yOffset, fonts, player);
            }
        }
    }
    
    if (!rocks.empty()) {
        for (auto & element : rocks) {
            element.update(xOffset, yOffset);
        }
    }
    
    if (!doors.empty()) {
        for (auto & element : doors) {
            element.update(xOffset, yOffset, pInput, pscr);
        }
    }
    
    if (!misc32x26.empty()) {
        for (auto & element : misc32x26) {
            element.update(xOffset, yOffset);
        }
    }
    
    if (!damagedRobots.empty()) {
        for (auto & element : damagedRobots) {
            element.update(xOffset, yOffset);
        }
    }
    
    if (!terminals.empty()) {
        for (auto & element : terminals) {
            element.update(xOffset, yOffset);
            if ((PlayerSprIndex == 1) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && std::abs(8 + element.getxPos() - element.getWindowCenterX() / 2) < 10 && std::abs(element.getyPos() - element.getWindowCenterY() / 2) < 16)
                UIStates[0] = 1;
        }
    }
}

template <typename T>
void drawElements(std::vector<T>& vec, std::vector<std::tuple<sf::Sprite, float, int>>& gameObjects, std::vector<std::tuple<sf::Sprite, float, int>>& gameShadows) {
    if (!vec.empty()) {
        std::tuple<sf::Sprite, float, int> tObject, tShadow;
        for (auto & element : vec) {
            // Push back the object
            std::get<0>(tObject) = *element.getSprite();
            std::get<1>(tObject) = element.getyPos() - 8;
            gameObjects.push_back(tObject);
            // Push back its shadow
            std::get<0>(tShadow) = *element.getShadow();
            gameShadows.push_back(tShadow);
        }
    }
}

void detailController::killTeleporter() {
    teleporters.clear();
}

void detailController::draw(std::vector<std::tuple<sf::Sprite, float, int>>& gameObjects, std::vector<std::tuple<sf::Sprite, float, int>>& gameShadows, sf::RenderWindow& window) {
    std::tuple<sf::Sprite, float, int> tObject, tShadow;
    if (!misc32x26.empty()) {
        for (auto & element : misc32x26) {
            std::get<0>(tObject) = *element.getSprite();
            std::get<1>(tObject) = element.getyPos() - 26;
            gameObjects.push_back(tObject);
        }
    }
    
    if (!teleporters.empty()) {
        // These textures are flat and z-ordering doesn't matter, so no need to put too much strain on the sort function (just draw them manually)
        for (auto & element : teleporters) {
            window.draw(*element.getShadow());
            window.draw(*element.getSprite());
        }
    }
    
    if (!doors.empty()) {
        for (auto & element : doors) {
            std::get<0>(tObject) = *element.getSprite();
            std::get<1>(tObject) = element.getyPos() + 52;
            gameObjects.push_back(tObject);
        }
    }
    
    if (!rocks.empty()) {
        for (auto element : rocks) {
            std::get<0>(tObject) = *element.getSprite();
            std::get<1>(tObject) = element.getyPos() + 22;
            gameObjects.push_back(tObject);
        }
    }
    
    if (!damagedRobots.empty()) {
        for (auto element : damagedRobots) {
            std::get<0>(tObject) = *element.getSprite();
            std::get<1>(tObject) = element.getyPos();
            gameObjects.push_back(tObject);
        }
    }
    
    if (!chests.empty()) {
        for (auto & element : chests) {
            // Push back the object
            std::get<0>(tObject) = *element.getSprite();
            std::get<1>(tObject) = element.getZY();
            gameObjects.push_back(tObject);
            // Push back its shadow
            std::get<0>(tShadow) = *element.getShadow();
            gameShadows.push_back(tShadow);
        }
    }
    
    if (!lamps.empty()) {
        for (auto & element : lamps) {
            window.draw(*element.getSprite());
        }
    }
    
    drawElements(terminals, gameObjects, gameShadows);
}

void detailController::clear() {
    teleporters.clear();
    chests.clear();
    misc32x26.clear();
    terminals.clear();
    lamps.clear();
    damagedRobots.clear();
    rocks.clear();
    doors.clear();
}

std::vector<TreasureChest> detailController::getChests() {
    return chests;
}

Teleporter* detailController::getTeleporter() {
    return &teleporters[0];
}

std::vector<Terminal> detailController::getTerms() {
    return terminals;
}

unsigned char* detailController::getUIStates() {
    return UIStates;
}

std::vector<LampLight>* detailController::getLamps() {
    return &lamps;
}

std::vector<Rock>* detailController::getRocks() {
    return &rocks;
}

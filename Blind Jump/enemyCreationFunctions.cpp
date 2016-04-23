//
//  enemyCreationFunctions.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/19/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "enemyCreationFunctions.hpp"
#include "turret.hpp"
#include "scoot.hpp"
#include "dasher.hpp"

//A function to add a turret
void addTurret(short mapArray[61][61], short descriptionArray[61][61], enemyController& en, float posX, float posY, float windowW, float windowH, std::vector<Coordinate>& emptyLocations) {
    
    //Construct a turret with all its sprites
    turret t(en.getTurretSprites());
    
    // Randomly pick an available empty location
    int locationSelect = (rand() % 2) ? rand() % (emptyLocations.size() / 2 ) : rand() % (emptyLocations.size());
    Coordinate c = emptyLocations[locationSelect];
    // Don't want to place two objects in the same position, so remove coordinate from the vector if used
    emptyLocations[locationSelect] = std::move(emptyLocations.back());
    emptyLocations.pop_back();
    
    // Use the selected coordinate to initialize the position of the enemy object
    t.setInitPosition((c.x * 32) + posX + 8 + ((rand() % 6) - 3), (c.y * 26) + posY - 12 + ((rand() % 6) - 3));
    //Let the turret know where the player is (always at the center of the window!
    t.setPlayerPos(windowW, windowH);
    en.addTurret(t);
}

void addScoot(short mapArray[61][61], short descriptionArray[61][61], enemyController& en, float posX, float posY, float windowW, float windowH, std::vector<Coordinate>& emptyLocations) {
    
    Scoot s(en.getScootSprites());
    
    int locationSelect = (rand() % 2) ? rand() % (emptyLocations.size() / 2 ) : rand() % (emptyLocations.size());
    Coordinate c = emptyLocations[locationSelect];
    emptyLocations[locationSelect] = std::move(emptyLocations.back());
    emptyLocations.pop_back();
    s.setInitPosition((c.x * 32) + posX + 16, (c.y * 26) + posY - 3);
    s.setPlayerPos(windowW, windowH);
    en.addScoot(s);
}

void addDasher(short mapArray[61][61], short descriptionArray[61][61], enemyController& en, float posX, float posY, float windowW, float windowH, std::vector<Coordinate>& emptyLocations) {
    
    Dasher d(en.getDasherSprites());
    
    int locationSelect = (rand() % 2) ? rand() % (emptyLocations.size() / 3 ) : rand() % (emptyLocations.size() / 2);
    Coordinate c = emptyLocations[locationSelect];
    emptyLocations[locationSelect] = std::move(emptyLocations.back());
    emptyLocations.pop_back();
    d.setInitPosition((c.x * 32) + posX + 16, (c.y * 26) + posY - 3);
    d.setPlayerPos(windowW, windowH);
    en.addDasher(d);
}

void addHeavyBot(short mapArray[61][61], short descriptionArray[61][61], enemyController& en, float posX, float posY, float windowW, float windowH, std::vector<Coordinate>& emptyLocations) {
    
    HeavyBot h(en.getHeavyBotSprites(), mapArray);
    
    int locationSelect = rand() % (emptyLocations.size() / 1);
    Coordinate c = emptyLocations[locationSelect];
    emptyLocations[locationSelect] = std::move(emptyLocations.back());
    emptyLocations.pop_back();
    h.setInitPosition((c.x * 32) + posX, (c.y * 26) + posY);
    h.setPlayerPos(windowW / 2, windowH / 2);
    en.addHeavyBot(h);
}

void addCritter(short mapArray[61][61], short descriptionArray[61][61], enemyController& en, float posX, float posY, float windowW, float windowH, std::vector<Coordinate>& emptyLocations, int rep) {
    // Fill a vector with a bunch of chasers
    std::vector<Critter> critters(rep, Critter(en.getChaserSprites(), mapArray));
    
    int locationSelect = rand() % (emptyLocations.size() / 1);
    Coordinate c = emptyLocations[locationSelect];
    emptyLocations[locationSelect] = std::move(emptyLocations.back());
    emptyLocations.pop_back();
    for (auto & element : critters) {
        element.setInitPosition((c.x * 32) + posX + 8, (c.y * 26) + posY + 8);
        element.setPlayerPos(windowW, windowH);
        en.addCritter(element);
    }
}


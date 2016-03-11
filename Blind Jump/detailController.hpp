//
//  detailController.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/29/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef detailController_hpp
#define detailController_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include "Teleporter.hpp"
#include "treasureChest.hpp"
#include "tileController.hpp"
#include "coordinate.h"
#include "terminal.hpp"
#include "generalDetail.hpp"
#include "lampLight.hpp"
#include "userInterface.hpp"
#include "damagedRobot.hpp"
#include "rock.hpp"

class detailController {
private:
    sf::Texture rockTextures[2];
    sf::Texture textures[2];
    sf::Texture damagedRobotTexture[2];
    sf::Texture teleporterTexture[2];
    sf::Texture chestTextures[6];
    sf::Texture chestGlow;
    sf::Texture termTexture[2];
    sf::Texture chestShadow;
    sf::Texture miscTextures32x26;
    sf::Texture enemyScraps[1];
    sf::Texture dasherScraps;
    sf::Texture lampGlow;
    sf::Texture lampTextures[3];
    sf::Texture teleporterGlow;
    std::vector<Teleporter> teleporters;
    std::vector<Terminal> terminals;
    std::vector<TreasureChest> chests;
    std::vector<LampLight> lamps;
    std::vector<Rock> rocks;
    std::vector<DamagedRobot> damagedRobots;
    // A vector of objects with no polymorphism, for background details that don't need any added functionality
    std::vector<GeneralDetail> misc32x26;
    // Variables to keep track of which ui elements to draw
    unsigned char UIStates[1];

public:
    detailController();
    void addCrystals(float, float, float, float);
    void addDamagedRobots(tileController&, float, float);
    void addLamplight(tileController&, float, float, int, int, float, float);
    void addChest(tileController&, float, float, float, float, char);
    void addEnemyScrap(tileController&, float, float, float, float);
    void addDamagedTurret(float, float, float, float);
    void addTeleporter(tileController&, float, float, float, float);
    void addRock(tileController&, float, float, int, int);
    void addTerminal(tileController&, float, float, float, float);
    void update(float, float, effectsController& ef, char, std::vector<wall>&, std::vector<sf::Sprite*>*, std::vector<sf::Sprite*>*, userInterface&, FontController&, Player&);
    void addDasherScrap(tileController&, float, float, int);
    void draw(std::vector<std::tuple<sf::Sprite, float, int>>&, std::vector<std::tuple<sf::Sprite, float, int>>&, sf::RenderWindow&);
    void clear();
    std::vector<TreasureChest> getChests();
    Teleporter getTeleporter();
    std::vector<LampLight>* getLamps();
    void addWarpImpact(float, float);
    std::vector<Terminal> getTerms();
    unsigned char* getUIStates();
    void killTeleporter();
    void setWindowSize(float, float);
};

#endif /* detailController_hpp */

//
//  mapInit.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/15/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef gameMap_hpp
#define gameMap_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include "Player.hpp"
#include "backgroundHandler.hpp"
#include "effectsController.hpp"
#include "detailController.hpp"
#include "tileController.hpp"
#include "fontController.hpp"
#include "userInterface.hpp"
#include "enemyController.hpp"
#include "SFML/Audio.hpp"
#include "screenShakeController.hpp"
#include "soundController.hpp"
#include "initLoot.hpp"
#include "inputController.hpp"

class GameMap {
private:
    // Instaintiate a player object
    Player player;
    
    // Set the world type
    short worldType;
    
    // Declare a user Interface object
    userInterface UI;
    
    // Define an object to control sounds
    SoundController sndCtrl;
    
    // Store the current level
    int level;
    
    // The engine creates the illusion of motion by offsetting the background during key presses
    float xOffset;
    float yOffset;
    
    // Controls input from the keyboard and joystick
    InputController *pInput;
    
    sf::Texture vignetteTexture;
    sf::Sprite vignetteSprite;
    
    char itemArray[48][3];
    
    // Add a detail controller
    detailController details;
    
    // Instantiate an effects controller to handle drawing sfx
    effectsController effects;
    
    // Instantiate a background controller
    backgroundHandler bkg;
    
    // A boolean variable that is true when the player is nearby a teleporter
    bool teleporterCond;
    
    // Number of enemies on the map
    unsigned char turretCount;
    unsigned char dasherCount;
    unsigned char scootCount;
    
    // Create a GL rectangle primitive for the teleporter effect
    sf::RectangleShape teleporterBeam;
    sf::RectangleShape entryBeam;
    
    // For the beam to cast a glow to the map
    sf::Texture beamGlowTxr;
    sf::Sprite beamGlowSpr;
    
    // State variables for the teleporter effects at the end of the levels
    bool animationBegin;
    bool beamExpanding;
    bool dispEntryBeam;
    
    sf::Shader redShader, whiteShader, blueShader;
    
    // RenderTexture and shapes for lighting effects
    sf::RenderTexture lightingMap;
    sf::RectangleShape shadowShape;
    
    // Create a font controller
    FontController fonts;
    
    // Locations to place lights
    std::vector<Coordinate> lightPositions;
    
    // Locations to place pillars
    std::vector<Coordinate> pillarPositions;
    
    // Create a vector of pairs with enemy index and placement probability for enemy creation
    std::vector<std::pair<int, int>> enemySelectVec;
    int idealLvs[4] = {2/*Scoot*/, 4/*Critter Swarms*/, 6/*Dasher*/, 18/*Heavybots*/};
    
    // Stack of sprites with y-position and height, for z-ordering
    std::vector<std::tuple<sf::Sprite, float, int>> gameObjects;
    std::vector<std::tuple<sf::Sprite, float, int>> gameShadows;
    
    // Create a screenshake controller for that effect
    ScreenShakeController ssc;
    
public:
    GameMap(float, float, sf::Texture*, InputController*);
    //Pass in the render window and draw sprites to it
    void update(sf::RenderWindow&);
    // The opening map does not follow the procedural generation approach, have a separate function for this
    void updateLv1(sf::RenderWindow&);
    Player getPlayer();
    detailController getDetails();
    void Reset();
    bool getTeleporterCond();
    std::vector<std::pair<int, int>>* getEnemySelectVec();
    int* getIdealLvs();
    int getLevel();
 
    
    // Store the window width and window height for map resets
    float windowW;
    float windowH;
    
    // Add an enemy controller to take care of moving, updating, and drawing the enemies
    enemyController en;
    
    // Instantiate a tile controller for the drawing the background tiles to the window
    tileController tiles;
};

#endif /* mapInit_hpp */

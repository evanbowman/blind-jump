//
//  tileController.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/11/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef tileController_hpp
#define tileController_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "wall.hpp"
#include "enemyController.hpp"
#include <queue>
#include <stack>
#include "coordinate.h"

class tileController {
public:
	sf::Texture lamplight;
	sf::Sprite lmplght;
	
	sf::Texture transitionLevels[1];
	sf::Sprite transitionLvSpr;
	
	sf::Texture spotlightTxtr;
	sf::Sprite spotlightSpr;
	
	sf::Image tileImg[2];
	sf::Image grassSet[2];
	sf::Image grassSetEdge[2];
	sf::Image redSet;
	sf::Image redSetFlowers;
	
	sf::Sprite tileSprite;
	tileController();
	void drawTiles(sf::RenderTexture&, std::vector<sf::Sprite*>*, std::vector<sf::Sprite*>*, int level);
	void drawTiles(sf::RenderTexture&);
	void drawMiniMap(sf::RenderTexture&);
	//The number of tiles to draw
	int tileCount;
	int xTiles;
	int yTiles;
	float xOffset;
	float yOffset;
	float posX;
	float posY;
	void setPosition(float, float);
	void setOffset(float, float);
	sf::RectangleShape shadow;
	
	int zoomCounter;
	
	sf::Texture mapTexture[2];
	sf::Sprite mapSprite1, mapSprite2;
	
	// Rendertexture top, rendertexture edge
	sf::RenderTexture rt, re;
	
	//Declare a map array variable
	short mapArray[61][61];
	//Some temporary variables for assigning enemy position
	short tempX;
	short tempY;
	//Declare a wall vector
	std::vector <wall> walls;
	//Declare a wall object to push to the wall vector
	wall w;
	//Declare vectors to hold posible positions for object placement
	std::vector<Coordinate> emptyMapLocations;
	std::vector<Coordinate> edgeLocations;
	std::vector<Coordinate> largeEmptyLocations;	// For large footprint object placement
	std::vector<Coordinate> primeChestLocations;	// Find tiles with small number of neighbors, good place to hide items
	
	Coordinate teleporterLocation;
	
	Coordinate getTeleporterLoc();
		
	float windowH;
	float windowW;
	//Declare an array to keep track of the positions of objects drawn to the map as not to place two in the same spot
	short descriptionArray[61][61];
	void clear();
	// Draw a different overworld based on choice of current working set of tiles
	unsigned char workingSet;
	// A function to rebuild map vectors
	void rebuild(char itemArray[48][3], int);
	// Initial build is a flat plane
	void init();
	// Return the working set of tiles background controller access
	unsigned char getWorkingSet();
	void setWindowSize(float, float);
	void reset();
};

#endif /* tileController_hpp */
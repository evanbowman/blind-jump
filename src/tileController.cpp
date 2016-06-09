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
#include "drawPixels.hpp"


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
			if (mapArray[i][j] == 8 || mapArray[i][j] == 11 || mapArray[i][j] == 10 || mapArray[i][j] == 9 || mapArray[i][j] == 7) {
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
	// Set specifically for player position in the first room
	posX = -72;
	posY = -476;
	windowH = 0;
	windowW = 0;
		
	tileImg[0].loadFromFile(resourcePath() + "soilTileset.png");
	tileImg[1].loadFromFile(resourcePath() + "aquaTileset.png");
	grassSet[0].loadFromFile(resourcePath() + "grassSet.png");
	grassSetEdge[0].loadFromFile(resourcePath() + "grassSetEdge.png");
	grassSet[1].loadFromFile(resourcePath() + "grassSetBluish.png");
	grassSetEdge[1].loadFromFile(resourcePath() + "grassSetEdgeBluish.png");
    
	//Call the mapping function to transform the array into something useful
	int count = mappingFunction(mapArray, 0, true);
	
	while (count < 200) {
		count = mappingFunction(mapArray, 0, true);
	}
	
	char itemArray[48][3];
	for (int i = 0; i < 48; i++) {
		for (int j = 0; j < 3; j++) {
			itemArray[i][j] = 0;
		}
	}
	createMapImage(&tileImg[0], mapArray, mapTexture, &grassSet[0], &grassSetEdge[0]);

	createMapImage(&tileImg[0], mapArray, mapTexture, &grassSet[0], &grassSetEdge[0]);
	mapSprite1.setTexture(mapTexture[0]);
	mapSprite2.setTexture(mapTexture[1]);
    
	shadow.setFillColor(sf::Color(188, 188, 198, 255));
}

void tileController::drawTiles(sf::RenderTexture& window, std::vector<sf::Sprite*>* glowSprites, std::vector<sf::Sprite*>* glowSprites2, int level) {
	if (!walls.empty()) {
		for (size_t i = 0; i < walls.size(); i++) {
			//Also move the walls with the same offset
			walls[i].setPosition(walls[i].getXinit() + xOffset + posX, walls[i].getYinit() + yOffset + posY);
		}
	}
	transitionLvSpr.setPosition(posX + xOffset, posY + yOffset);
	mapSprite1.setPosition(posX + xOffset, posY + yOffset);
	mapSprite2.setPosition(posX + xOffset, posY + yOffset);

	// Clear out the RenderTexture
	rt.clear(sf::Color::Transparent);
	// Draw the map sprite to the texture
	if (level != 0)
		rt.draw(mapSprite1);
	else
		rt.draw(transitionLvSpr);
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
	if (level != 0)
		re.draw(mapSprite2);
	re.draw(shadow, sf::BlendMultiply);
	
	re.display();
	
	// Construct a sprite from the new texture
	sf::Sprite sprite(rt.getTexture());
	sf::Sprite sprite2(re.getTexture());
	// Draw the whole thing to the window
	window.draw(sprite);
	window.draw(sprite2);
}

void tileController::drawTiles(sf::RenderTexture& window) {
	mapSprite1.setPosition(posX + xOffset, posY + yOffset);
	mapSprite2.setPosition(posX + xOffset, posY + yOffset);
	window.draw(mapSprite1);
	window.draw(mapSprite2);
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
}

void tileController::setTextures(TextureManager * pTM) {
	lmplght.setTexture(*pTM->getTexture(TextureManager::Texture::lamplight));
	transitionLvSpr.setTexture(*pTM->getTexture(TextureManager::Texture::introLevel));
}

void tileController::rebuild(char itemArray[48][3], int level) {
	// If the vector of map data contains values
	if (level == 0) {
		workingSet = 0;
		posX = -72;
		posY = -476;
		shadow.setFillColor(sf::Color(188, 188, 198, 255));
	} else if (level > 0 && level <= BOSS_LEVEL_1) {
		workingSet = 1;
		shadow.setFillColor(sf::Color(188, 188, 198, 255));
		createMapImage(&tileImg[0], mapArray, mapTexture, &grassSet[0], &grassSetEdge[0]);
		initMapVectors(this, level);
	} else if (level > BOSS_LEVEL_1) {
		workingSet = 2;
		shadow.setFillColor(sf::Color(215, 194, 194, 255));
		createMapImage(&tileImg[1], mapArray, mapTexture, &grassSet[1], &grassSetEdge[1]);
		initMapVectors(this, level);
	}
	
	mapSprite1.setTexture(mapTexture[0]);
	mapSprite2.setTexture(mapTexture[1]);
	
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

void tileController::reset() {

	
}

//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
//                                                                        //
// This program is free software: you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or      //
// (at your option) any later version.                                    //
//                                                                        //
// This program is distributed in the hope that it will be useful,        //
// but WITHOUT ANY WARRANTY; without even the implied warranty of         //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
// GNU General Public License for more details.                           //
//                                                                        //
// You should have received a copy of the GNU General Public License      //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
//========================================================================//

#pragma once

#include <SFML/Graphics.hpp>
#include "wall.hpp"
#include "enemyController.hpp"
#include <queue>
#include <stack>
#include "coordinate.hpp"
#include "resourceHandler.hpp"

class tileController {
public:
	enum class Tileset {
		intro, regular
	};

	sf::Sprite transitionLvSpr;
	
	sf::Image tileImg[2];
	sf::Image grassSet[2];
	sf::Image grassSetEdge[2];

	tileController();
	void drawTiles(sf::RenderTexture&, std::vector<sf::Sprite*>*, std::vector<sf::Sprite*>*, int level, const float, const float);
	float posX;
	float posY;
	void setPosition(float, float);

	sf::RectangleShape shadow;
	
	sf::Texture mapTexture[2];
	sf::Sprite mapSprite1, mapSprite2;
	
	sf::RenderTexture rt, re;
	
	uint8_t mapArray[61][61];

	std::vector <wall> walls;

	std::vector<Coordinate> emptyMapLocations;
	std::vector<Coordinate> edgeLocations;
	std::vector<Coordinate> primeChestLocations;	// Find tiles with small number of neighbors, good place to hide items
	
	Coordinate teleporterLocation;
	
	Coordinate getTeleporterLoc();
		
	float windowH;
	float windowW;
	//Declare an array to keep track of the positions of objects drawn to the map as not to place two in the same spot
	uint8_t descriptionArray[61][61];
	void clear();
	// Draw a different overworld based on choice of current working set of tiles
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

//
//  aStar.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/26/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef aStar_hpp
#define aStar_hpp

#include <vector>

#define MAP_WIDTH 61
#define MAP_HEIGHT 61

// A simple structure to hold ordered pairs
struct aStrCoordinate {
	int x, y;
	float f, g;
};

// Define a class for a node
std::vector<aStrCoordinate> astar_path(aStrCoordinate&, aStrCoordinate&, short map[MAP_WIDTH][MAP_HEIGHT]);

bool contains(std::vector<aStrCoordinate>&, aStrCoordinate&);

std::vector<aStrCoordinate> getAdjacent(aStrCoordinate&, aStrCoordinate&, short map[MAP_WIDTH][MAP_HEIGHT]);

float heuristic(int, int, int, int);

#endif /* aStar_hpp */

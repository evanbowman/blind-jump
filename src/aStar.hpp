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

#include <vector>
#include <stdint.h>

#define MAP_WIDTH 61
#define MAP_HEIGHT 61

// A simple structure to hold ordered pairs
struct aStrCoordinate {
	int x, y;
	float f, g;
};

// Define a class for a node
std::vector<aStrCoordinate> astar_path(aStrCoordinate&, aStrCoordinate&, uint8_t map[MAP_WIDTH][MAP_HEIGHT]);

bool contains(std::vector<aStrCoordinate>&, aStrCoordinate&);

std::vector<aStrCoordinate> getAdjacent(aStrCoordinate&, aStrCoordinate&, uint8_t map[MAP_WIDTH][MAP_HEIGHT]);

float heuristic(int, int, int, int);

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

#include "aStar.hpp"
#include <cmath>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

// Calculates a heuristic based on the distance between two nodes
inline float heuristic(int x1, int x2, int y1, int y2) {
	return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

namespace std {
	template <>
	struct hash<aStrCoordinate> {
		inline size_t operator()(const aStrCoordinate& n) const {
			return n.x * 1812433253 + n.y;
		}
	};
}

// Overloaded operator for comparing two nodes
bool operator!=(const aStrCoordinate& a, const aStrCoordinate& b)  {
	return (a.x != b.x) || (a.y != b.y);
}

// Overloaded operator for comparing two nodes
bool operator==(const aStrCoordinate& a, const aStrCoordinate& b)  {
	return (a.x == b.x) && (a.y == b.y);
}

struct compare {
	bool operator()(const aStrCoordinate& a,const aStrCoordinate& b) const {
		return a.f < b.f;
	}
};

// A function to return a list of adjacent empty squares
std::vector<aStrCoordinate> getAdjacent(aStrCoordinate& coord, aStrCoordinate& target, short map[MAP_WIDTH][MAP_HEIGHT]) {
	// Declare a vector of adjacent coordinates to return
	std::vector<aStrCoordinate> adjacentTiles;
	bool diagonalMove = true;
	// Look left
	if (map[coord.x-1][coord.y] == 3 || map[coord.x-1][coord.y] == 4 || map[coord.x-1][coord.y] == 5 || map[coord.x-1][coord.y] == 8 || map[coord.x-1][coord.y] == 11) {
		aStrCoordinate newCoord;
		newCoord.g = coord.g + 1;
		newCoord.x = coord.x - 1;
		newCoord.y = coord.y;
		newCoord.f = newCoord.g + heuristic(newCoord.x, target.x, newCoord.y, target.y);
		adjacentTiles.push_back(newCoord);
	}
	else {
		diagonalMove = false;
	}
	
	// Check right
	if (map[coord.x+1][coord.y] == 3 || map[coord.x+1][coord.y] == 4 || map[coord.x+1][coord.y] == 5 || map[coord.x+1][coord.y] == 8 || map[coord.x+1][coord.y] == 11) {
		aStrCoordinate newCoord;
		newCoord.g = coord.g + 1;
		newCoord.x = coord.x + 1;
		newCoord.y = coord.y;
		newCoord.f = newCoord.g + heuristic(newCoord.x, target.x, newCoord.y, target.y);
		adjacentTiles.push_back(newCoord);
	}
	else {
		diagonalMove = false;
	}
	
	// Inspect up
	if (map[coord.x][coord.y-1] == 3 || map[coord.x][coord.y-1] == 4 || map[coord.x][coord.y-1] == 5 || map[coord.x][coord.y-1] == 8 || map[coord.x][coord.y-1] == 11) {
		aStrCoordinate newCoord;
		newCoord.g = coord.g + 1;
		newCoord.x = coord.x;
		newCoord.y = coord.y - 1;
		newCoord.f = newCoord.g + heuristic(newCoord.x, target.x, newCoord.y, target.y);
		adjacentTiles.push_back(newCoord);
	}
	else {
		diagonalMove = false;
	}
	
	// Look down
	if (map[coord.x][coord.y+1] == 3 || map[coord.x][coord.y+1] == 4 || map[coord.x][coord.y+1] == 5 || map[coord.x][coord.y+1] == 8 || map[coord.x][coord.y+1] == 11) {
		aStrCoordinate newCoord;
		newCoord.g = coord.g + 1;
		newCoord.x = coord.x;
		newCoord.y = coord.y + 1;
		newCoord.f = newCoord.g + heuristic(newCoord.x, target.x, newCoord.y, target.y);
		adjacentTiles.push_back(newCoord);
	}
	else {
		diagonalMove = false;
	}
	
	// Diagonal directions
	if (diagonalMove) {
		if (map[coord.x+1][coord.y+1] == 3 || map[coord.x+1][coord.y+1] == 4 || map[coord.x+1][coord.y+1] == 5 || map[coord.x+1][coord.y+1] == 8 || map[coord.x][coord.y+1] == 11) {
			aStrCoordinate newCoord;
			newCoord.g = coord.g + 1;
			newCoord.x = coord.x + 1;
			newCoord.y = coord.y + 1;
			newCoord.f = newCoord.g + heuristic(newCoord.x, target.x, newCoord.y, target.y);
			adjacentTiles.push_back(newCoord);
		}
		if (map[coord.x-1][coord.y+1] == 3 || map[coord.x-1][coord.y+1] == 4 || map[coord.x-1][coord.y+1] == 5 || map[coord.x-1][coord.y+1] == 8 || map[coord.x-1][coord.y+1] == 11) {
			aStrCoordinate newCoord;
			newCoord.g = coord.g + 1;
			newCoord.x = coord.x - 1;
			newCoord.y = coord.y + 1;
			newCoord.f = newCoord.g + heuristic(newCoord.x, target.x, newCoord.y, target.y);
			adjacentTiles.push_back(newCoord);
		}
		if (map[coord.x-1][coord.y-1] == 3 || map[coord.x-1][coord.y-1] == 4 || map[coord.x-1][coord.y-1] == 5 || map[coord.x-1][coord.y-1] == 8 || map[coord.x-1][coord.y-1] == 11) {
			aStrCoordinate newCoord;
			newCoord.g = coord.g + 1;
			newCoord.x = coord.x - 1;
			newCoord.y = coord.y - 1;
			newCoord.f = newCoord.g + heuristic(newCoord.x, target.x, newCoord.y, target.y);
			adjacentTiles.push_back(newCoord);
		}
		if (map[coord.x+1][coord.y+1] == 3 || map[coord.x+1][coord.y+1] == 4 || map[coord.x+1][coord.y+1] == 5 || map[coord.x+1][coord.y+1] == 8 || map[coord.x+1][coord.y+1] == 11) {
			aStrCoordinate newCoord;
			newCoord.g = coord.g + 1;
			newCoord.x = coord.x + 1;
			newCoord.y = coord.y + 1;
			newCoord.f = newCoord.g + heuristic(newCoord.x, target.x, newCoord.y, target.y);
		}
	}
	// Return the new vector
	return adjacentTiles;
}

bool contains(std::vector<aStrCoordinate>& closed, aStrCoordinate& node) {
	for (auto element : closed) {
		if (element.x == node.x && element.y == node.y) {
			return true;
		}
	}
	
	return false;
}

std::vector<aStrCoordinate> reconstruct_path(aStrCoordinate start, aStrCoordinate goal, std::unordered_map<aStrCoordinate, aStrCoordinate>& came_from) {
	std::vector<aStrCoordinate> path;
	aStrCoordinate current = goal;
	path.push_back(current);
	while (current != start) {
		current = came_from[current];
		path.push_back(current);
	}
	std::reverse(path.begin(), path.end());
	return path;
}

// The main function for finding a path between two points using the A* algorithm
std::vector<aStrCoordinate> astar_path(aStrCoordinate& origin, aStrCoordinate& target, short map[MAP_WIDTH][MAP_HEIGHT]) {
	// The open and closed sets of nodes
	std::vector<aStrCoordinate> closed;
	std::vector<aStrCoordinate> open = {origin};
	// Push the first node onto the heap, it has a g score of 0 (no moves yet)
	origin.g = 0;
	origin.f = heuristic(origin.x, target.x, origin.y, target.y);
	// Make the vector into a heap (priority_queue does not give access to underlying vector)
	std::make_heap(open.begin(), open.end(), compare());
	// Map of previous nodes
	std::unordered_map<aStrCoordinate, aStrCoordinate> cameFrom;
	cameFrom[origin] = origin;
	
	do {
		// Retrieve the node from the priority queue with the lowest f score
		aStrCoordinate currentNode = open.back();
		closed.push_back(currentNode);
		// Remove the top node from the priority queue
		open.pop_back();
		//std::pop_heap(open.begin(), open.end(), compare());
		
		// Check if the closed list contains the target node
		for (auto element : closed) {
			if (element.x == target.x && element.y == target.y) {
				// If the open set contains the target node, break execution
				return reconstruct_path(origin, target, cameFrom);
			}
		}
		// Now get the adjacent tiles
		std::vector<aStrCoordinate> adjacentTiles = getAdjacent(currentNode, target, map);
		for (auto element : adjacentTiles) {
			// If it's already in the closed list
			if (contains(closed, element)) {
				continue;
			}
			// If it's not in the open list yet
			if (!contains(open, element)) {
				// Add the element to both the open set and heapify
				open.push_back(element);
				cameFrom[element] = closed.back();
				std::push_heap(open.begin(), open.end(), compare());
			}
			// If it's already in the open list and the current g score makes f lower,
			else {
				////*** See how important this is
			}
		}
		
	} while (!open.empty());
	
	return closed;
}

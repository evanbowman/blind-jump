//
//  Header.h
//  Blind Jump
//
//  Created by Evan Bowman on 2/16/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//
//  This algorithm procedurally generates a lighting map for lights using additive
//  blending by first drawing circles at every point on a game map, randomly shuffling
//  the resulting list, and then iterating through it and for each circle removing all
//  overlapping circles.



#ifndef lightingmap_h
#define lightingmap_h

#include <vector>
#include "coordinate.hpp"
#include <cmath>

#define CIRC_RADIUS 200

typedef struct __circle {
	int x;
	int y;
	int r;
} Circle;

bool checkOverlap(Circle c1, Circle c2) {
	double centerDifference = sqrt((double) (32 * (c1.x - c2.x)) * (32 * (c1.x - c2.x)) + (26 * (c1.y - c2.y)) * (26 * (c1.y - c2.y)));
	if (centerDifference <= (double) c1.r || centerDifference <= (double) c2.r) {
		return true;
	}
	return false;
}

void getLightingPositions(short gameMap[61][61], std::vector<Coordinate>& availableLocations) {
	// First create a temporary map containing only the surfaces from the game map
	std::vector<Circle> lightMap;
	int i, j;
	for (i = 0; i < 61; i++) {
		for (j = 0; j < 61; j++) {
			Circle c;
			if (gameMap[i][j] == 3 || gameMap[i][j] == 4 || gameMap[i][j] == 8 || gameMap[i][j] == 11) {
				c.x = i;
				c.y = j;
				c.r = CIRC_RADIUS + rand() % 40;
				lightMap.push_back(c);
			}
		}
	}
	
	size_t length = lightMap.size();
	// Randomly shuffle the vector so not to just pick elements that are spatially close
	std::random_shuffle(lightMap.begin(), lightMap.end());
	for (size_t i = 0; i < length; i++) {
		// Remove all intersecting circles
		for (std::vector<Circle>::iterator it = lightMap.begin(); it != lightMap.end();) {
			if (checkOverlap(lightMap[i], *it) && (it->x != lightMap[i].x || it->y != lightMap[i].y)) {
				it = lightMap.erase(it);
				length--;
			}
			
			else {
				// Go to the next element
				++it;
			}
		}
	}
	
	// Now add whatever's left to the vector of available coordinates
	for (auto element : lightMap) {
		Coordinate c;
		c.x = element.x;
		c.y = element.y;
		availableLocations.push_back(c);
	}
}

#endif /* Header_h */

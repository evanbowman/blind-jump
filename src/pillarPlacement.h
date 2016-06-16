//
//  pillarPlacement.h
//  Blind Jump
//
//  Created by Evan Bowman on 3/6/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef pillarPlacement_h
#define pillarPlacement_h

#include <vector>
#include "coordinate.hpp"
#include <cmath>

#define PILLAR_RADIUS 180

void getRockPositions(short gameMap[61][61], std::vector<Coordinate>& availableLocations) {
	// First create a temporary map containing only the surfaces from the game map
	std::vector<Circle> pillarMap;
	int i, j;
	
	auto checkOverlap = [](Circle c1, Circle c2) {
		double centerDifference = sqrt((double) (32 * (c1.x - c2.x)) * (32 * (c1.x - c2.x)) + (26 * (c1.y - c2.y)) * (26 * (c1.y - c2.y)));
		if (centerDifference <= (double) c1.r || centerDifference <= (double) c2.r) {
			return true;
		}
		return false;
	};
	
	for (i = 0; i < 61; i++) {
		for (j = 0; j < 61; j++) {
			Circle c;
			if (gameMap[i][j] == 3 || gameMap[i][j] == 4) {
				c.x = i;
				c.y = j;
				c.r = PILLAR_RADIUS + rand() % 60;
				pillarMap.push_back(c);
			}
		}
	}
	
	size_t length = pillarMap.size();
	// Randomly shuffle the vector so not to just pick elements that are spatially close
	std::random_shuffle(pillarMap.begin(), pillarMap.end());
	for (size_t i = 0; i < length; i++) {
		// Remove all intersecting circles
		for (std::vector<Circle>::iterator it = pillarMap.begin(); it != pillarMap.end();) {
			if (checkOverlap(pillarMap[i], *it) && (it->x != pillarMap[i].x || it->y != pillarMap[i].y)) {
				it = pillarMap.erase(it);
				length--;
			}
			
			else {
				// Go to the next element
				++it;
			}
		}
	}
	
	// Now add whatever's left to the vector of available coordinates
	for (auto element : pillarMap) {
		Coordinate c;
		c.x = element.x;
		c.y = element.y;
		availableLocations.push_back(c);
	}
}

#endif /* pillarPlacement_h */

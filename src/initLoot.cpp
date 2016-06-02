//
//  initLoot.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/4/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//
//  This function determines which items will be placed
//  on which levels, by assigning weighted values to each
//  item type.
//  Conditions:
//  -- At least one hidden weapon per four levels.
//  -- At least one health container per four levels.
//

#include "initLoot.hpp"
#include <map>
#include <random>
#include <tuple>

#define NUM_LEVELS 48

void initLoot(char itemArray[48][3]) {
	// Store item weights and corresponding items in a vector
	std::vector<std::pair<int/*Weight*/, char/*Item index*/>> items = {
		std::make_pair(60, 1),
		std::make_pair(60, 2),
		std::make_pair(40, 3),
		std::make_pair(40, 4),
		std::make_pair(35, 5)
	};
	
	// Initialize the item array values to 0
	for (int i = 0; i < 48; i++) {
		itemArray[i][0] = 0;
		itemArray[i][1] = 0;
	}
	
	// Because I didn't want to just copypaste everywhere and didn't feel like writing a separate function
	auto deleteElement = [](std::vector<std::pair<int, char>> &items, char target) {
		for (auto it = items.begin(); it != items.end();) {
			if (it->second == target) {
				it = items.erase(it);
			}
			else {
				++it;
			}
		}
	};
	
	// Now for each level, there's a 1 in 4 chance of placing new weapon
	// But if four levels have passed with no weapons placed, need to add one
	int placeCounter = 0;
	// Number of steps to place the next life capsule
	char nextCapsule = rand() % 4 + 2;
	for (int i = 1; i < NUM_LEVELS; i++) {
		if (!items.empty()) {
			// First figure out the total sum of all item weights remaining in the vector
			int weightSum = 0;
			for (auto element : items) {
				weightSum += element.first;
			}
			// Now lets create a map and fill it with the vector's weighted elements
			std::map<double, char> distribution;
			// ***THE PRECISION IS ACTUALLY IMPORTANT HERE OR I WOULD BE USING FLOATS***
			double fractionSoFar = 0;
			for (auto element : items) {
				fractionSoFar += ((double) element.first) / ((double) weightSum);
				distribution[fractionSoFar] = element.second;
			}
			// With 12.5% chance, place a weapon on the level, but only if there are items left to place
			if (!(rand() % 8)) {
				// Sample the map
				double linear = rand() * 1.0 / RAND_MAX;
				itemArray[i][0] = distribution.upper_bound(linear)->second;
				// Just placed an item, so set counter back to 0
				placeCounter = 0;
				// Don't want to place the same item twice! So delete it from the vector
				deleteElement(items, distribution.upper_bound(linear)->second);
			}
			// If no items have been placed for a while
			else if (placeCounter == 6) {
				double linear = rand() * 1.0 / RAND_MAX;
				itemArray[i][0] = distribution.upper_bound(linear)->second;
				deleteElement(items, distribution.upper_bound(linear)->second);
			}
			// Increment the counter
			placeCounter++;
			if (placeCounter > 6) {
				placeCounter = 0;
			}
		}
		
		if (--nextCapsule == 0) {
			nextCapsule = (rand() % 3) + 5;
			itemArray[i][1] = 90;
		}
	}
}

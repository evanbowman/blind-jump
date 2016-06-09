//
//  treasureChest.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 11/14/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef treasureChest_hpp
#define treasureChest_hpp

#include <stdio.h>
#include "detailParent.hpp"
#include "inputController.hpp"
#include "spriteSheet.hpp"

class TreasureChest : public detailParent {
public:
	TreasureChest(float, float, sf::Texture *, sf::Texture *, int, float, float, char);
	sf::Sprite* getShadow();
	sf::Sprite* getSprite();
	void update(float, float, char, InputController*, sf::Time&);
	float getZY();
	char getFrameIndex();
	bool isValid();
	char getItem();
	
private:
	bool animationIsRunning;
	int32_t animationTimer;
	uint8_t frameIndex;
	// Boolean to keep track of opened or closed
	bool isOpen;
	char item;
	bool valid;
	SpriteSheet<16, 32> chestSheet;
	sf::Sprite chestShadow;
};
#endif /* treasureChest_hpp */

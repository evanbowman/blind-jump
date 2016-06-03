//
//  teleporterSmoke.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/1/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef teleporterSmoke_hpp
#define teleporterSmoke_hpp

#include <stdio.h>
#include "sfml/graphics.hpp"

class TeleporterSmoke {
private:
	float xPos;
	float yPos;
	float xInit;
	float yInit;
	unsigned int frameTimer;
	uint8_t frameIndex;
	sf::Sprite effectSprites[6];
	// Boolean variable that goes from low to high when the animation ends (triggers controller to remove the object)
	bool killFlag;
	// Smoke changes depth with time, store in variable
	char drawOrder;
	
public:
	// Constructor arguments are initial position and input sprites from the effect controller object
	TeleporterSmoke(sf::Sprite inputSprites[6], float, float);
	// For updating the position with external offset information
	void update(float, float, sf::Time &);
	sf::Sprite getSprite();
	// Accessor function to determine whether the animation is done running
	bool getKillFlag();
	float getPosX();
	float getYpos();
	char getDrawOrder();
};
#endif /* teleporterSmoke_hpp */

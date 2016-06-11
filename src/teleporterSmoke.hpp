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
#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"

class TeleporterSmoke {
private:
	float xPos;
	float yPos;
	float xInit;
	float yInit;
    int32_t frameTimer;
	uint8_t frameIndex;
	SpriteSheet<16, 16> spriteSheet;
   	bool killFlag;
	// Smoke changes depth with time, store in variable
	char drawOrder;
	
public:
	// Constructor arguments are initial position and input sprites from the effect controller object
	TeleporterSmoke(sf::Texture *, float, float);
	// For updating the position with external offset information
	void update(float, float, sf::Time &);
	const sf::Sprite & getSprite();
	// Accessor function to determine whether the animation is done running
	bool getKillFlag();
	float getPosX();
	float getYpos();
	char getDrawOrder();
};
#endif /* teleporterSmoke_hpp */

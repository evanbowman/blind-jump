//
//  shotPoof.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/14/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef shotPuff_hpp
#define shotPuff_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "spriteSheet.hpp"

class shotPuff {
public:
	shotPuff(sf::Texture *, float, float, char, int);
	float xPos;
	float yPos;
	float xInit;
	float yInit;
	void update(float, float, sf::Time &);
	const sf::Sprite & getSprite();
	bool getKillFlag();
	float getYpos();
	
private:
	int frameIndex;
	int32_t frameTimer;
	SpriteSheet<16, 16> spriteSheet;
	bool killFlag;
};
#endif /* shotPuff_hpp */

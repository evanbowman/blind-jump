//
//  smallExplosion.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/19/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef smallExplosion_hpp
#define smallExplosion_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"

class SmallExplosion {
private:
	SpriteSheet<36, 36> spriteSheet;
	sf::Sprite glow;
	float xInit, yInit, xPos, yPos;
	bool killFlag;
	uint8_t frameIndex;
	uint32_t timer;
	
public:
	SmallExplosion(sf::Texture *, sf::Texture *, float, float);
	void update(float, float, const sf::Time &);
	const sf::Sprite & getSprite();
	bool getKillFlag();
	float getYpos();
	sf::Sprite * getGlow();
};

#endif /* smallExplosion_hpp */

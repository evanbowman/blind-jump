//
//  turretFlashEffect.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef turretFlashEffect_hpp
#define turretFlashEffect_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"

class turretFlashEffect {
private:
	SpriteSheet<16, 16> spriteSheet;
	float xPos;
	float yPos;
	float xInit;
	float yInit;
	sf::Clock clock;
	bool killFlag;
	uint8_t imageIndex;
	
public:
	void update(float, float);
	turretFlashEffect(sf::Texture *, float, float);
	float getYpos();
	bool getKillFlag();
	const sf::Sprite & getSprite();
};
#endif /* turretFlashEffect_hpp */

//
//  enemyShot.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/2/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef enemyShot_hpp
#define enemyShot_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include <cmath>
#include "spriteSheet.hpp"

class Enemyshot {
private:
	SpriteSheet <14, 14> spriteSheet;
	float xPos;
	float yPos;
	float xInit;
	double yInit;
	unsigned char imageIndex;
	int32_t frameTimer;
	int32_t elapsedTime;
	float direction;
	bool killFlag;
	sf::Sprite glowSprite;
	
public:
	Enemyshot(sf::Texture *, sf::Texture *, float, float, float);
	void update(float, float, sf::Time &);
	const sf::Sprite & getSprite();
	bool getKillFlag();
	void setKillFlag();
	float getXpos();
	float getYpos();
	sf::Sprite * getGlow();
};

#endif /* enemyShot_hpp */

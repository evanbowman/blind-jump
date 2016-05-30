//
//  healthEffect.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/9/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef healthEffect_hpp
#define healthEffect_hpp

#include <stdio.h>
#include "SFML/graphics.hpp"

class HealthEffect {
private:
	float xInit;
	float yInit;
	sf::Sprite spr;
	bool killFlag;
	unsigned short lifeCounter;
	char mode;
	
public:
	void update(float, float);
	bool getKillFlag();
	sf::Sprite getSprite();
	HealthEffect(sf::Sprite, float, float);
	void setMode(char, float, float);
	float getYpos();
};

#endif /* healthEffect_hpp */

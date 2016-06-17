//
//  Hearts.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 4/2/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef Hearts_hpp
#define Hearts_hpp

#include "SFML/Graphics.hpp"
#include <cmath>
#include "spritesheet.hpp"

class Powerup {
private:
	float xInit, yInit, xPos, yPos;
	sf::Sprite glow;
	SpriteSheet<13, 13> powerupSheet;
	bool killFlag; 
	// to keep time, for making hearts float up and down
	int32_t timer;
	
public:
	enum class Type {
		heart, coin
			};
	
	Powerup(const sf::Texture &, const sf::Texture &, float, float, Type);
	bool getKillFlag();
	void setKillFlag(bool);
	const sf::Sprite & getSprite();
	sf::Sprite* getGlow();
	void update(float, float, sf::Time &);
	float getXpos();
	float getYpos();
};

#endif /* Hearts_hpp */

//
//  bulletType1.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/14/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef bulletType1_hpp
#define bulletType1_hpp

#include <SFML/Graphics.hpp>
#include "spriteSheet.hpp"

class bulletType1 {
private:
	SpriteSheet<16, 16> spriteSheet;
	sf::Sprite glow;
	char direction;
	float xPos;
	float yPos;
	float xInit;
	float yInit;
	bool killFlag;
	bool canPoof;
	sf::Clock clock;
	
public:
	bulletType1(const sf::Texture &, const sf::Texture &, char, float, float);
	const sf::Sprite & getSprite();
	sf::Sprite* getGlow();
	void update(float, float);
	bool getKillFlag();
	void setKillFlag();
	void setPosition(float, float);
	float getXpos();
	float getYpos();
	char getDirection();
	bool checkCanPoof();
	void disablePuff();
};

#endif /* bulletType1_hpp */

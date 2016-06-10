//
//  FireExplosion.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/18/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef FireExplosion_hpp
#define FireExplosion_hpp

#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"

class FireExplosion {
private:
	SpriteSheet<58, 51> spriteSheet;
	sf::Sprite glow;
	float xInit, yInit, xPos, yPos;
	bool killFlag;
	uint8_t frameIndex;
	int32_t animationTimer;
	bool valid;
	
public:
	FireExplosion(sf::Texture *, sf::Texture *, float, float);
	void update(float, float, sf::Time &);
	const sf::Sprite & getSprite();
	bool getKillFlag();
	float getYpos();
	float getXpos();
	sf::Sprite * getGlow();
	void setOrigin(int, int);
	bool isValid();
	void invalidate();
};

#endif /* FireExplosion_hpp */

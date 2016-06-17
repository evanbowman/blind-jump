//
//  turretShot.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/26/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef turretShot_hpp
#define turretShot_hpp

#include "SFML/Graphics.hpp"
#include <cmath>
#include "spritesheet.hpp"

class turretShot {
public:
	turretShot(sf::Texture *, sf::Texture *, float, float, float);
	float xPos;
	float yPos;
	float xInit;
	float yInit;
	SpriteSheet<9, 16> spriteSheet;
	sf::Sprite glowSprite;
	sf::Sprite * getGlow();
	const sf::Sprite & getSprite();
	void update(float, float, sf::Time&);
	float direction;
	bool killFlag;
	bool getKillFlag();
	void setKillFlag();
	float getXpos();
	float getYpos();
	void speedFactor(float);
	int32_t timer;
	int32_t animationTimer;
	
private:
	float scale;
	uint8_t frameIndex;	
};
#endif /* turretShot_hpp */

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

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include <cmath>

class turretShot {
public:
	turretShot(sf::Sprite*, sf::Sprite, float, float, float);
	float xPos;
	float yPos;
	float xInit;
	float yInit;
	sf::Sprite sprs[2];
	sf::Sprite glowSprite;
	sf::Sprite* getGlow();
	sf::Sprite getSprite();
	void update(float, float, sf::Time&);
	char imageIndex;
	float direction;
	bool killFlag;
	bool getKillFlag();
	void setKillFlag();
	float getXpos();
	float getYpos();
	void speedFactor(float);
	void enableTracking(float, float);
	float playerPosX;
	float playerPosY;
	unsigned int timer;
	unsigned int animationTimer;
	
private:
	float scale;
	bool trackPlayer;
	char frameIndex;	
};
#endif /* turretShot_hpp */

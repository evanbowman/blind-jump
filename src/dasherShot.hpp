//
//  dasherShot.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/12/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef dasherShot_hpp
#define dasherShot_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include <cmath>

class DasherShot {
public:
	DasherShot(sf::Sprite*, sf::Sprite, float, float, float);
	float xPos;
	float yPos;
	float xInit;
	float yInit;
	sf::Sprite sprs[2];
	const sf::Sprite & getSprite();
	void update(float, float, sf::Time &);
	char imageIndex;
	float direction;
	bool killFlag;
	bool getKillFlag();
	float getXpos();
	float getYpos();
	void speedFactor(float);
	float playerPosX;
	float playerPosY;
	bool frameIndex;
	bool driftSel;
	sf::Sprite* getGlow();
	void setKillFlag();
	
private:
	int32_t timer, timeout;
	float scale;
	bool trackPlayer;
	sf::Sprite glowSprite;
};

#endif /* dasherShot_hpp */

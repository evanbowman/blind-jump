//
//  enemyParent.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/21/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef enemy_hpp
#define enemy_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include "wall.hpp"
#include "effectsController.hpp"
#include <vector>
#include <cmath>

class Enemy {
protected:
	virtual void onDeath(effectsController &) = 0;
	bool killFlag, colored;
	float xInit, yInit, playerPosX, playerPosY, xPos, yPos, colorAmount;
	uint8_t frameIndex, health;
	uint32_t colorTimer, frameTimer;
	bool checkWallCollision(std::vector<wall> &, float, float, float);
	bool wallInPath(std::vector<wall> &, float, float, float);

public:
	Enemy(float, float, float, float);
	virtual const sf::Sprite & getSprite() const = 0;
	virtual const sf::Sprite & getShadow() const = 0;
	void update(float, float);
	virtual void update(float, float, const std::vector<wall> &, effectsController & ef,  const sf::Time &) = 0;
	bool getKillFlag() const;
	bool isColored() const;
	float getXinit() const;
	float getYinit() const;
	float getXpos() const;
	float getYpos() const;
	float getColorAmount() const;
};

#endif /* enemyParent_hpp */

//
//  chaser.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/26/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef chaser_hpp
#define chaser_hpp

#include <stdio.h>
#include "enemyParent.hpp"
#include "effectsController.hpp"
#include "aStar.hpp"

class tileController;

class Critter : public EnemyParent {
public:
	// This calls the parent constructor, which initializes common values like initial position
	Critter(sf::Sprite*, short map[61][61]);
	// A function to update all of the enemy's values
	void update(float, float, effectsController&, tileController*, sf::Time &);
	sf::Sprite * getSprite();
	sf::Sprite * getShadow();
	void softUpdate(float, float);
	void checkBulletCollision(effectsController& ef);
	void randDir();
	void activate();
	void deActivate();
	bool isActive();
	uint8_t frameIndex;
	char frameRate;
	void updatePlayerDead();
	
private:
	float health;
	float currentDir, chargeDir;
	float jumpTargetx, jumpTargety;
	void newPath(tileController*);
	sf::Sprite sprites[4];
	aStrCoordinate previous;
	bool awake;
	// The current path of enemy to the player
	std::vector<aStrCoordinate> path;
	// Next positon to move to
	bool active, attacking;
	int moveCounter, recalc, moveCount, dashCount;
	// Store a pointer to the game map
	short (*map)[61]; //*** I know this is a nasty solution, perhaps there's a better way to not store it locally...
};

#endif /* chaser_hpp */

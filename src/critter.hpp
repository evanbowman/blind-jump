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

#include "enemy.hpp"
#include "effectsController.hpp"
#include "aStar.hpp"
#include "spriteSheet.hpp"

class tileController;

class Critter : public Enemy {
public:
	Critter(const sf::Texture &, short map[61][61], float, float, float, float);
	void update(float, float, const std::vector<wall> &, effectsController & ef, const sf::Time &) override;
	void critterUpdate(float, float, effectsController & ef, const sf::Time &, tileController * pTiles);
	const sf::Sprite & getSprite() const override;
	const sf::Sprite & getShadow() const override;
	void activate();
	void deActivate();
	bool isActive();
	void updatePlayerDead();
	
private:
	void onDeath(effectsController &) override;
    float currentDir;
	float jumpTargetx, jumpTargety;
	void newPath(tileController *);
	mutable SpriteSheet<0, 57, 18, 18> spriteSheet;
	sf::Sprite shadow;
	aStrCoordinate previous;
	bool awake;
	// The current path of enemy to the player
	std::vector<aStrCoordinate> path;
	// Next positon to move to
	bool active;
	int recalc;
	// Store a pointer to the game map
	short (*map)[61]; //*** I know this is a nasty solution, perhaps there's a better way to not store it locally...
};

#endif /* chaser_hpp */

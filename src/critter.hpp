//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "enemy.hpp"
#include "effectsController.hpp"
#include "aStar.hpp"
#include "spriteSheet.hpp"

class tileController;

class Critter : public Enemy {
public:
	using HBox = framework::HitBox<12, 12, 4, -3>;
	Critter(const sf::Texture &, uint8_t map[61][61], float, float);
	void update(float, float, const std::vector<wall> &, EffectGroup & ef, const sf::Time &);
	void critterUpdate(float, float, EffectGroup & ef, const sf::Time &, tileController & tiles);
	const sf::Sprite & getSprite() const;
	const sf::Sprite & getShadow() const;
	void activate();
	void deActivate();
	bool isActive();
	void updatePlayerDead();
	const HBox & getHitBox() const;
	
private:
	float xInit, yInit;
	void onDeath(EffectGroup &);
    float currentDir;
	float jumpTargetx, jumpTargety;
	void newPath(tileController &);
	mutable SpriteSheet<0, 57, 18, 18> spriteSheet;
	std::vector<aStrCoordinate> path;
	aStrCoordinate previous;
	sf::Sprite shadow;
	HBox hitBox;
	bool awake;
	bool active;
	int recalc;
	uint8_t (*map)[61]; //*** I know this is a nasty solution, perhaps there's a better way to not store it locally...
};

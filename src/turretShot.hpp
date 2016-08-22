//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <cmath>
#include "spriteSheet.hpp"
#include "Effect.hpp"
#include "rng.hpp"

class TurretShot : public Effect {
public:
	using HBox = Framework::HitBox<10, 10, -5, -5>;
	const HBox & getHitBox() const;
	TurretShot(const sf::Texture &, const sf::Texture &, float, float, float);
	const sf::Sprite & getGlow();
	const sf::Sprite & getSprite();
	void update(sf::Time&);
	void speedFactor(float);
	int32_t animationTimer;
	
private:
	SpriteSheet<26, 75, 9, 16> spriteSheet;
	HBox hitBox;
	sf::Sprite glowSprite;
	float direction;
	float scale;	
};

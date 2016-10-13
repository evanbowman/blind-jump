//========================================================================//
// Copyright (C) 2016 Evan Bowman										  //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.			  //
//========================================================================//

#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "spriteSheet.hpp"
#include "Effect.hpp"
#include "math.hpp"
#include "rng.hpp"

class EnemyShot : public Effect {
public:
	using HBox = framework::HitBox<14, 14, 0, 0>;
	EnemyShot(const sf::Texture &, const sf::Texture &, float, float, float);
	void update(const sf::Time &);
	const sf::Sprite & getSprite();
	const HBox & getHitBox() const;
	const sf::Sprite & getGlow() const;
	
private:
	HBox hitBox;
	SpriteSheet<50, 91, 14, 14> spriteSheet;
	int32_t frameTimer;
	float direction;
	sf::Sprite glowSprite;
	
};

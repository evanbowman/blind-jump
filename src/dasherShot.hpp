//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "SFML/Graphics.hpp"
#include <cmath>
#include "spriteSheet.hpp"
#include "Effect.hpp"
#include "rng.hpp"
#include "easingTemplates.hpp"

class DasherShot : public Effect {
public:
	using HBox = Framework::HitBox<12, 12, -6, -6>;
	DasherShot(const sf::Texture &, const sf::Texture &, float, float, float);
	SpriteSheet<0, 88, 12, 12> spriteSheet;
	const sf::Sprite & getSprite();
	void update(const sf::Time &);
	float direction;
	bool driftSel;
	const sf::Sprite & getGlow() const;
	const HBox & getHitBox() const;
	
private:
	int64_t timeout;
	float initialVelocity;
	HBox hitBox;
	sf::Sprite glowSprite;
};

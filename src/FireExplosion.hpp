//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <SFML/Graphics.hpp>
#include "spriteSheet.hpp"
#include "Effect.hpp"
#include "easingTemplates.hpp"

class FireExplosion : public Effect {
private:
	mutable SpriteSheet<208, 173, 58, 51> spriteSheet;
	sf::Sprite glow;
    int64_t glowFadeTimer;
	
public:
	FireExplosion(const sf::Texture &, const sf::Texture &, float, float);
	void update(const sf::Time &);
	const sf::Sprite & getSprite() const;
	const sf::Sprite & getGlow() const;
};

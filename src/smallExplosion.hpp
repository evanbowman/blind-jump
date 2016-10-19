//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <SFML/Graphics.hpp>
#include "spriteSheet.hpp"
#include "Effect.hpp"
#include "easingTemplates.hpp"

class SmallExplosion : public Effect {
private:
	mutable SpriteSheet<174, 224, 36, 36> spriteSheet;
	framework::Sprite glow;
	int64_t glowFadeTimer;
	
public:
	SmallExplosion(const sf::Texture &, const sf::Texture &, float, float);
	void update(const sf::Time &);
	const framework::Sprite & getSprite() const;
	const framework::Sprite & getGlow() const;
};

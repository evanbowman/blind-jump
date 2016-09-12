//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "spriteSheet.hpp"
#include "Effect.hpp"

class Item : public Effect {
public:
	enum class Type { Heart, Coin };
	using HBox = framework::HitBox<13, 13, -8, -8>;
	Item(const sf::Texture &, const sf::Texture &, float, float, Type);
	const sf::Sprite & getSprite();
	const HBox & getHitBox() const;
	const sf::Sprite & getGlow();
	void update(sf::Time &);
	
protected:
	HBox hitBox;
	Sprite glow;
	SpriteSheet<0, 75, 13, 13> powerupSheet;
};

//
//  Hearts.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 4/2/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef Hearts_hpp
#define Hearts_hpp

#include <SFML/Graphics.hpp>
#include <cmath>
#include "spritesheet.hpp"
#include "Effect.hpp"

class Powerup : public Effect {
public:
	enum class Type { Heart, Coin };
	using HBox = Framework::HitBox<13, 13, -8, -8>;
	Powerup(const sf::Texture &, const sf::Texture &, float, float, Type);
	const sf::Sprite & getSprite();
	const HBox & getHitBox() const;
	sf::Sprite * getGlow();
	void update(float, float, sf::Time &);
	
protected:
	HBox hitBox;
	Sprite glow;
	SpriteSheet<0, 75, 13, 13> powerupSheet;
};

#endif /* Hearts_hpp */

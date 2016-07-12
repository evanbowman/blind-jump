//
//  smallExplosion.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/19/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef smallExplosion_hpp
#define smallExplosion_hpp

#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"
#include "Effect.hpp"

class SmallExplosion : public Effect {
private:
	mutable SpriteSheet<174, 224, 36, 36> spriteSheet;
	sf::Sprite glow;
	
public:
	SmallExplosion(const sf::Texture &, const sf::Texture &, float, float);
	void update(float, float, const sf::Time &);
	const Sprite & getSprite() const;
	sf::Sprite * getGlow();
};

#endif /* smallExplosion_hpp */

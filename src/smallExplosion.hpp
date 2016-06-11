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

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"
#include "Effect.hpp"

class SmallExplosion : public Effect {
private:
	SpriteSheet<36, 36> spriteSheet;
	sf::Sprite glow;
	
public:
	SmallExplosion(sf::Texture *, sf::Texture *, float, float);
	virtual void update(float, float, const sf::Time &);
	virtual const sf::Sprite & getSprite();
	sf::Sprite * getGlow();
};

#endif /* smallExplosion_hpp */

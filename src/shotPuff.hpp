//
//  shotPoof.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/14/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef shotPuff_hpp
#define shotPuff_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "spriteSheet.hpp"
#include "Effect.hpp"

class shotPuff : public Effect {
private:
	SpriteSheet<16, 16> spriteSheet;

public:
	shotPuff(sf::Texture *, float, float);
	virtual void update(float, float, const sf::Time &);
	virtual const sf::Sprite & getSprite();
	
};
#endif /* shotPuff_hpp */

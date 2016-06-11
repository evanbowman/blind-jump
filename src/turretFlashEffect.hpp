//
//  turretFlashEffect.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef turretFlashEffect_hpp
#define turretFlashEffect_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"
#include "Effect.hpp"

class turretFlashEffect : public Effect {
private:
	SpriteSheet<16, 16> spriteSheet;
	
public:
	turretFlashEffect(sf::Texture *, float, float);
	virtual void update(float, float, const sf::Time &);
	virtual const sf::Sprite & getSprite();
};

#endif /* turretFlashEffect_hpp */

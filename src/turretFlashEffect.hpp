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

#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"
#include "Effect.hpp"

class turretFlashEffect : public Effect {
private:
	mutable SpriteSheet<0, 116, 16, 16> spriteSheet;
	
public:
	turretFlashEffect(const sf::Texture &, float, float);
	void update(float, float, const sf::Time &) override;
	const sf::Sprite & getSprite() const override;
};

#endif /* turretFlashEffect_hpp */

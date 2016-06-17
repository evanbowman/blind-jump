//
//  FireExplosion.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/18/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef FireExplosion_hpp
#define FireExplosion_hpp

#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"
#include "Effect.hpp"

class FireExplosion : public Effect {
private:
	mutable SpriteSheet<58, 51> spriteSheet;
	sf::Sprite glow;
	bool valid;
	
public:
	FireExplosion(const sf::Texture &, const sf::Texture &, float, float);
	void update(float, float, const sf::Time &) override;
	const sf::Sprite & getSprite() const override;
	sf::Sprite * getGlow();
	bool isValid();
	void invalidate();
};

#endif /* FireExplosion_hpp */

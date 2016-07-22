//
//  enemyShot.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/2/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef enemyShot_hpp
#define enemyShot_hpp

#include "SFML/Graphics.hpp"
#include <cmath>
#include "spriteSheet.hpp"
#include "Effect.hpp"
#include "rng.hpp"

class EnemyShot : public Effect {
public:
	using HBox = Framework::HitBox<14, 14, 0, 0>;
	EnemyShot(const sf::Texture &, const sf::Texture &, float, float, float);
	void update(float, float, sf::Time &);
	const sf::Sprite & getSprite();
    const HBox & getHitBox() const;
	sf::Sprite * getGlow();
	
private:
	HBox hitBox;
	SpriteSheet<50, 91, 14, 14> spriteSheet;
	int32_t frameTimer;
	float direction;
	sf::Sprite glowSprite;
	
};

#endif /* enemyShot_hpp */

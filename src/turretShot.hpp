//
//  turretShot.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/26/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef turretShot_hpp
#define turretShot_hpp

#include <cmath>
#include "spritesheet.hpp"
#include "Effect.hpp"
#include "hitBox.hpp"

class TurretShot : public Effect {
public:
	using HBox = HitBox<10, 10, -5, -5>;
	const HBox & getHitBox() const;
	TurretShot(const sf::Texture &, const sf::Texture &, float, float, float);
	sf::Sprite * getGlow();
	const sf::Sprite & getSprite();
	void update(float, float, sf::Time&);
	void speedFactor(float);
	int32_t animationTimer;
	
private:
	SpriteSheet<26, 75, 9, 16> spriteSheet;
	HBox hitBox;
	sf::Sprite glowSprite;
	float direction;
	float scale;
	uint8_t frameIndex;	
};
#endif /* TurretShot_hpp */

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

#include "SFML/Graphics.hpp"
#include <cmath>
#include "spritesheet.hpp"
#include "Effect.hpp"

class TurretShot : public Effect {
public:
	TurretShot(const sf::Texture &, const sf::Texture &, float, float, float);
	SpriteSheet<26, 75, 9, 16> spriteSheet;
	sf::Sprite glowSprite;
	sf::Sprite * getGlow();
	const sf::Sprite & getSprite();
	void update(float, float, sf::Time&);
	float direction;
	void speedFactor(float);
	int32_t animationTimer;
	
private:
	float scale;
	uint8_t frameIndex;	
};
#endif /* TurretShot_hpp */

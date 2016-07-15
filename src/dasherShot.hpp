//
//  dasherShot.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/12/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef dasherShot_hpp
#define dasherShot_hpp

#include "SFML/Graphics.hpp"
#include <cmath>
#include "spriteSheet.hpp"
#include "Effect.hpp"
#include "hitBox.hpp"

class DasherShot : public Effect {
public:
	using HBox = HitBox<12, 12, -6, -6>;
	DasherShot(const sf::Texture &, const sf::Texture &, float, float, float);
	SpriteSheet<0, 88, 12, 12> spriteSheet;
	const sf::Sprite & getSprite();
	void update(float, float, sf::Time &);
	float direction;
	void speedFactor(float);
	bool driftSel;
	sf::Sprite * getGlow();
	const HBox & getHitBox() const;
	
private:
	int32_t timeout;
	float scale;
	HBox hitBox;
	sf::Sprite glowSprite;
};

#endif /* dasherShot_hpp */

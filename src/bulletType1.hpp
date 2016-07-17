//
//  bulletType1.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/14/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef bulletType1_hpp
#define bulletType1_hpp

#include <SFML/Graphics.hpp>
#include "spriteSheet.hpp"
#include "Effect.hpp"

class PlayerShot : public Effect {
public:
	using HBox = Framework::HitBox<12, 12, 2, 2>;
	PlayerShot(const sf::Texture &, const sf::Texture &, char, float, float);
	const sf::Sprite & getSprite();
	sf::Sprite * getGlow();
	void update(float, float, const sf::Time &);
	char getDirection();
	bool checkCanPoof();
	void poof();
	void disablePuff();
	const HBox & getHitBox() const;

private:
	HBox hitBox;
	SpriteSheet<44, 75, 16, 16> spriteSheet; // This could easily be a plain sprite, but the memory usage would be the same
	SpriteSheet<88, 145, 16, 16> puffSheet;
	sf::Sprite glow;
	char direction;
	bool canPoof;
	enum class State { travelling, poof };
	State state;
};

#endif /* bulletType1_hpp */

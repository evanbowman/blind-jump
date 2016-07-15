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
private:
	SpriteSheet<44, 75, 16, 16> spriteSheet;
	SpriteSheet<88, 145, 16, 16> puffSheet;
	sf::Sprite glow;
	char direction;
	bool canPoof;
	enum class State { travelling, poof };
	State state;
	
public:
	PlayerShot(const sf::Texture &, const sf::Texture &, char, float, float);
	const sf::Sprite & getSprite();
	sf::Sprite * getGlow();
	void update(float, float, const sf::Time &);
	char getDirection();
	bool checkCanPoof();
	void disablePuff();
};

#endif /* bulletType1_hpp */

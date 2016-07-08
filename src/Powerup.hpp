//
//  Hearts.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 4/2/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef Hearts_hpp
#define Hearts_hpp

#include "SFML/Graphics.hpp"
#include <cmath>
#include "spritesheet.hpp"
#include "hitBox.hpp"

class Powerup {
public:
	using HBox = HitBox<13, 13, 0, 0>;
	enum class Type {
		heart, coin
	};
	Powerup(const sf::Texture &, const sf::Texture &, float, float, Type);
	bool getKillFlag();
	void setKillFlag();
	const sf::Sprite & getSprite();
	const HBox & getHitBox() const;
	sf::Sprite* getGlow();
	void update(float, float, sf::Time &);
	float getXpos();
	float getYpos();

private:
	HBox hitBox;
	float xInit, yInit, xPos, yPos;
	sf::Sprite glow;
	SpriteSheet<0, 75, 13, 13> powerupSheet;
	bool killFlag; 
	// to keep time, for making hearts float up and down
	int32_t timer;
};

#endif /* Hearts_hpp */

#pragma once
#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "SFML/Graphics.hpp"

class Effect {
protected:
	float xInit, yInit, yPos;
	int16_t timer;
	bool killFlag;
	uint8_t frameIndex;

public:
	Effect(float, float);
	virtual void update(float, float, const sf::Time &) = 0;
	virtual const sf::Sprite & getSprite() const = 0;
	float getYpos() const;
	bool getKillFlag() const;
};

#endif

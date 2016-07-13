#pragma once
#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "SFML/Graphics.hpp"
#include "Framework/framework.hpp"

class Effect : public Framework::Object {
protected:
	int16_t timer;
	uint8_t frameIndex;
	float xInit, yInit;

public:
	Effect(float x, float y) : Object{0, 0}, timer{0}, frameIndex{0}, xInit{x}, yInit{y} {}
};

#endif

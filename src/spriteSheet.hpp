#pragma once
#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include "SFML/Graphics.hpp"

class SpriteSheet {
private:
	sf::Sprite sprite;
	uint16_t width, height;
	
public:
	SpriteSheet();
	sf::Sprite operator[](std::size_t);
	void setPosition(float, float);
	void setTexture(const sf::Texture *);
	void setSize(const uint16_t, const uint16_t);
};

#endif

#pragma once
#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include "SFML/Graphics.hpp"

template <uint16_t w, uint16_t h>
class SpriteSheet {
private:
	sf::Sprite sprite;
	
public:
	sf::Sprite operator[](std::size_t idx) {
		sprite.setTextureRect(sf::IntRect(idx * w, 0, w, h));
		return sprite;
	}
	
	void setPosition(float xPos, float yPos) {
		sprite.setPosition(xPos, yPos);
	}
	
	void setTexture(const sf::Texture * pTexture) {
		sprite.setTexture(*pTexture);
	}

	void setOrigin(const int16_t xCenter, const int16_t yCenter) {
		sprite.setOrigin(xCenter, yCenter);
	}
};

#endif

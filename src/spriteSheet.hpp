#pragma once
#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include "SFML/Graphics.hpp"

template <uint16_t w, uint16_t h>
class SpriteSheet {
private:
	sf::Sprite sprite;
	
public:
	const sf::Sprite & operator[](const std::size_t idx) {
		sprite.setTextureRect(sf::IntRect(idx * w, 0, w, h));
		return sprite;
	}

	sf::Sprite * getSpritePtr() {
		return &sprite;
	}

	const sf::Sprite & getSprite() {
		return sprite;
	}

	void setRotation(float degrees) {
		sprite.setRotation(degrees);
	}
	
	void setScale(float xScale, float yScale) {
		sprite.setScale(xScale, yScale);
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

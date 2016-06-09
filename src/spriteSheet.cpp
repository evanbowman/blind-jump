#include "spriteSheet.hpp"

SpriteSheet::SpriteSheet() {
	width = 1;
	height = 1;
}

sf::Sprite SpriteSheet::operator[](std::size_t idx) {
	sprite.setTextureRect(sf::IntRect(idx * width, 0, width, height));
	return sprite;
}

void SpriteSheet::setPosition(float xPos, float yPos) {
	sprite.setPosition(xPos, yPos);
}

void SpriteSheet::setTexture(const sf::Texture * pTexture) {
    sprite.setTexture(*pTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, width, height));
}

void SpriteSheet::setSize(const uint16_t width, const uint16_t height) {
	this->width = width;
	this->height = height;
}

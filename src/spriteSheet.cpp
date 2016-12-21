#include "spriteSheet.hpp"

SpriteSheet::SpriteSheet(const sf::Texture & texture,
			 const sf::IntRect & bounds) : m_sprite(texture),
						       m_bounds(bounds) {}

void SpriteSheet::setFrame(const int frameno) {
    m_sprite.setTextureRect(sf::IntRect{m_bounds.left + m_bounds.width * frameno, m_bounds.top, m_bounds.width, m_bounds.height});
}

sf::Sprite & SpriteSheet::getSprite() {
    return m_sprite;
}


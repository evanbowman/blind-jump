#pragma once

#include "framework/framework.hpp"
#include <SFML/Graphics.hpp>

class SpriteSheet {
public:
    SpriteSheet(const sf::Texture &, const sf::IntRect &);
    void setFrame(const int);
    sf::Sprite & getSprite();

private:
    sf::Sprite m_sprite;
    sf::IntRect m_bounds;
};

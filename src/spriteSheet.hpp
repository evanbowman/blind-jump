//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "framework/framework.hpp"
#include <SFML/Graphics.hpp>

template <uint16_t x, uint16_t y, uint16_t w, uint16_t h> class SpriteSheet {
private:
    sf::Sprite sprite;

public:
    SpriteSheet() {}

    explicit SpriteSheet(const sf::Texture & txtr) { setTexture(txtr); }

    sf::Sprite & operator[](const size_t idx) {
        sprite.setTextureRect(sf::IntRect(x + idx * w, y, w, h));
        return sprite;
    }

    const sf::Vector2f & getScale() const { return sprite.getScale(); }

    sf::Sprite * getSpritePtr() { return &sprite; }

    void setColor(const sf::Color color) { sprite.setColor(color); }

    const sf::Sprite & getSprite() const { return sprite; }

    sf::FloatRect getSize() const { return sprite.getLocalBounds(); }

    void setRotation(float degrees) { sprite.setRotation(degrees); }

    void setScale(float xScale, float yScale) {
        sprite.setScale(xScale, yScale);
    }

    void setPosition(float xPos, float yPos) { sprite.setPosition(xPos, yPos); }

    void setPosition(const sf::Vector2f & position) {
        sprite.setPosition(position);
    }

    float getYpos() const { return sprite.getPosition().y; }

    void setTexture(const sf::Texture & texture) { sprite.setTexture(texture); }

    void setOrigin(const float xCenter, const float yCenter) {
        sprite.setOrigin(xCenter, yCenter);
    }
};


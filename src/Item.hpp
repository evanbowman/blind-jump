//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Effect.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

class Item : public Effect {
public:
    enum class Type { Heart, Coin };
    using HBox = framework::HitBox<13, 13, -8, -8>;
    Item(const sf::Texture &, const sf::Texture &, float, float, Type);
    const framework::Sprite & getSprite();
    const HBox & getHitBox() const;
    const framework::Sprite & getGlow();
    void update(const sf::Time &);

protected:
    HBox hitBox;
    framework::Sprite glow;
    SpriteSheet<0, 75, 13, 13> powerupSheet;
};

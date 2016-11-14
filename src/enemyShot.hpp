//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Effect.hpp"
#include "math.hpp"
#include "rng.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

class EnemyShot : public Effect {
public:
    using HBox = framework::HitBox<14, 14, 0, 0>;
    enum { lifetime = 600 };
    EnemyShot(const sf::Texture &, const sf::Texture &, float, float, float);
    void update(const sf::Time &);
    const framework::Sprite & getSprite();
    const HBox & getHitBox() const;
    const framework::Sprite & getGlow() const;

private:
    HBox hitBox;
    SpriteSheet<50, 91, 14, 14> spriteSheet;
    int32_t frameTimer;
    float direction;
    framework::Sprite glowSprite;
};

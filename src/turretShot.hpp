//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Effect.hpp"
#include "rng.hpp"
#include "spriteSheet.hpp"
#include <cmath>

class TurretShot : public Effect {
public:
    using HBox = framework::HitBox<10, 10, -5, -5>;
    const HBox & getHitBox() const;
    enum { lifetime = 600 };
    TurretShot(const sf::Texture &, const sf::Texture &, float, float, float);
    const framework::Sprite & getGlow();
    const framework::Sprite & getSprite();
    void update(const sf::Time &);
    void speedFactor(float);
    int32_t animationTimer;

private:
    SpriteSheet<26, 75, 9, 16> spriteSheet;
    HBox hitBox;
    framework::Sprite glowSprite;
    float direction;
    float scale;
};

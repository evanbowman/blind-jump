//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "spriteSheet.hpp"
#include "Effect.hpp"

class ShotPuff : public Effect {
private:
    mutable SpriteSheet<88, 145, 16, 16> spriteSheet;

public:
    ShotPuff(const sf::Texture &, float, float);
    void update(const sf::Time &);
    const framework::Sprite & getSprite() const;
};

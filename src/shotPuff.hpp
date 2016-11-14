//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Effect.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

class ShotPuff : public Effect {
  private:
    mutable SpriteSheet<88, 145, 16, 16> spriteSheet;

  public:
    ShotPuff(const sf::Texture &, float, float);
    void update(const sf::Time &);
    const framework::Sprite & getSprite() const;
};

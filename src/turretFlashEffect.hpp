//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Effect.hpp"
#include "rng.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>

class TurretFlashEffect : public Effect {
  private:
    mutable SpriteSheet<0, 116, 16, 16> spriteSheet;

  public:
    TurretFlashEffect(const sf::Texture &, float, float);
    void update(const sf::Time &);
    const framework::Sprite & getSprite() const;
};

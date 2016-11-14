//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Effect.hpp"
#include "easingTemplates.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>

class FireExplosion : public Effect {
private:
    mutable SpriteSheet<208, 173, 58, 51> spriteSheet;
    framework::Sprite glow;
    int64_t glowFadeTimer;

public:
    FireExplosion(const sf::Texture &, const sf::Texture &, float, float);
    void update(const sf::Time &);
    const framework::Sprite & getSprite() const;
    const framework::Sprite & getGlow() const;
};

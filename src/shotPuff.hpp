//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Drawable.hpp"
#include "Effect.hpp"
#include "GfxContext.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

namespace effect {
template <typename DrawPolicy>
class ShotPuff : public Drawable<ShotPuff<DrawPolicy>, DrawPolicy>,
                 public Effect {
public:
    static const int drawOffset = 0;
    ShotPuff(const sf::Texture & txtr, float x, float y) : Effect(x, y) {
        spriteSheet.setTexture(txtr);
        spriteSheet.setPosition(position.x, position.y);
    }
    void update(const sf::Time & elapsedTime) {
        timer += elapsedTime.asMilliseconds();
        if (timer > 50) {
            timer -= 50;
            frameIndex += 1;
            if (frameIndex == 4) {
                frameIndex = 3;
                killFlag = true;
            }
        }
    }
    const sf::Sprite & getSprite() const { return spriteSheet[frameIndex]; }

private:
    mutable SpriteSheet<88, 145, 16, 16> spriteSheet;
};
}

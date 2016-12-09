//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Effect.hpp"
#include "rng.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>
#include "Drawable.hpp"

namespace effect {
    template <typename DrawPolicy>
    class TurretFlashEffect : public Drawable<TurretFlashEffect<DrawPolicy>, DrawPolicy>, public Effect {
    public:
        static const int drawOffset = 11;
        TurretFlashEffect(const sf::Texture & txtr, float x, float y)
            : Effect(x, y) {
            spriteSheet.setTexture(txtr);
            bool select = rng::random<2>();
            if (select) {
                spriteSheet.setScale(-1.f, 1.f);
                position.x += 17;
            }
            spriteSheet.setPosition(position.x, position.y);
        }
        void update(const sf::Time & elapsedTime) {
            timer += elapsedTime.asMilliseconds();
            if (timer > 40) {
                timer -= 40;
                frameIndex += 1;
                if (frameIndex > 4) {
                    setKillFlag();
                    frameIndex = 4;
                };
            }
        }
        const sf::Sprite & getSprite() const {
            return spriteSheet[frameIndex];
        }

    private:
        mutable SpriteSheet<0, 116, 16, 16> spriteSheet;
    };
}

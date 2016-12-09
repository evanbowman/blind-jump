//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Effect.hpp"
#include "easingTemplates.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>
#include "GfxContext.hpp"
#include "Drawable.hpp"

namespace effect {
    template <typename DrawPolicy>
    class FireExplosion : public Drawable<FireExplosion<DrawPolicy>, DrawPolicy>, public Effect {
    public:
        static const int drawOffset = 0;
        FireExplosion(const sf::Texture & mainTxtr,
                      const sf::Texture & glowTxtr, float x, float y)
            : Effect(x, y), glowFadeTimer(0) {
            spriteSheet.setTexture(mainTxtr);
            spriteSheet.setOrigin(29, 25);
            glow.setTexture(glowTxtr);
            glow.setColor(sf::Color(240, 240, 240));
            spriteSheet.setPosition(position.x, position.y);
            glow.setPosition(position.x - 225, position.y - 225);
        }
        void update(const sf::Time & elapsedTime) {
            timer += elapsedTime.asMicroseconds();
            glowFadeTimer += elapsedTime.asMicroseconds();
            static const int frameTransitionTime = 70000;
            if (timer > frameTransitionTime) {
                timer -= frameTransitionTime;
                frameIndex++;
                static const int maxFrame = 8;
                if (frameIndex > maxFrame) {
                    frameIndex = maxFrame;
                    killFlag = true;
                }
            }
            uint8_t color =
                Easing::easeOut<1>(glowFadeTimer, static_cast<int64_t>(560000)) * 230;
            glow.setColor(sf::Color(color, color, color, 255));
        }
        const sf::Sprite & getGlow() const { return glow; }
        const sf::Sprite & getSprite() const {
            return spriteSheet[frameIndex];
        }
    private:
        mutable SpriteSheet<208, 173, 58, 51> spriteSheet;
        sf::Sprite glow;
        int64_t glowFadeTimer;
    };
}

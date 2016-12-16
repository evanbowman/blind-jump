//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Drawable.hpp"
#include "Effect.hpp"
#include "GfxContext.hpp"
#include "easingTemplates.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>

namespace effect {
template <typename DrawPolicy>
class SmallExplosion : public Drawable<SmallExplosion<DrawPolicy>, DrawPolicy>,
                       public Effect {
public:
    static const int drawOffset = 0;
    SmallExplosion(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr,
                   float x, float y)
        : Effect(x, y), glowFadeTimer(0) {
        spriteSheet.setTexture(mainTxtr);
        spriteSheet.setOrigin(18, 18);
        glow.setTexture(glowTxtr);
        glow.setColor(sf::Color(220, 220, 220));
        spriteSheet.setPosition(position.x, position.y);
        glow.setPosition(position.x - 225, position.y - 225);
    }
    template <typename Game>
    void update(const sf::Time & elapsedTime, Game *) {
        timer += elapsedTime.asMicroseconds();
        glowFadeTimer += elapsedTime.asMicroseconds();
        if (timer > 65000) {
            timer -= 65000;
            frameIndex++;
            if (frameIndex > 5) {
                frameIndex = 5;
                killFlag = true;
            }
        }
        uint8_t color =
            Easing::easeOut<2>(glowFadeTimer, static_cast<int64_t>(300000)) *
            230;
        glow.setColor(sf::Color(color, color, color, 255));
    }
    const sf::Sprite & getGlow() const { return glow; }
    const sf::Sprite & getSprite() const { return spriteSheet[frameIndex]; }

private:
    mutable SpriteSheet<174, 224, 36, 36> spriteSheet;
    sf::Sprite glow;
    int64_t glowFadeTimer;
};
}

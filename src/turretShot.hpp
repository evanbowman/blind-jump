//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Drawable.hpp"
#include "Effect.hpp"
#include "GfxContext.hpp"
#include "rng.hpp"
#include "spriteSheet.hpp"
#include <cmath>

namespace effect {
template <typename DrawPolicy>
class TurretShot : public Drawable<TurretShot<DrawPolicy>, DrawPolicy>,
                   public Effect {
public:
    static const int drawOffset = 11;
    using HBox = framework::HitBox<10, 10, -5, -5>;
    enum { lifetime = 600 };
    TurretShot(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr,
               float x, float y, float dir)
        : Effect{x, y} {
        spriteSheet.setTexture(mainTxtr);
        glowSprite.setTexture(glowTxtr);
        spriteSheet.setRotation(dir + 270);
        spriteSheet.setOrigin(4, 6);
        glowSprite.setOrigin(22.5, 22.5);
        direction = dir * 3.14 / 180;
        scale = 2.8;
        animationTimer = 0;
    }
    void update(const sf::Time & elapsedTime) {
        position.x += scale * 1.5 * (elapsedTime.asMicroseconds() * 0.00005f) *
                      (cos(direction));
        position.y += scale * 1.5 * (elapsedTime.asMicroseconds() * 0.00005f) *
                      (sin(direction));
        hitBox.setPosition(position);
        spriteSheet.setPosition(position.x, position.y);
        glowSprite.setPosition(position.x, position.y + 18);
        timer += elapsedTime.asMilliseconds();
        if (timer > lifetime) {
            setKillFlag();
        }
        float offset = rng::random<20>();
        glowSprite.setColor(
            sf::Color(230 + offset, 230 + offset, 230 + offset, 255));
        animationTimer += elapsedTime.asMilliseconds();
        if (animationTimer > 50) {
            animationTimer -= 50;
            frameIndex ^= 0x01; // Toggle between the two frames
        }
    }
    const HBox & getHitBox() const { return hitBox; }
    const sf::Sprite & getSprite() const { return spriteSheet[frameIndex]; }
    const sf::Sprite & getGlow() const { return glowSprite; }
    void speedFactor(float factor) { scale = factor; }
    int32_t animationTimer;

private:
    mutable SpriteSheet<26, 75, 9, 16> spriteSheet;
    HBox hitBox;
    sf::Sprite glowSprite;
    float direction;
    float scale;
};
}

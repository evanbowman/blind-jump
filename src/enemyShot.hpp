#pragma once

#include "Drawable.hpp"
#include "Effect.hpp"
#include "GfxContext.hpp"
#include "math.hpp"
#include "rng.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

template <typename DrawPolicy>
class _EnemyShot : public Drawable<_EnemyShot<DrawPolicy>, DrawPolicy>,
                   public Effect {
public:
    static const int drawOffset = 11;
    using HBox = HitBox<14, 14, 0, 0>;
    enum { lifetime = 600 };
    _EnemyShot(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr,
               float x, float y, float dir)
        : Effect(x, y), frameTimer(0) {
        glowSprite.setTexture(glowTxtr);
        glowSprite.setOrigin(22.5, 22.5);
        spriteSheet.setTexture(mainTxtr);
        direction = dir * (3.14 / 180);
    }
    template <typename Game> void update(const sf::Time & elapsedTime, Game *) {
        position.x +=
            4.4 * (elapsedTime.asMicroseconds() * 0.00005f) * (cos(direction));
        position.y +=
            4.4 * (elapsedTime.asMicroseconds() * 0.00005f) * (sin(direction));
        hitBox.setPosition(position);
        glowSprite.setPosition(position.x, position.y + 18);
        timer += elapsedTime.asMilliseconds();
        frameTimer += elapsedTime.asMilliseconds();
        if (frameTimer > 211) {
            frameTimer -= 211;
            if (frameIndex == 0) {
                frameIndex = 1;
            } else {
                frameIndex = 0;
            }
        }
        if (timer > lifetime) {
            setKillFlag();
        }
        float offset = rng::random<20>();
        glowSprite.setColor(
            sf::Color(230 + offset, 230 + offset, 230 + offset, 255));
        spriteSheet.setPosition(position.x, position.y);
    }
    const sf::Sprite & getGlow() const { return glowSprite; }
    const HBox & getHitBox() const { return hitBox; }
    const sf::Sprite & getSprite() const { return spriteSheet[frameIndex]; }

private:
    HBox hitBox;
    mutable SpriteSheet<50, 91, 14, 14> spriteSheet;
    int32_t frameTimer;
    float direction;
    sf::Sprite glowSprite;
};

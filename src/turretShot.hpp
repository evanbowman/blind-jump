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
#include "soundController.hpp"
#include <memory>

namespace effect {
template <typename DrawPolicy>
class TurretShot : public Drawable<TurretShot<DrawPolicy>, DrawPolicy>,
                   public Effect,
                   public std::enable_shared_from_this<TurretShot<DrawPolicy>> {
public:
    static const int drawOffset = 11;
    using HBox = framework::HitBox<10, 10, -5, -5>;
    enum { lifetime = 600 };
    TurretShot(float x, float y, float dir)
        : Effect(x, y), soundsStarted(false) {
        auto res = getgResHandlerPtr();
        spriteSheet.setTexture(res->getTexture(ResHandler::Texture::gameObjects));
        glowSprite.setTexture(res->getTexture(ResHandler::Texture::redglow));
        spriteSheet.setRotation(dir + 270);
        spriteSheet.setOrigin(4, 6);
        glowSprite.setOrigin(22.5, 22.5);
        direction = dir * 3.14 / 180;
        scale = 2.8;
        animationTimer = 0;
    }
    void initSounds(SoundController & sounds) {
        sounds.play(ResHandler::Sound::espark, this->shared_from_this(), 38.f, 20.f, true);
    }
    template <typename Game>
    void update(const sf::Time & elapsedTime, Game * pGame) {
        if (!soundsStarted) {
            initSounds(pGame->getSounds());
            soundsStarted = true;
        }
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
    bool soundsStarted;
    mutable SpriteSheet<26, 75, 9, 16> spriteSheet;
    HBox hitBox;
    sf::Sprite glowSprite;
    float direction;
    float scale;
};
}

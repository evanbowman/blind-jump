//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Drawable.hpp"
#include "Effect.hpp"
#include "GfxContext.hpp"
#include "easingTemplates.hpp"
#include "rng.hpp"
#include "soundController.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>

namespace effect {
template <typename DrawPolicy>
class DasherShot : public Drawable<DasherShot<DrawPolicy>, DrawPolicy>,
                   public Effect,
                   public std::enable_shared_from_this<DasherShot<DrawPolicy>> {
public:
    static const int drawOffset = 11;
    using HBox = framework::HitBox<12, 12, -6, -6>;
    DasherShot(float x, float y, float dir)
        : Effect(x, y), soundsStarted(false) {
        auto res = getgResHandlerPtr();
        spriteSheet.setTexture(
            res->getTexture("textures/gameObjects.png"));
        spriteSheet.setOrigin(6, 6);
        glowSprite.setTexture(res->getTexture("textures/redFloorGlow.png"));
        glowSprite.setOrigin(22.5, 22.5);
        int diff = pow(-1, rng::random<2>() + rng::random<6, -3>());
        direction = (dir + diff) * (3.14 / 180);
        initialVelocity = 5.8f + (0.8f * rng::random<3>());
        timeout = 0;
        driftSel = rng::random<2>();
    }
    void initSounds(SoundController & sounds) {
        // sounds.play(ResHandler::Sound::espark, this->shared_from_this(), 38.f,
        //             20.f, true);
    }
    template <typename Game>
    void update(const sf::Time & elapsedTime, Game * pGame) {
        if (!soundsStarted) {
            initSounds(pGame->getSounds());
            soundsStarted = true;
        }
        float scale = initialVelocity *
                      Easing::easeOut<2>(timeout, static_cast<int64_t>(830000));
        position.x += scale * (elapsedTime.asMicroseconds() * 0.00005f) *
                      (cos(direction));
        position.y += scale * (elapsedTime.asMicroseconds() * 0.00005f) *
                      (sin(direction));
        hitBox.setPosition(position);
        glowSprite.setPosition(position.x, position.y + 18);
        timer += elapsedTime.asMilliseconds();
        timeout += elapsedTime.asMicroseconds();
        // Alternate between frames
        if (timer > 70) {
            frameIndex ^= 0x01;
            timer -= 70;
        }
        if (driftSel) {
            direction += 0.004f * elapsedTime.asMicroseconds() * 0.00005f;
        } else {
            direction -= 0.004f * elapsedTime.asMicroseconds() * 0.00005f;
        }
        if (timeout > 750000) {
            setKillFlag();
        }
        spriteSheet.setPosition(position.x, position.y);
    }
    float direction;
    bool driftSel;
    const sf::Sprite & getSprite() const { return spriteSheet[frameIndex]; }
    const sf::Sprite & getGlow() const { return glowSprite; }
    const DasherShot::HBox & getHitBox() const { return hitBox; }

private:
    mutable SpriteSheet<0, 88, 12, 12> spriteSheet;
    int64_t timeout;
    float initialVelocity;
    HBox hitBox;
    sf::Sprite glowSprite;
    bool soundsStarted;
};
}

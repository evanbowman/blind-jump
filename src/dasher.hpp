//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "effectsController.hpp"
#include "enemy.hpp"
#include "resourceHandler.hpp"
#include "soundController.hpp"

class Player;

class Dasher : public Enemy {
public:
    using HBox = framework::HitBox<20, 32, -6, -4>;
    struct Blur {
        Blur(sf::Sprite *, float, float);
        sf::Sprite * getSprite();
        void update(const sf::Time &);
        bool getKillFlag();
        int32_t timer;
        float xInit;
        float yInit;
        sf::Sprite spr;
        bool killflag;
    };
    enum class State {
        idle,
        shooting,
        dashBegin,
        dashing,
        dashEnd,
        dying,
        dead,
        shootBegin,
        pause
    };
    Dasher(const sf::Texture &, float, float);
    const sf::Sprite & getSprite() const;
    const sf::Sprite & getShadow() const;
    void update(const Player *, SoundController &, const std::vector<wall> &, EffectGroup & ef,
                const sf::Time &);
    std::vector<Dasher::Blur> * getBlurEffects();
    State getState() const;
    const sf::Vector2f & getScale() const;
    const HBox & getHitBox() const;

private:
    HBox hitBox;
    uint8_t shotCount;
    State state;
    mutable SpriteSheet<648, 38, 29, 38> dasherSheet;
    mutable SpriteSheet<80, 0, 47, 38> deathSheet;
    sf::Sprite shadow;
    sf::Vector2f target;
    float hSpeed, vSpeed;
    int32_t timer;
    std::vector<Dasher::Blur> blurEffects;
    void onDeath(EffectGroup &);
    void facePlayer();
};

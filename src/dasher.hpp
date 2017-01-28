#pragma once

#include "effectsController.hpp"
#include "enemy.hpp"
#include "resourceHandler.hpp"
#include "soundController.hpp"

class Game;

class Dasher : public Enemy, public std::enable_shared_from_this<Dasher> {
public:
    using HBox = HitBox<20, 32, -6, -4>;
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
        shootBegin,
        pause
    };
    Dasher(const sf::Texture &, float, float);
    const sf::Sprite & getSprite() const;
    const sf::Sprite & getShadow() const;
    void update(Game * pGame, const std::vector<wall> &, const sf::Time &);
    std::vector<Dasher::Blur> * getBlurEffects();
    State getState() const;
    const sf::Vector2f & getScale() const;
    const HBox & getHitBox() const;

private:
    HBox hitBox;
    uint8_t shotCount;
    State state;
    mutable SpriteSheet<648, 38, 29, 38> dasherSheet;
    sf::Sprite shadow;
    sf::Vector2f target;
    float hSpeed, vSpeed;
    int32_t timer;
    std::vector<Dasher::Blur> blurEffects;
    void facePlayer();
};

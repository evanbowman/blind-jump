#pragma once

#include "effectsController.hpp"
#include "enemy.hpp"
#include "framework/framework.hpp"
#include "resourceHandler.hpp"
#include "spriteSheet.hpp"
#include "turret.hpp"
#include <SFML/Graphics.hpp>
#include <stdio.h>

class Game;

class Turret : public Enemy {
private:
    enum class State { closed, opening, shoot1, shoot2, shoot3, rest, closing };
    State state;
    using HBox = HitBox<16, 32>;
    HBox hitBox;
    int8_t frameIndex;
    SpriteSheet<0, 0, 16, 32> turretSheet;
    SpriteSheet<0, 32, 16, 26> shadowSheet;
    bool active;
    int64_t timer;
    float hp;
    char colorTimer;
    bool isColored;
    float colorAmount;

public:
    Turret(const sf::Texture &, float, float);
    const HBox & getHitBox() const;
    void setPosition(float, float);
    const sf::Sprite & getShadow();
    const sf::Sprite & getSprite();
    sf::Vector2f target;
    void update(const sf::Time &, Game *);
    bool colored();
    float getColorAmount();
};

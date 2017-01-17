#pragma once

#include "aStar.hpp"
#include "effectsController.hpp"
#include "enemy.hpp"
#include "spriteSheet.hpp"

class tileController;

class Game;

class Critter : public Enemy {
public:
    using HBox = HitBox<12, 12, 4, -3>;
    Critter(const sf::Texture &, uint8_t map[61][61], float, float);
    void update(Game *, const sf::Time &, tileController & tiles);
    const sf::Sprite & getSprite() const;
    const sf::Sprite & getShadow() const;
    void activate();
    void deActivate();
    bool isActive();
    void updatePlayerDead();
    const HBox & getHitBox() const;

private:
    float xInit, yInit;
    void onDeath(EffectGroup &);
    float currentDir;
    mutable SpriteSheet<0, 57, 18, 18> spriteSheet;
    std::vector<aStrCoordinate> path;
    aStrCoordinate previous;
    sf::Sprite shadow;
    HBox hitBox;
    bool awake;
    bool active;
    int recalc;
    uint8_t (*map)[61]; //*** I know this is a nasty solution, perhaps there's a
                        // better way to not store it locally...
};

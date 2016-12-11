//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Drawable.hpp"
#include "Drawable.hpp"
#include "GfxContext.hpp"
#include "inputController.hpp"
#include "powerup.hpp"
#include "rng.hpp"
#include "spriteSheet.hpp"

namespace detail {
template <typename DrawPolicy>
class TreasureChest : public Drawable<TreasureChest<DrawPolicy>, DrawPolicy>,
                      public framework::Object {
public:
    static const int drawOffset = -16;
    enum class State { closed, opening, ready, complete };
    TreasureChest(float _xInit, float _yInit, const sf::Texture & mainTxtr,
                  Powerup _powerup)
        : Object(_xInit + rng::random<4, -2>(), _yInit), state(State::closed),
          powerup(_powerup), animationTimer(0), frameIndex(0),
          chestSheet(mainTxtr) {
        chestShadow.setTexture(mainTxtr);
        chestShadow.setTextureRect(sf::IntRect(18, 107, 16, 8));
        chestSheet.setPosition(position.x, position.y - 16);
        chestShadow.setPosition(position.x, position.y + 12);
    }
    const sf::Sprite & getShadow() const { return chestShadow; }
    const sf::Sprite & getSprite() const { return chestSheet[frameIndex]; }
    template <typename Game>
    void update(const sf::Time & elapsedTime, Game * pGame) {
        switch (state) {
        case State::opening:
            animationTimer += elapsedTime.asMicroseconds();
            if (animationTimer > 50000) {
                animationTimer -= 50000;
                frameIndex++;
                if (frameIndex > 5) {
                    frameIndex = 4;
                    state = State::ready;
                }
            }
            break;

        case State::ready:
            // TODO: play reward sound
            pGame->getUI().setPowerup(powerup);
            state = State::complete;
            break;

        default:
            break;
        }
    }
    State getState() const { return state; }
    void setState(const State _state) { state = _state; }
    Powerup getPowerup() const { return powerup; }

private:
    State state;
    Powerup powerup;
    int64_t animationTimer;
    uint8_t frameIndex;
    mutable SpriteSheet<656, 76, 16, 30> chestSheet;
    mutable sf::Sprite chestShadow;
};
}

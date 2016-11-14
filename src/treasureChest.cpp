//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "treasureChest.hpp"
#include <cmath>

TreasureChest::TreasureChest(float _xInit, float _yInit,
                             const sf::Texture & mainTxtr, Powerup _powerup)
    : Detail(_xInit + rng::random<4, -2>(), _yInit), state(State::closed),
      powerup(_powerup), animationTimer(0), frameIndex(0),
      chestSheet(mainTxtr) {
    chestShadow.setTexture(mainTxtr);
    chestShadow.setTextureRect(sf::IntRect(18, 107, 16, 8));
    chestSheet.setPosition(position.x, position.y - 16);
    chestShadow.setPosition(position.x, position.y + 12);
}

Powerup TreasureChest::getPowerup() const { return powerup; }

const framework::Sprite & TreasureChest::getShadow() const {
    return chestShadow;
}

const framework::Sprite & TreasureChest::getSprite() const {
    return chestSheet[frameIndex];
}

void TreasureChest::update(const sf::Time & elapsedTime) {
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

    default:
        break;
    }
}

TreasureChest::State TreasureChest::getState() const { return state; }

void TreasureChest::setState(const TreasureChest::State _state) {
    state = _state;
}

//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "detailParent.hpp"
#include "inputController.hpp"
#include "spriteSheet.hpp"
#include "rng.hpp"
#include "powerup.hpp"

class TreasureChest : public Detail {
public:
    enum class State {
        closed, opening, ready, complete
    };
    TreasureChest(float, float, const sf::Texture &, Powerup);
    const framework::Sprite & getShadow() const;
    const framework::Sprite & getSprite() const;
    void update(const sf::Time &);
    State getState() const;
    void setState(const State);
    Powerup getPowerup() const;
    
private:
    State state;
    Powerup powerup;
    int64_t animationTimer;
    uint8_t frameIndex;
    mutable SpriteSheet<656, 76, 16, 30> chestSheet;
    mutable framework::Sprite chestShadow;
};

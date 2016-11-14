//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "detailParent.hpp"
#include "effectsController.hpp"
#include "spriteSheet.hpp"

class ScreenShakeController;

class IntroDoor : public Detail {
private:
    enum class State { dormant, opening, opened };
    mutable SpriteSheet<0, 0, 200, 95> doorSheet;
    uint8_t frameIndex;
    // int32_t timer;
    // State state;

public:
    void update(const sf::Time &);
    IntroDoor(float, float, const sf::Texture &);
    const sf::Sprite & getSprite() const;
};

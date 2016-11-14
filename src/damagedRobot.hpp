//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "detailParent.hpp"
#include "rng.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>

class DamagedRobot : public Detail {
public:
    DamagedRobot(float, float, const sf::Texture &);
    void update(const sf::Time &);
    const framework::Sprite & getSprite() const;

private:
    mutable SpriteSheet<88, 102, 40, 43> robotSheet;
};

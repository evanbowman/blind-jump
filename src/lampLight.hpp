//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "detailParent.hpp"

class LampLight : public Detail {
public:
    LampLight(float, float, const sf::Texture &, const sf::Texture &);
    const framework::Sprite & getSprite() const;
    const framework::Sprite & getGlow() const;
    void update(const sf::Time &);

private:
    framework::Sprite lampSprite;
    framework::Sprite glowSprite;
};

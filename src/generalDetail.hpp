//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "detailParent.hpp"

class Game;

class GeneralDetail : public Detail {
public:
    GeneralDetail(float, float, sf::Sprite &);
    const sf::Sprite & getSprite() const;
    void update(const sf::Time & elapsedTime, Game *);

private:
    sf::Sprite spr;
};

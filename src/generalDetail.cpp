//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "generalDetail.hpp"

GeneralDetail::GeneralDetail(float _xInit, float _yInit, sf::Sprite & _spr)
    : Detail{_xInit, _yInit} {
    spr = _spr;
    spr.setPosition(position.x, position.y);
}

void GeneralDetail::update(const sf::Time &) {
    // ...
}

const sf::Sprite & GeneralDetail::getSprite() const { return spr; }

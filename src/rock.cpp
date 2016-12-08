//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "rock.hpp"

Rock::Rock(float _xPos, float _yPos, const sf::Texture & inpTxtr)
    : Detail{_xPos, _yPos} {
    rockSheet.setTexture(inpTxtr);
    if (rng::random<2>()) {
        rockSheet.setScale(-1, 1);
        position.x += 32;
    }
    rockSheet[rng::random<4>()];
    rockSheet.setPosition(position.x, position.y);
}

void Rock::update(const sf::Time &, Game *) {
    // nil
}

const sf::Sprite & Rock::getSprite() const { return rockSheet.getSprite(); }

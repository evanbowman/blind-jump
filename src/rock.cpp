//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "rock.hpp"

Rock::Rock(float _xPos, float _yPos, const sf::Texture & inpTxtr)
	: Detail{_xPos, _yPos}
{
	rockSheet.setTexture(inpTxtr);
    if (std::abs(static_cast<int>(global::RNG())) % 2) {
		rockSheet.setScale(-1, 1);
	    position.x += 32;
	}
	rockSheet[std::abs(static_cast<int>(global::RNG())) % 4];
	rockSheet.setPosition(position.x, position.y);
}

void Rock::update(const sf::Time &) {
	// nil
}

const sf::Sprite & Rock::getSprite() const {
	return rockSheet.getSprite();
}

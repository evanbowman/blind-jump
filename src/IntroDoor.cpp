//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "IntroDoor.hpp"
#include <cmath>

IntroDoor::IntroDoor(float _xInit, float _yInit, const sf::Texture & inpTxtr)
	: Detail{_xInit, _yInit},
	  doorSheet{inpTxtr},
	  frameIndex{3}/*,
	  timer{0},
	  state{State::dormant}*/
{
	doorSheet.setPosition(position.x, position.y);
}
 
const framework::Sprite & IntroDoor::getSprite() const {
	return doorSheet[frameIndex];
}

void IntroDoor::update(const sf::Time &) {
	// ...
}

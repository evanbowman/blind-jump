//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "damagedRobot.hpp"

DamagedRobot::DamagedRobot(float _xInit, float _yInit, const sf::Texture & inpTxtr)
	: Detail{_xInit, _yInit}, robotSheet{inpTxtr}
{
	robotSheet[std::abs(static_cast<int>(global::RNG())) % 2]; // Randomly pick one of the textures...
	robotSheet.setPosition(position.x, position.y);
}

void DamagedRobot::update(const sf::Time &) {
	// ...
}

const sf::Sprite & DamagedRobot::getSprite() const {
	return robotSheet.getSprite();
}

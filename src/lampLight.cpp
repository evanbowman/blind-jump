//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "lampLight.hpp"

LampLight::LampLight(float _xInit, float _yInit, const sf::Texture & txtr, const sf::Texture & glwTxtr)
	: Detail{_xInit, _yInit}
{
	glowSprite.setTexture(glwTxtr);
	lampSprite.setTexture(txtr);
	lampSprite.setTextureRect(sf::IntRect(40, 91, 10, 9));
	lampSprite.setPosition(position.x, position.y + 8);
	glowSprite.setPosition(position.x - 250 + 16, position.y - 250 + 16);
}

void LampLight::update(const sf::Time &) {
	// ...
}

const framework::Sprite & LampLight::getSprite() const {
	return lampSprite;
}

const framework::Sprite & LampLight::getGlow() const {
	return glowSprite;
}

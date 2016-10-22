//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "Item.hpp"

const static float PI{3.1415926535};

Item::Item(const sf::Texture & bodyTxtr, const sf::Texture & glowTxtr, float xInit, float yInit, Type id) :
	Effect(xInit, yInit)
{
	glow.setTexture(glowTxtr);
	glow.setOrigin(22.5, 22.5);
	powerupSheet.setTexture(bodyTxtr);
	// Square brace overloads provide access, but in doing so also set the working frame
	powerupSheet[static_cast<int>(id)];
	powerupSheet.setOrigin(7, 7);
	timer = 0;
	killFlag = false;
	hitBox.setPosition(position);
}

void Item::update(const sf::Time & elapsedTime) {
	timer += elapsedTime.asMilliseconds();
	const float offset = (3 * sinf(2 * PI * 0.001 * timer + 180));
	// Make the sprite float up and down
	powerupSheet.setPosition(position.x, position.y + offset);
}

const framework::Sprite & Item::getSprite() {
	return powerupSheet.getSprite();
}

const framework::Sprite & Item::getGlow() {
	glow.setPosition(position.x, position.y + 10);
	return glow;
}

const Item::HBox & Item::getHitBox() const {
	return hitBox;
}

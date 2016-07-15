//
//  Hearts.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 4/2/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "Powerup.hpp"

const static float PI{3.1415926535};

Powerup::Powerup(const sf::Texture & bodyTxtr, const sf::Texture & glowTxtr, float xInit, float yInit, Type id) :
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
}

void Powerup::update(float xOffset, float yOffset, sf::Time & elapsedTime) {
	setPosition(xInit + xOffset, yInit + yOffset);
	hitBox.setPosition(position);
	timer += elapsedTime.asMilliseconds();
}

const sf::Sprite & Powerup::getSprite() {
	const float offset = (3 * sinf(2 * PI * 0.001 * timer + 180));
	// Make the sprite float up and down
	powerupSheet.setPosition(position.x, position.y + offset);
	return powerupSheet.getSprite();
}

sf::Sprite * Powerup::getGlow() {
	glow.setPosition(position.x, position.y + 10);
	return &glow;
}

const Powerup::HBox & Powerup::getHitBox() const {
	return hitBox;
}

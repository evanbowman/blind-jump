//
//  turretShot.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/26/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "turretShot.hpp"

TurretShot::TurretShot(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr, float x, float y, float dir) :
	Effect{x, y}
{
	spriteSheet.setTexture(mainTxtr);
	glowSprite.setTexture(glowTxtr);
	int diff = pow(-1,rand() % 2) + rand() % 6 - 3;
	spriteSheet.setRotation(dir + diff);
	spriteSheet.setOrigin(4, 6);
	glowSprite.setOrigin(22.5, 22.5);
	direction = (dir - 270 + diff) * (3.14 / 180);
	scale = 2.8;
	animationTimer = 0;
}

void TurretShot::update(float xOffset, float yOffset, sf::Time & elapsedTime) {
	xInit += scale * 1.5 * (elapsedTime.asMilliseconds() / 17.6) * (cos(direction));
	yInit += scale * 1.5 * (elapsedTime.asMilliseconds() / 17.6) * (sin(direction));
	setPosition(xInit + xOffset, yInit + yOffset);
	hitBox.setPosition(position.x, position.y);
	spriteSheet.setPosition(position.x, position.y);
	glowSprite.setPosition(position.x, position.y + 18);
	timer += elapsedTime.asMilliseconds();
	if (timer > 600) {
	    setKillFlag();
	}
	float offset = rand() % 20;
	glowSprite.setColor(sf::Color(230 + offset, 230 + offset, 230 + offset, 255));
	animationTimer += elapsedTime.asMilliseconds();
	if (animationTimer > 50) {
		animationTimer -= 50;
		frameIndex ^= 0x01; // Toggle between the two frames
	}
}

const TurretShot::HBox & TurretShot::getHitBox() const {
	return hitBox;
}

const sf::Sprite & TurretShot::getSprite() {
	return spriteSheet[frameIndex];
}

sf::Sprite * TurretShot::getGlow() {
	return &glowSprite;
}

void TurretShot::speedFactor(float factor) {
	scale = factor;
}

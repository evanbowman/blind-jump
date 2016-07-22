//
//  enemyShot.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/2/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "enemyShot.hpp"

EnemyShot::EnemyShot(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr, float x, float y, float dir) :
	Effect{x, y},
	frameTimer{0}
{
	glowSprite.setTexture(glowTxtr);
	glowSprite.setOrigin(22.5, 22.5);
	spriteSheet.setTexture(mainTxtr);
	direction = (dir - 270) * (3.14 / 180);
}

void EnemyShot::update(float xOffset, float yOffset, sf::Time & elapsedTime) {
	xInit += 4.4 * (elapsedTime.asMilliseconds() / 17.6) * (cos(direction));
	yInit += 4.4 * (elapsedTime.asMilliseconds() / 17.6) * (sin(direction));
	setPosition(xInit + xOffset, yInit + yOffset);

	hitBox.setPosition(position);
	glowSprite.setPosition(position.x, position.y + 18);
	
	timer += elapsedTime.asMilliseconds();
	frameTimer += elapsedTime.asMilliseconds();
	
	if (frameTimer > 211) {
		frameTimer -= 211;
		if (frameIndex == 0) {
			frameIndex = 1;
		} else {
			frameIndex = 0;
		}
	}
	
	if (timer > 600) {
		setKillFlag();
	}
	
	float offset = std::abs(static_cast<int>(globalRNG())) % 20;
	glowSprite.setColor(sf::Color(230 + offset, 230 + offset, 230 + offset, 255));
	spriteSheet.setPosition(position.x, position.y);
}

sf::Sprite * EnemyShot::getGlow() {
	return &glowSprite;
}

const EnemyShot::HBox & EnemyShot::getHitBox() const {
	return hitBox;
}

const Sprite & EnemyShot::getSprite() {
	return spriteSheet[frameIndex];
}

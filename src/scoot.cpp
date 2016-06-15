//
//  scoot.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/21/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "scoot.hpp"
#include <cmath>
#include "angleFunction.hpp"

#define PI 3.14159265

Scoot::Scoot(sf::Texture * pMainTxtr, sf::Texture * pShadowTxtr, float _xInit, float _yInit, float _playerPosX, float _playerPosY)
	: Enemy{_xInit, _yInit, _playerPosX, _playerPosY},
	  spriteSheet{pMainTxtr},
	  speedScale{0.5f},
	  state{State::drift1},
	  timer{rand() % 250}
{
	spriteSheet.setOrigin(6, 6);
	shadow.setTexture(*pShadowTxtr);
	float dir = rand() % 359;
	hSpeed = cos(dir) * 0.5;
	vSpeed = sin(dir) * 0.5;
	health = 2;
}

void Scoot::changeDir(float dir) {
	hSpeed = std::cos(dir);
	vSpeed = std::sin(dir);	
}

void Scoot::update(float xOffset, float yOffset, const std::vector<wall> & w, effectsController & effects, const sf::Time & elapsedTime) {
	Enemy::update(xOffset, yOffset, w, effects, elapsedTime);
	Enemy::checkShotCollision(effects, 8.f);
	Enemy::updateColor(elapsedTime);
	spriteSheet.setPosition(xPos, yPos);
	shadow.setPosition(xPos - 6, yPos + 2);
    
	// Enemies behave as state machines
	switch(state) {
	case State::drift1:
		timer += elapsedTime.asMilliseconds();
		if (timer > 1400) {
			timer -= 1400;
			state = State::drift2;
			changeDir(static_cast<float>(rand() % 359));
			state = State::drift2;
		}
		break;

	case State::drift2:
		timer += elapsedTime.asMilliseconds();
		if (timer > 1400) {
			timer -= 1400;
			state = State::shoot;
		}
		break;
		
	case State::shoot:
		effects.addTurretFlash(xInit - 8, yInit - 12);
		effects.addScootShot(xInit - 8, yInit - 12, angleFunction(xPos -8, yPos - 8, playerPosX, playerPosY), playerPosX, playerPosY);
		effects.addScootShot(xInit - 8, yInit - 12, angleFunction(xPos -8, yPos - 8, playerPosX, playerPosY) + 28, playerPosX, playerPosY);
		effects.addScootShot(xInit - 8, yInit - 12, angleFunction(xPos -8, yPos - 8, playerPosX, playerPosY) - 28, playerPosX, playerPosY);
		state = State::recoil;
		changeDir(angleFunction(xPos -8, yPos - 8, playerPosX, playerPosY));
		break;

	case State::recoil:
		timer += elapsedTime.asMilliseconds();
		if (timer > 400) {
			changeDir(static_cast<float>(rand() % 359));
			state = State::drift1;
		}
		break;
	}

	if (Enemy::checkWallCollision(w, 8.f, xPos - 8, yPos - 8)) {
		hSpeed *= -1;
		vSpeed *= -1;
	}
	
	xInit += (elapsedTime.asMilliseconds() / 17.6) * hSpeed * speedScale;
	yInit += (elapsedTime.asMilliseconds() / 17.6) * vSpeed * speedScale;
	
	// Update the frameIndex based on delta time
	frameTimer += elapsedTime.asMilliseconds();
	if (frameTimer > 87) {
		frameTimer -= 87;
		if (frameIndex == 0) {
			frameIndex = 1;
		}
		else {
			frameIndex = 0;
		}
	}
}

const sf::Sprite & Scoot::getSprite() const {
	return spriteSheet[frameIndex];
}

const sf::Sprite & Scoot::getShadow() const {
	return shadow;
}

void Scoot::onDeath(effectsController & effects) {
	int select{rand() % 5};
	if (select == 0) {
		effects.addHearts(xInit, yInit);
	} else {
		effects.addCoins(xInit, yInit);
	}
	effects.addFireExplosion(xInit, yInit - 2);
	return;
}

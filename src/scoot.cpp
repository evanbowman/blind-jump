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
	  speedScale{1.f},
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

void Scoot::update(float xOffset, float yOffset, const std::vector<wall> & w, effectsController & ef, const sf::Time & elapsedTime) {
	// Update position information
	Enemy::update(xOffset, yOffset);	
	spriteSheet.setPosition(xPos, yPos);
	shadow.setPosition(xPos, yPos);
	float dir;
	
	// Enemies behave as state machines
	switch(state) {
	case State::drift1:
		timer += elapsedTime.asMilliseconds();
		if (timer > 1400) {
			timer -= 1400;
			state = State::changeDir1;
		}
		break;

	case State::changeDir1:
		dir = static_cast<float>(rand() % 359);
		hSpeed = std::cos(dir) * 0.5f;
		vSpeed = std::sin(dir) * 0.5f;
		state = State::drift2;
		break;

	case State::drift2:
		timer += elapsedTime.asMilliseconds();
		if (timer > 1400) {
			timer -= 1400;
			state = State::shoot;
		}
		break;
		
	case State::shoot:
		ef.addTurretFlash(xInit - 8, yInit - 12);
		ef.addScootShot(xInit - 8, yInit - 12, angleFunction(xPos -8, yPos - 8, playerPosX, playerPosY), playerPosX, playerPosY);
		ef.addScootShot(xInit - 8, yInit - 12, angleFunction(xPos -8, yPos - 8, playerPosX, playerPosY) + 28, playerPosX, playerPosY);
		ef.addScootShot(xInit - 8, yInit - 12, angleFunction(xPos -8, yPos - 8, playerPosX, playerPosY) - 28, playerPosX, playerPosY);
		state = State::recoil;
		break;

	case State::recoil:
		state = State::changeDir2;
		break;

	case State::changeDir2:
		dir = static_cast<float>(rand() % 359);
		hSpeed = std::cos(dir) * 0.5f;
		vSpeed = std::sin(dir) * 0.5f;
		state = State::drift1;
		break;
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

// Base class internally calls this when health hits zero, overridden for custom behavior
const sf::Sprite & Scoot::getShadow() const {
	return shadow;
}

void Scoot::onDeath(effectsController & effects) {
	return;
}

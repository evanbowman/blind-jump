//
//  dasher.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/11/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "dasher.hpp"
#include <cmath>
#include "angleFunction.hpp"

Dasher::Blur::Blur(sf::Sprite * spr, float xInit, float yInit) {
	this->spr = *spr;
	this->xInit = xInit;
	this->yInit = yInit;
	killflag = false;
	timer = 0;
	sf::Color c = this->spr.getColor();
	c.a -= 120;
	c.r -= 30;
	c.g -= 30;
	c.b -= 10;
	this->spr.setColor(c);
}

sf::Sprite * Dasher::Blur::getSprite() {
	return &spr;
}

void Dasher::Blur::update(const sf::Time & elapsedTime, float xOffset, float yOffset) {
	timer += elapsedTime.asMilliseconds();
	spr.setPosition(xInit + xOffset, yInit + yOffset);
	if (timer > 18) {
		timer = 0;
		sf::Color c = spr.getColor();
		if (c.a > 30) {
			c.a -= 30;
			spr.setColor(c);
		} else
			killflag = true;
	}
}

bool Dasher::Blur::getKillFlag() {
	return killflag;
}

Dasher::Dasher(const sf::Texture & mainTxtr, const sf::Texture & deathTxtr, const sf::Texture & shadowTxtr, float _xInit, float _yInit, float _ppx, float _ppy)
	: Enemy{_xInit, _yInit, _ppx, _ppy},
	  shotCount{0},
	  state{State::idle},
	  dasherSheet{mainTxtr},
	  deathSheet{deathTxtr},
	  hSpeed{0.f},
	  vSpeed{0.f},
	  timer{0}
{
	dasherSheet.setOrigin(14, 8);
	deathSheet.setOrigin(14, 8);
	shadow.setTexture(shadowTxtr);
	health = 5;
}

const sf::Sprite & Dasher::getSprite() const {
	switch(state) {
	case State::dying:
		return deathSheet[frameIndex];
			
	case State::dead:
		return deathSheet[14];

	default:
		return dasherSheet[frameIndex];
	}
}

const sf::Sprite & Dasher::getShadow() const {
	return shadow;
}

void Dasher::facePlayer() {
	if (xPos > playerPosX)
		dasherSheet.setScale(1, 1);
	else
		dasherSheet.setScale(-1, 1);
}

void Dasher::update(float xOffset, float yOffset, const std::vector<wall> & walls, effectsController & effects, const sf::Time & elapsedTime) {
	Enemy::update(xOffset, yOffset, walls, effects, elapsedTime);
	if (health > 0)
		Enemy::checkShotCollision(effects, 12.f);
	Enemy::updateColor(elapsedTime);

	dasherSheet.setPosition(xPos + 4, yPos);
	deathSheet.setPosition(xPos + 4, yPos);
	shadow.setPosition(xPos - 4, yPos + 22);

	timer += elapsedTime.asMilliseconds();
	
	switch(state) {
	case State::idle:
		if (timer >= 200) {
			timer -= 200;
			const int select = rand() % 2;
			if (select) {
				state = State::dashBegin;
				frameIndex = 1;
			} else {
				state = State::shootBegin;
				frameIndex = 3;
			}
		}
		break;

	case State::pause:
		if (timer >= 200) {
			timer -= 200;
			state = State::dashBegin;
			frameIndex = 1;
		}
		break;

	case State::shooting:
		facePlayer();
		frameTimer += elapsedTime.asMilliseconds();
		if (frameTimer > 80 && shotCount < 3) {
			frameTimer -= 80;
			shotCount++;
			if (xPos > playerPosX) {
				effects.addDasherShot(xInit - 12, yInit - 12, angleFunction(xPos + 18, yPos, playerPosX, playerPosY));
				effects.addTurretFlash(xInit - 12, yInit - 12);
			}
			
			else {
				effects.addDasherShot(xInit + 4, yInit - 12, angleFunction(xPos + 18, yPos, playerPosX, playerPosY));
				effects.addTurretFlash(xInit + 4, yInit - 12);
			}
		}

		if (timer > 300) {
			timer -= 300;
			shotCount = 0;
			state = State::pause;
		}
		break;

	case State::shootBegin:
		facePlayer();
		if (timer > 80) {
			timer -= 80;
			frameTimer = 0;
			state = State::shooting;
			frameIndex = 4;
		}
		break;

	case State::dashBegin:
    begin:
		facePlayer();
		if (timer > 352) {
			timer -= 352;
			state = State::dashing;
			frameIndex = 2;
			uint8_t tries{0};
			float dir{static_cast<float>(rand() % 359)};
			do {
				tries++;
				if (tries > 254) {
					state = State::shootBegin;
					frameIndex = 3;
				    goto begin;
				}
				dir += 12;
			} while (wallInPath(walls, dir, xPos, yPos));
			hSpeed = 5 * cos(dir);
			vSpeed = 5 * sin(dir);
			if (hSpeed > 0) {
				dasherSheet.setScale(-1, 1);
				deathSheet.setScale(-1, 1);
			} else {
				dasherSheet.setScale(1, 1);
				dasherSheet.setScale(1, 1);
			}
		}
		break;

	case State::dashing:
		frameTimer += elapsedTime.asMilliseconds();
		if (frameTimer > 40) {
			frameTimer = 0;
			blurEffects.emplace_back(dasherSheet.getSpritePtr(), xInit, yInit);
		}
		if (timer > 250) {
			timer -= 250;
			state = State::dashEnd;
			frameIndex = 1;
			hSpeed = 0.f;
			vSpeed = 0.f;
		}
		
		if (Enemy::checkWallCollision(walls, 48, xPos, yPos)) {
			hSpeed *= -1.f;
			vSpeed *= -1.f;
		}
		break;

	case State::dashEnd:
		if (timer > 150) {
			blurEffects.clear();
			timer -= 150;
			state = State::idle;
			frameIndex = 0;
		}
		break;

	case State::dying:
		frameTimer += elapsedTime.asMilliseconds();
		if (frameTimer > 53) {
			frameTimer -= 53;
			frameIndex++;
			if (frameIndex > 14)
				state = State::dead;
		}
		break;

	case State::dead:
		break;
	}

	if (!blurEffects.empty()) {
		for (auto it = blurEffects.begin(); it != blurEffects.end();) {
			if (it->getKillFlag())
				it = blurEffects.erase(it);
			else {
				it->update(elapsedTime, xOffset, yOffset);
				++it;
			}
		}
	}
	
	xInit += hSpeed * (elapsedTime.asMilliseconds() / 17.6f);
	yInit += vSpeed * (elapsedTime.asMilliseconds() / 17.6f);
}

void Dasher::onDeath(effectsController & effects) {
	state = State::dying;
	hSpeed = 0;
	vSpeed = 0;
	frameIndex = 0;
	unsigned long int temp = rand() % 4;
	if (temp == 0)
		effects.addHearts(xInit, yInit);
	else
		effects.addCoins(xInit, yInit);
	effects.addSmallExplosion(xInit, yInit);
	blurEffects.clear();
}

Dasher::State Dasher::getState() const {
	return state;
}

std::vector<Dasher::Blur> * Dasher::getBlurEffects() {
	return &blurEffects;
}

const sf::Vector2f & Dasher::getScale() const {
	return deathSheet.getScale();
}

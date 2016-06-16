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

DasherBlur::DasherBlur(sf::Sprite* spr, float xInit, float yInit) {
	this->spr = *spr;
	this->xInit = xInit;
	this->yInit = yInit;
	killflag = false;
	sf::Color c = this->spr.getColor();
	c.a -= 90;
	c.r -= 30;
	c.g -= 30;
	c.b -= 10;
	this->spr.setColor(c);
}

sf::Sprite* DasherBlur::getSprite() {
	sf::Color c = spr.getColor();
	if (c.a > 20) {
		c.a -= 15;
		spr.setColor(c);
	}
	else {
		killflag = true;
	}
	return &spr;
}

bool DasherBlur::getKillFlag() {
	return killflag;
}

Dasher::Dasher(sf::Texture * pMain, sf::Texture * pDeath, sf::Texture * pShadow, float _xInit, float _yInit, float _ppx, float _ppy)
	: Enemy{_xInit, _yInit, _ppx, _ppy},
	  state{State::idle},
	  dasherSheet{pMain},
	  deathSheet{pDeath},
	  hSpeed{0.f},
	  vSpeed{0.f},
	  timer{0}
{
	dasherSheet.setOrigin(14, 8);
	deathSheet.setOrigin(14, 8);
	shadow.setTexture(*pShadow);
	health = 5;
}

const sf::Sprite & Dasher::getSprite() const {
	switch(state) {
	case State::dying:
		return deathSheet[frameIndex];
			
	case State::dead:
		return deathSheet[frameIndex];

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
	Enemy::checkShotCollision(effects, 12.f);
	Enemy::updateColor(elapsedTime);

	dasherSheet.setPosition(xPos + 4, yPos);
	deathSheet.setPosition(xPos + 4, yPos);
	shadow.setPosition(xPos + 4, yPos + 2);

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
		if (frameTimer > 80 && timer < 240) {
			frameTimer -= 80;
			if (xPos > playerPosX) {
				effects.addDasherShot(xInit - 12, yInit - 12, angleFunction(xPos + 18, yPos, playerPosX, playerPosY));
				effects.addTurretFlash(xInit - 12, yInit - 12);
			}
			
			else {
				effects.addDasherShot(xInit + 4, yInit - 12, angleFunction(xPos + 18, yPos, playerPosX, playerPosY));
				effects.addTurretFlash(xInit + 4, yInit - 12);
			}
		}

		if (timer > 280) {
			timer -= 280;
			state = State::pause;
		}
		break;

	case State::shootBegin:
		facePlayer();
		if (timer > 80) {
			timer -= 80;
			state = State::shooting;
			frameIndex = 4;
		}
		break;

	case State::dashBegin:
		facePlayer();
		if (timer > 352) {
			timer -= 352;
			state = State::dashing;
			frameIndex = 2;
			float dir{static_cast<float>(rand() % 359)};
			do {
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
		if (timer > 300) {
			timer -= 300;
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
			timer -= 150;
			state = State::idle;
			frameIndex = 0;
		}
		break;

	case State::dying:
		break;

	case State::dead:
		break;
	}

	xInit += hSpeed * (elapsedTime.asMilliseconds() / 17.6f);
	yInit += vSpeed * (elapsedTime.asMilliseconds() / 17.6f);
}

void Dasher::onDeath(effectsController & effects) {
	state = State::dying;
}

Dasher::State Dasher::getState() const {
	return state;
}

/*
void Dasher::update(float xOffset, float yOffset, std::vector<wall> walls, effectsController& ef, sf::Time & elapsedTime) {
	
	for (int i = 0; i < 21; i++) {
		sprs[i].setPosition(xPos + 4, yPos);
	}
	sprs[3].setPosition(xPos + 4, yPos + 2);
	
	if (!deathSeq) {
		if (!isDashing) {
			// Flip the sprite to face the player
			if (xPos > playerPosX) {
				sf::Vector2f scaleVec(1, 1);
				for (int i = 0; i < 21; i++) {
					sprs[i].setScale(scaleVec);
				}
			}
			
			else {
				sf::Vector2f scaleVec(-1, 1);
				for (int i = 0; i < 21; i++) {
					sprs[i].setScale(scaleVec);
				}
			}

			if (--dashCnt == 0) {
				dashCnt = 29;
				isDashing = true;
				frameIndex = 2;
				
				// Pick a random direction to move in, with 50% chance of moving toward the player
				float dir;
				
				if (std::abs(xPos - playerPosX) > 80 && std::abs(yPos - playerPosY) > 80) {
					dir = atan((yPos - playerPosY) / (xPos - playerPosX));
					if (!wallInPath(walls, dir, xPos, yPos)) {
						hspeed = cos(dir) * 5;
						vspeed = sin(dir) * 5;
						if (xPos > playerPosX) {
							hspeed = hspeed * -1;
							vspeed = vspeed * -1;
						}
					}
					
					else {
						dir = rand() % 359;
						do {
							dir += 12;
						} while (wallInPath(walls, dir, xPos, yPos));
						
						hspeed = cos(dir) * 5;
						vspeed = sin(dir) * 5;
					}
				}
				
				else {
					dir = rand() % 359;
					do {
						dir += 12;
					} while (wallInPath(walls, dir, xPos, yPos));
					
					hspeed = cos(dir) * 5;
					vspeed = sin(dir) * 5;
				}
			}
			
			// These next lines are for the purpose of animating the character
			if (dashCnt < 20 && dashCnt > 0) {
				frameIndex = 1;
			}
			
			if (dashCnt == 148) {
				if (rand() % 2) {
					dashCnt = 10;
				}
			}
			
			if (dashCnt == 146) {
				frameIndex = 4;
			}
			
			else if (dashCnt == 145) {
				frameIndex = 5;
			}
			
			else if (dashCnt == 23) {
				frameIndex = 4;
			}
			
			else if (dashCnt == 120 || dashCnt == 118 || dashCnt == 116) {
				if (xPos > playerPosX) {
					ef.addDasherShot(xInit - 12, yInit - 12, angleFunction(xPos + 18, yPos, playerPosX, playerPosY));
					ef.addTurretFlash(xInit - 12, yInit - 12);
				}
				
				else {
					ef.addDasherShot(xInit + 4, yInit - 12, angleFunction(xPos + 18, yPos, playerPosX, playerPosY));
					ef.addTurretFlash(xInit + 4, yInit - 12);
				}
			}
			
			else if (dashCnt == 100 || dashCnt == 98 || dashCnt == 96) {
			}
			
			else if (dashCnt == 80 || dashCnt == 78 || dashCnt == 76) {
				if (xPos > playerPosX) {
					ef.addDasherShot(xInit - 12, yInit - 12, angleFunction(xPos + 18, yPos, playerPosX, playerPosY));
					ef.addTurretFlash(xInit - 12, yInit - 12);
				}
				
				else {
					ef.addDasherShot(xInit + 4, yInit - 12, angleFunction(xPos + 18, yPos, playerPosX, playerPosY));
					ef.addTurretFlash(xInit + 4, yInit - 12);
				}
			}
		}

		else {
			// Check for collisions with walls, with a certain radius constraint
			bool foundCollision = ::checkWallCollision(walls, 48, xPos, yPos);
			// Redirect the enemy if a collision occurs with a wall
			if (foundCollision) {
				hspeed *= -1;
				vspeed *= -1;
			}
			
			// If counter reaches 0, switch state variable
			if (--dashCnt == 0) {
				dashCnt = 150;
				frameIndex = 0;
				isDashing = false;
			}
			
			if (dashCnt == 23 || dashCnt == 14) {
				hspeed *= 0.6;
				vspeed *= 0.6;
			}
			
			if (dashCnt > 20) {
				// Create motion blur
				if (--blurCountDown == 0) {
					blurCountDown = 3;
					DasherBlur b (&sprs[2], xInit + 4, yInit);
					blurEffects.push_back(b);
				}
			}
			
			if (dashCnt < 15) {
				frameIndex = 1;
				hspeed = 0;
				vspeed = 0;
				blurCountDown = 3;
			}

			else {
				// Flip the enemy's sprites according to the direction it will be moving in
			}
		}

		if (!blurEffects.empty()) {
			for (std::vector<DasherBlur>::iterator it = blurEffects.begin(); it != blurEffects.end();) {
				if (it->getKillFlag()) {
					it = blurEffects.erase(it);
				}
				
				else {
					it->getSprite()->setPosition(it->xInit + xOffset, it->yInit + yOffset);
					++it;
				}
			}
		}

		// Move the object based on current speed
		xInit += hspeed;
		yInit += vspeed;
	}
	
	// If it's time to play the death sequence
	else {
		timer += elapsedTime.asMilliseconds();
		if (timer > 52.8) {
			timer = 0;
			if (frameIndex < 16) {
				if (!::checkWallCollision(walls, 48, xPos, yPos))
					xInit += 0.5 * sprs[frameIndex].getScale().x;
			} else {
				if (!::checkWallCollision(walls, 48, xPos, yPos))
					xInit += 0.35 * sprs[frameIndex].getScale().x;
			}
			
			if (frameIndex == 20) {
				killFlag = true;
			}
			
			if (frameIndex < 20) {
				frameIndex++;
			}
		}
	}
}
*/

std::vector<DasherBlur> * Dasher::getBlurEffects() {
	return &blurEffects;
}

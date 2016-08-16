//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
//                                                                        //
// This program is free software: you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or      //
// (at your option) any later version.                                    //
//                                                                        //
// This program is distributed in the hope that it will be useful,        //
// but WITHOUT ANY WARRANTY; without even the implied warranty of         //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
// GNU General Public License for more details.                           //
//                                                                        //
// You should have received a copy of the GNU General Public License      //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
//========================================================================//

#include "scoot.hpp"
#include <cmath>
#include "angleFunction.hpp"

Scoot::Scoot(const sf::Texture & mainTxtr, const sf::Texture & shadowTxtr, float _xPos, float _yPos)
	: Enemy{_xPos, _yPos},
	  spriteSheet{mainTxtr},
	  speedScale{0.5f},
	  state{State::drift1},
	  timer{std::abs(static_cast<int>(global::RNG())) % 250}
{
	spriteSheet.setOrigin(6, 6);
	shadow.setTexture(shadowTxtr);
	float dir = std::abs(static_cast<int>(global::RNG())) % 359;
	hSpeed = cos(dir) * 0.5;
	vSpeed = sin(dir) * 0.5;
	health = 2;
}

const Scoot::HBox & Scoot::getHitBox() const {
	return hitBox;
}

void Scoot::changeDir(float dir) {
	hSpeed = std::cos(dir);
	vSpeed = std::sin(dir);	
}

void Scoot::update(float playerPosX, float playerPosY, const std::vector<wall> & w, EffectGroup & effects, const sf::Time & elapsedTime) {
	for (auto & element : effects.get<9>()) {
		if (hitBox.overlapping(element.getHitBox()) && element.checkCanPoof()) {
			if (health == 1) {
				element.disablePuff();
				element.setKillFlag();
			}
			element.poof();
			health -= 1;
			colored = true;
			colorAmount = 1.f;
		}
	}
	if (health == 0) {
		onDeath(effects);
	}
	Enemy::updateColor(elapsedTime);
	hitBox.setPosition(xPos, yPos);
	spriteSheet.setPosition(xPos, yPos);
	shadow.setPosition(xPos - 6, yPos + 2);

	// Face the player
	if (xPos > playerPosX)
		spriteSheet.setScale(1, 1);
	else 
		spriteSheet.setScale(-1, 1);
	
	// Enemies behave as state machines
	switch(state) {
	case State::drift1:
		timer += elapsedTime.asMilliseconds();
		if (timer > 1800) {
			timer -= 1800;;
			state = State::drift2;
			if (std::abs(static_cast<int>(global::RNG())) % 2) {
				changeDir(atan((yPos - playerPosY) / (xPos - playerPosX)));
			} else {
				changeDir(static_cast<float>(std::abs(static_cast<int>(global::RNG())) % 359));
			}
		}
		break;

	case State::drift2:
		timer += elapsedTime.asMilliseconds();
		if (timer > 1800) {
			timer -= 1800;
			state = State::shoot;
		}
		break;
		
	case State::shoot:
		effects.add<0>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects), xPos - 8, yPos - 12);
		effects.add<8>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects),
					   global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::redglow),
					   xPos - 8, yPos - 12, angleFunction(playerPosX + 16, playerPosY + 8, xPos - 8, yPos - 8));
		state = State::recoil;
		changeDir(atan((yPos - playerPosY) / (xPos - playerPosX)));
		hSpeed *= -1;
		vSpeed *= -1;
		// Correct for negative values in arctan calculation
		if (xPos > playerPosX) {
			hSpeed *= -1;
			vSpeed *= -1;
		}
		speedScale = 2.f;
		break;

	case State::recoil:
		timer += elapsedTime.asMilliseconds();
		speedScale *= 0.99;
		if (timer > 400) {
			timer -= 400;
			state = State::drift1;
			speedScale = 0.5f;
			if (std::abs(static_cast<int>(global::RNG())) % 2) {
				changeDir(atan((yPos - playerPosY) / (xPos - playerPosX)));
			} else {
				changeDir(static_cast<float>(std::abs(static_cast<int>(global::RNG())) % 359));
			}
		}
		break;
	}
	uint_fast8_t collisionMask = Enemy::checkWallCollision(w, xPos - 8, yPos - 8);
	if (collisionMask) {
		hSpeed = 0;
		vSpeed = 0;
		if (collisionMask & 0x01) {
			hSpeed += 1;
		}
		if (collisionMask & 0x02) {
			hSpeed -= 1;
		}
		if (collisionMask & 0x04) {
			vSpeed += 1;
		}
		if (collisionMask & 0x08) {
			vSpeed -= 1;
		}
	}
	xPos += (elapsedTime.asMicroseconds() * 0.00006f) * hSpeed * speedScale;
	yPos += (elapsedTime.asMicroseconds() * 0.00006f) * vSpeed * speedScale;
	frameTimer += elapsedTime.asMilliseconds();
	if (frameTimer > 87) {
		frameTimer -= 87;
		frameIndex ^= 0x01;
	}
}

const sf::Sprite & Scoot::getSprite() const {
	return spriteSheet[frameIndex];
}

const sf::Sprite & Scoot::getShadow() const {
	return shadow;
}

void Scoot::onDeath(EffectGroup & effects) {
	int select{std::abs(static_cast<int>(global::RNG())) % 5};
	if (select == 0) {
		effects.add<4>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects),
					   global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::redglow),
					   xPos, yPos + 4, Item::Type::Heart);
	} else {
		effects.add<5>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects),
					   global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::blueglow),
					   xPos, yPos + 4, Item::Type::Coin);
	}
	effects.add<2>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects),
				   global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::fireExplosionGlow),
				   xPos, yPos - 2);
	killFlag = true;
	return;
}

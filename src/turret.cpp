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

#include "turret.hpp"
#include <cmath>
#include "angleFunction.hpp"

Turret::Turret(const sf::Texture & gameObjects, float _xPos, float _yPos) :
	state(State::closed),
	xPos(_xPos),
	yPos(_yPos),
	frameIndex(0),
	timer(0),
	hp(6),
	killFlag(0),
	colorTimer(0),
	isColored(0),
	colorAmount(0)
{
	turretSheet.setTexture(gameObjects);
	shadowSheet.setTexture(gameObjects);
	hitBox.setPosition(xPos, yPos);
	turretSheet.setPosition(xPos, yPos);
	shadowSheet.setPosition(xPos, yPos + 18);
}

const sf::Sprite & Turret::getSprite() {
	return turretSheet[frameIndex];
}

void Turret::update(const sf::Time & elapsedTime, float playerPosX, float playerPosY, EffectGroup & effects) {
	if (isColored) {
		colorTimer += elapsedTime.asMilliseconds();
		if (colorTimer > 20.f) {
			colorTimer -= 20.f;
			colorAmount -= 0.1f;
		}
		if (colorAmount <= 0.f) {
			isColored = false;
		}
	}
	for (auto & element : effects.get<9>()) {
		if (hitBox.overlapping(element.getHitBox()) && element.checkCanPoof()) {
			if (hp == 1) {
				element.disablePuff();
				element.setKillFlag();
			}
			element.poof();
			hp -= 1;
			isColored = true;
			colorAmount = 1.f;
		}
	}
	if (hp == 0) {
		killFlag = true;
		if ((std::abs(static_cast<int>(global::RNG())) % 4) == 0) {
			effects.add<4>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects),
						   global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::redglow),
						   xPos + 8, yPos + 4, Item::Type::Heart);
		} else {
		    effects.add<5>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects),
						   global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::blueglow),
						   xPos + 8, yPos + 4, Item::Type::Coin);
		}
		effects.add<2>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects),
					   global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::fireExplosionGlow),
					   xPos + 12, yPos + 12);
	}
	switch (state) {
	case State::closed:
		if (std::sqrt(std::pow((xPos - playerPosX + 8), 2) + std::pow((yPos - playerPosY + 16), 2)) < 174) {
			state = State::opening;
			timer = 0;
			frameIndex = 0;
		}
		break;

	case State::opening:
		timer += elapsedTime.asMicroseconds();
		if (timer > 50000) {
			timer = 0;
			frameIndex += 1;
			if (frameIndex > 4) {
				frameIndex = 4;
				state = State::shoot1;
			}
		}
		break;

	case State::shoot1:
		timer += elapsedTime.asMicroseconds();
		if (timer > 200000) {
			effects.add<0>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects), xPos, yPos + 6);
			effects.add<6>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects),
						   global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::redglow),
						   xPos, yPos + 6, angleFunction(playerPosX + 16, playerPosY + 8, xPos + 18, yPos + 6));
			timer = 0;
			state = State::shoot2;
		}
		break;

	case State::shoot2:
		timer += elapsedTime.asMicroseconds();
		if (timer > 200000) {
			effects.add<0>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects), xPos, yPos + 6);
			effects.add<6>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects),
						   global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::redglow),
						   xPos, yPos + 6, angleFunction(playerPosX + 16, playerPosY + 8, xPos + 18, yPos + 6));
			timer = 0;
			state = State::shoot3;
		}
		break;

	case State::shoot3:
		timer += elapsedTime.asMicroseconds();
		if (timer > 200000) {
			effects.add<0>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects), xPos, yPos + 6);
			effects.add<6>(global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::gameObjects),
						   global::resourceHandlerPtr->getTexture(ResourceHandler::Texture::redglow),
						   xPos, yPos + 6, angleFunction(playerPosX + 16, playerPosY + 8, xPos + 18, yPos + 6));
			timer = 0;
			state = State::rest;
		}
		break;

	case State::rest:
		timer += elapsedTime.asMicroseconds();
		if (timer > 1200000) {
			if (std::sqrt(std::pow((xPos - playerPosX + 8), 2) + std::pow((yPos - playerPosY + 16), 2)) < 174) {
				state = State::shoot1;
			} else {
				state = State::closing;
			}
			timer = 0;
		}
		break;
		
	case State::closing:
		timer += elapsedTime.asMicroseconds();
		if (timer > 50000) {
			timer = 0;
			frameIndex -= 1;
			if (frameIndex < 0) {
				frameIndex = 0;
				state = State::closed;
			}
		}
		break;
	}
}

const Turret::HBox & Turret::getHitBox() const {
	return hitBox;
}

//Returns the turret's shadow sprite
const sf::Sprite & Turret::getShadow() {
	return shadowSheet[frameIndex];
}

bool Turret::getKillFlag() {
	return killFlag;
}

float Turret::getXpos() {
	return xPos;
}

float Turret::getYpos() {
	return yPos;
}

bool Turret::colored() {
	return isColored;
}

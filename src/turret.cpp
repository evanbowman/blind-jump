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
	xPos(_xPos),
	yPos(_yPos),
	imageIndex(0),
	animationCount(0),
	active(0),
	activateTimer(120),
	shotCountdown(40),
	shotsFired(0),
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
	return turretSheet[imageIndex];
}

void Turret::update(const sf::Time & elapsedTime, float playerPosX, float playerPosY) {
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
	if (active) {
		if (sqrt(pow((xPos - playerPosX + 8), 2) + pow((yPos - playerPosY + 16), 2)) > 174) {
			if (imageIndex != 0 && sqrt(pow((xPos - playerPosX + 8), 2) + pow((yPos - playerPosY + 16), 2)) > 228) {	//If the player is far enough away de-activate it
				if (animationCount == 1) {
					imageIndex -= 1;
					animationCount = 0;
				}
				animationCount += 1;
				//Lets have the time until the turret shoots after upening be the same every time:
				shotCountdown = 20;
				shotsFired = 0;
			}
			else {
				animationCount = 0;
			}
		}
		else {							  //If the player is close activate the turret
			if (imageIndex != 4) {
				if (animationCount == 3) {
					imageIndex += 1;
					animationCount = 0;
				}
				animationCount += 1;
			
			}
			else {
				animationCount = 0;
				disableCountdown = 50;
			}
		}
	}
	else {
		if (--activateTimer == 0) {
			active = 1;
		}
	}
}

const Turret::HBox & Turret::getHitBox() const {
	return hitBox;
}

//Returns the turret's shadow sprite
const sf::Sprite & Turret::getShadow() {
	return shadowSheet[imageIndex];
}

void Turret::updateShots(EffectGroup & effects, FontController & fonts, float playerPosX, float playerPosY) {
	//If the turret is open...
	if (imageIndex == 4) {
		//And the shot coundown timer has decremented far enough
		if (--shotCountdown == 0) {
			//Add a shot flash effect to the effects controller
			effects.add<0>(globalResourceHandler.getTexture(ResourceHandler::Texture::gameObjects), xPos, yPos);
			//Create a shot object with an angle equal to the angle between the player and the turret
			effects.add<6>(globalResourceHandler.getTexture(ResourceHandler::Texture::gameObjects),
						   globalResourceHandler.getTexture(ResourceHandler::Texture::redglow),
						   xPos, yPos, angleFunction(playerPosX, playerPosY, xPos + 18, yPos + 6));
			//Increment the number of shots fired
			shotsFired++;
			//Reset the countdown timer
			if (shotsFired != 3) {
				shotCountdown = 8;
			}
			else {
				shotCountdown = 60;
				shotsFired = 0;
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
	}
	
	if (hp == 0) {
		killFlag = true;
		if ((std::abs(static_cast<int>(globalRNG())) % 4) == 0) {
			effects.add<4>(globalResourceHandler.getTexture(ResourceHandler::Texture::gameObjects),
					   globalResourceHandler.getTexture(ResourceHandler::Texture::redglow),
					   xPos, yPos + 4, Powerup::Type::Heart);
		} else {
		    effects.add<5>(globalResourceHandler.getTexture(ResourceHandler::Texture::gameObjects),
					   globalResourceHandler.getTexture(ResourceHandler::Texture::blueglow),
					   xPos, yPos + 4, Powerup::Type::Coin);
		}
		effects.add<2>(globalResourceHandler.getTexture(ResourceHandler::Texture::gameObjects),
				   globalResourceHandler.getTexture(ResourceHandler::Texture::fireExplosionGlow),
				   xPos, yPos -2);
	}
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

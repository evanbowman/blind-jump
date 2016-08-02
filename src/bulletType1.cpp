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

#include "bulletType1.hpp"

PlayerShot::PlayerShot(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr, char dir, float x, float y) :
	Effect{x, y},
	direction{dir},
	canPoof{true},
	state{State::travelling}
{
	spriteSheet.setTexture(mainTxtr);
	puffSheet.setTexture(mainTxtr);
	glow.setTexture(glowTxtr);
	canPoof = true;
	if (dir == 0 || dir == 1 || dir == 4 || dir == 5) {
		spriteSheet[1];
	} else {
		spriteSheet[0];
	}
}

const sf::Sprite & PlayerShot::getSprite() {
	switch (state) {
	case State::travelling:
		return spriteSheet.getSprite();
		break;

	case State::poof:
		return puffSheet[frameIndex];
		break;
	}
}

const sf::Sprite & PlayerShot::getGlow() {
	return glow;
}

void PlayerShot::poof() {
	if (canPoof) {
		canPoof = false;
		state = State::poof;
		timer = 0;
		puffSheet.setPosition(position.x, position.y);
	}
}

void PlayerShot::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	const static float movementRate = 0.45;
	timer += elapsedTime.asMilliseconds();
	hitBox.setPosition(position);
	switch (state) {
	case State::travelling:
		if (direction == 0 || direction == 4) {
			yInit += movementRate * elapsedTime.asMilliseconds();
			setPosition(xInit + xOffset + 6, yInit + 12 + yOffset);	
		} else if (direction == 1 || direction == 5) {
			yInit -= movementRate * elapsedTime.asMilliseconds();
			setPosition(xInit + xOffset + 6, yInit  + yOffset);	
		} else if (direction == 2 || direction == 6) {
			xInit -= movementRate * elapsedTime.asMilliseconds();
			setPosition(xInit + xOffset - 5, yInit + 8 + yOffset);	
		} else if (direction == 3 || direction == 7) {
			xInit += movementRate * elapsedTime.asMilliseconds();
			setPosition(xInit + xOffset + 22, yInit + 8 + yOffset);	
		}
		spriteSheet.setPosition(position.x, position.y);
		glow.setPosition(position.x - 16, position.y - 11);
		if (timer > 200) {
			if (canPoof) {
				canPoof = false;
				state = State::poof;
				timer = 0;
				puffSheet.setPosition(position.x, position.y);
			} else {
				setKillFlag();
			}
		}
		break;

	case State::poof:
		if (direction == 0 || direction == 4) {
			setPosition(xInit + xOffset + 6, yInit + 12 + yOffset);	
		} else if (direction == 1 || direction == 5) {
			setPosition(xInit + xOffset + 6, yInit  + yOffset);	
		} else if (direction == 2 || direction == 6) {
			setPosition(xInit + xOffset - 5, yInit + 8 + yOffset);	
		} else if (direction == 3 || direction == 7) {
			setPosition(xInit + xOffset + 22, yInit + 8 + yOffset);	
		}
		if (timer > 50) {
			timer -= 50;
			++frameIndex;
			sf::Color color = glow.getColor();
			color.r -= 50;
			color.g -= 50;
			color.b -= 50;
			glow.setColor(color);
			if (frameIndex == 4) {
				frameIndex = 3;
				setKillFlag();
			}
		}
		puffSheet.setPosition(position.x, position.y);
		break;
	}
}

char PlayerShot::getDirection() {
	return direction;
}

bool PlayerShot::checkCanPoof() {
	return canPoof;
}

void PlayerShot::disablePuff() {
	canPoof = false;
}

const PlayerShot::HBox & PlayerShot::getHitBox() const {
	return hitBox;
}

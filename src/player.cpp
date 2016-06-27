//
//  player.cpp
//  BlindJump
//
//  Created by Evan Bowman on 10/9/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "player.hpp"
#include "ResourcePath.hpp"
#include "playerAnimationFunctions.hpp"
#include <cmath>
#include "playerCollisionFunctions.hpp"
#include "wall.hpp"
#include <tuple>
#include "gameMap.hpp"

Player::Player(ResourceHandler * pTM, float _xPos, float _yPos)
	: health{4},
	  xPos{_xPos},
	  yPos{_yPos},
	  worldOffsetX{0.f},
	  worldOffsetY{0.f},
	  frameIndex{5},
	  sheetIndex{Sheet::stillDown},
	  lSpeed{0},
	  rSpeed{0},
	  uSpeed{0},
	  dSpeed{0},
	  animationTimer{0},
	  invulnerableCounter{0},
	  invulnerable{false},
	  state{Player::State::nominal},
	  colorAmount{0.f},
	  colorTimer{0},
	  renderType{Rendertype::shadeDefault},
	  upPrevious{false},
	  downPrevious{false},
	  leftPrevious{false},
	  rightPrevious{false}
{
	weapon.setPosition(xPos, yPos);
	scrShakeState = false;
	deathSheet.setTexture(pTM->getTexture(ResourceHandler::Texture::gameObjects));
	walkDown.setTexture(pTM->getTexture(ResourceHandler::Texture::gameObjects));
	walkUp.setTexture(pTM->getTexture(ResourceHandler::Texture::gameObjects));
	walkLeft.setTexture(pTM->getTexture(ResourceHandler::Texture::gameObjects));
	walkRight.setTexture(pTM->getTexture(ResourceHandler::Texture::gameObjects));
	walkDown.setPosition(xPos, yPos);
	walkUp.setPosition(xPos, yPos);
	walkLeft.setPosition(xPos, yPos);
	walkRight.setPosition(xPos, yPos);
	shadowSprite.setPosition(xPos + 7, yPos + 24);
	dashSheet.setPosition(xPos, yPos);
	deathSheet.setPosition(xPos - 13, yPos - 1);
	dashSheet.setTexture(pTM->getTexture(ResourceHandler::Texture::gameObjects));
	dashSheet.setOrigin(0, 1);
	shadowSprite.setTexture(pTM->getTexture(ResourceHandler::Texture::gameObjects));
	shadowSprite.setTextureRect(sf::IntRect(0, 100, 18, 16));
}

void Player::setPosition(float _xPos, float _yPos) {
	xPos = _xPos;
	yPos = _yPos;
}

float Player::getXpos() const {
	return xPos;
}

float Player::getYpos() const {
	return yPos;
}

template<typename T>
bool checkShotCollision(std::vector<T>* shotVec, double playerXpos, double playerYpos) {
	// If the vector is not empty
	if (!shotVec->empty()) {
		// Loop through the vector and check whether the enemy shot objects are close to the player
		for (auto & element : *shotVec) {
			if (std::abs(playerXpos + 16 - element.getXpos()) < 10 && std::abs(playerYpos + 16 - element.getYpos()) < 10) {
				// Set a flag within the element that tells its controller to remove it from its vector
				element.setKillFlag();
				return true;
			}
		}
	}
	// Nothing hit the player, so return false
	return false;
}

void Player::update(GameMap * pGM, const sf::Time & elapsedTime) {
	InputController * pInput   {pGM->getPInput()};
	tileController & tiles     {pGM->getTileController()};
	detailController & details {pGM->getDetails()};
	bool x     {pInput->xPressed()};
	bool up    {pInput->upPressed()};
	bool down  {pInput->downPressed()};
	bool left  {pInput->leftPressed()};
	bool right {pInput->rightPressed()};
	bool collisionLeft  {false};
	bool collisionRight {false};
    bool collisionUp    {false};
	bool collisionDown  {false};

	checkCollisionWall(tiles.walls, collisionDown, collisionUp, collisionRight, collisionLeft, yPos, xPos);
	checkCollisionChest(details.getChests(), collisionDown, collisionUp, collisionRight, collisionLeft, yPos, xPos);
	
	switch (state) {
	case State::deactivated:
		sheetIndex = Sheet::walkDown;
		frameIndex = 5;
		lSpeed = 0.f;
		rSpeed = 0.f;
		uSpeed = 0.f;
		dSpeed = 0.f;
		break;

	case State::nominal:
		if (!x) {
			if (up) {
				if (!down && !left && !right && sheetIndex != Sheet::walkUp)  {
					sheetIndex = Sheet::walkUp;
				}
			
				if (collisionUp == 0) {
					if (left || right) {
						uSpeed = 1.87f;
					} else {
						uSpeed = 2.20f;
					}
				}
			} else {
				uSpeed = 0.f;
			}
			
			if (down) {
				if (!up && !left && !right && sheetIndex != Sheet::walkDown) {
					sheetIndex = Sheet::walkDown;
				}

				if (collisionDown == 0) {
					if (right || left) {
						dSpeed = 1.87f;
					} else {
						dSpeed = 2.20f;
					}
				}
			} else {
				dSpeed = 0.f;
			}
			
			if (right) {
				if (!left && !down && !up && sheetIndex != Sheet::walkRight) {
					sheetIndex = Sheet::walkRight;
					if (frameIndex > 5) {
						frameIndex = 0;
					}
				}

				if (collisionRight == 0) {
					if (up || down) {
						rSpeed = 1.87f;
					} else {
						rSpeed = 2.20f;
					}
				}
			} else {
				rSpeed = 0.f;
			}
			
			if (left) {
				if (!right && !up && !down && sheetIndex != Sheet::walkLeft) {
					sheetIndex = Sheet::walkLeft;
					if (frameIndex > 5) {
						frameIndex = 0;
					}
				}

				if (collisionLeft == 0) {
					if (up || down) {
						lSpeed = 1.87f;
					} else {
						lSpeed = 2.20f;
					}
				}
			} else {
				lSpeed = 0.f;
			}
		}

		if (!left && leftPrevious) {
			if (!left && !right && !up && !down) {
				if (!x) {
					sheetIndex = Sheet::stillLeft;
					frameIndex = 5;
				} // else if (x) {
				// 	compareSpriteIndex(sheetIndex);
				// }
			}
		}
		
		if (!right && rightPrevious) {
			if (!left && !right && !up && !down) {
				if (!x) {
					sheetIndex = Sheet::stillRight;
					frameIndex = 5;
				} // else if (x) {
				// 	compareSpriteIndex(sheetIndex);
				// }
			}
		}
		
		if (!up && upPrevious) {
			if (!left && !right && !up && !down) {
				if (!x) {
					sheetIndex = Sheet::stillUp;
					frameIndex = 6;
				} // else if (x) {
				// 	compareSpriteIndex(sheetIndex);
				// }
			}
		}
		
		if (!down && downPrevious) {
			if (!left && !right && !up && !down) {
				if (!x) {
					sheetIndex = Sheet::stillDown;
					frameIndex = 6;
				} // else if (x) {
				// 	compareSpriteIndex(sheetIndex);
				// }
			}
		}
		break;

	case State::dashing:
		break;

	case State::cooldown:
		break;

	case State::dead:
		break;

	case State::prepdash:
		break;
	}

	colorTimer = 0;
	
	worldOffsetX += lSpeed + -rSpeed * (elapsedTime.asMilliseconds() / 17.6);
	worldOffsetY += uSpeed + -dSpeed * (elapsedTime.asMilliseconds() / 17.6);
	
	upPrevious = up;
	downPrevious = down;
	leftPrevious = left;
	rightPrevious = right;
}

void Player::draw(drawableVec & gameObjects, drawableVec & gameShadows, const sf::Time & elapsedTime) {
	if (visible) {
		switch (sheetIndex) {
		case Sheet::stillDown:
			gameObjects.emplace_back(walkDown[5], yPos, renderType, colorAmount);
			gameShadows.emplace_back(shadowSprite, 0.f, Rendertype::shadeDefault, 0.f);
			break;

		case Sheet::stillUp:
			gameObjects.emplace_back(walkUp[5], yPos, renderType, colorAmount);
			gameShadows.emplace_back(shadowSprite, 0.f, Rendertype::shadeDefault, 0.f);
			break;

		case Sheet::stillLeft:
			gameObjects.emplace_back(walkLeft[6], yPos, renderType, colorAmount);
			gameShadows.emplace_back(shadowSprite, 0.f, Rendertype::shadeDefault, 0.f);
			break;

		case Sheet::stillRight:
			gameObjects.emplace_back(walkRight[6], yPos, renderType, colorAmount);
			gameShadows.emplace_back(shadowSprite, 0.f, Rendertype::shadeDefault, 0.f);
			break;
			
		case Sheet::walkDown:
		    updateAnimation(downPrevious, elapsedTime, 9, 100);
			gameObjects.emplace_back(walkDown[verticalAnimationDecoder(frameIndex)], yPos, renderType, colorAmount);
			gameShadows.emplace_back(shadowSprite, 0.f, Rendertype::shadeDefault, 0.f);
			break;

		case Sheet::walkUp:
			updateAnimation(upPrevious, elapsedTime, 9, 100);
			gameObjects.emplace_back(walkUp[verticalAnimationDecoder(frameIndex)], yPos, renderType, colorAmount);
			gameShadows.emplace_back(shadowSprite, 0.f, Rendertype::shadeDefault, 0.f);
			break;

		case Sheet::walkLeft:
			updateAnimation(leftPrevious, elapsedTime, 5, 100);
			gameObjects.emplace_back(walkLeft[frameIndex], yPos, renderType, colorAmount);
			gameShadows.emplace_back(shadowSprite, 0.f, Rendertype::shadeDefault, 0.f);
			break;

		case Sheet::walkRight:
			updateAnimation(rightPrevious, elapsedTime, 5, 100);
			gameObjects.emplace_back(walkRight[frameIndex], yPos, renderType, colorAmount);
			gameShadows.emplace_back(shadowSprite, 0.f, Rendertype::shadeDefault, 0.f);
			break;

		case Sheet::deathSheet:
			gameObjects.emplace_back(deathSheet[frameIndex], yPos, renderType, colorAmount);
			break;

		case Sheet::dashSheet:
			gameObjects.emplace_back(dashSheet[frameIndex], yPos, renderType, colorAmount);
			gameShadows.emplace_back(shadowSprite, 0.f, Rendertype::shadeDefault, 0.f);
			break;
		}
	}
}

void Player::updateAnimation(bool key, const sf::Time & elapsedTime, uint8_t maxIndex, uint8_t count) {
	if (key) {
		animationTimer += elapsedTime.asMilliseconds();
		if (animationTimer > count) {
			frameIndex++;
			animationTimer -= count;
			if (frameIndex > maxIndex)
				frameIndex = 0;
		}
	} else {
		frameIndex = maxIndex + 1;
	}
}

float Player::getWorldOffsetX() const {
	return worldOffsetX;
}

float Player::getWorldOffsetY() const {
	return worldOffsetY;
}

void Player::setWorldOffsetX(float x) {
	worldOffsetX = x;
}

void Player::setWorldOffsetY(float y) {
	worldOffsetY = y;
}

char Player::getSprIndex() const {
	return static_cast<int>(sheetIndex);
}

void Player::setState(State _state) {
	state = _state;
}

Player::State Player::getState() const {
	return state;
}

char Player::getHealth() const {
	return health;
}

void Player::reset() {
	state = State::nominal;
	invulnerable = false;
	invulnerableCounter = 0;
	health = 4;
	sheetIndex = Sheet::walkDown;
	weapon.setTimeout(0);
}

void Player::fillHealth(char health) {
	this->health = health;
}

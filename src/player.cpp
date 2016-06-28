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
	  xPos{_xPos - 17}, // Magic number that puts the player in the direct center of the screen. Hmmm why does it work...
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
	for (auto & element : *shotVec) {
		if (std::abs(playerXpos + 16 - element.getXpos()) < 10 && std::abs(playerYpos + 16 - element.getYpos()) < 10) {
			element.setKillFlag();
			return true;
		}
	}
	return false;
}

inline void compareSheetIndex(Player::Sheet & sheetIndex) {
	switch (sheetIndex) {
	case Player::Sheet::walkDown: sheetIndex = Player::Sheet::stillDown;
		break;
	case Player::Sheet::walkUp: sheetIndex = Player::Sheet::stillUp;
		break;
	case Player::Sheet::walkLeft: sheetIndex = Player::Sheet::stillLeft;
		break;
	case Player::Sheet::walkRight: sheetIndex = Player::Sheet::stillRight;
		break;
	default:
		break;
	}
}

template <Player::Sheet S>
void regKeyResponse(bool key1, bool key2, bool key3, bool key4, Player::Sheet & sheetIndex, float & speed, bool collision) {
	if (key1) {
		if (!key2 && !key3 && !key4 && sheetIndex != S) {
			sheetIndex = S;
		}
		if (!collision) {
			if (key3 || key4) {
				speed = 1.70f;
			} else {
				speed = 2.20f;
			}
		} else {
			speed = 0.f;
		}
	} else {
		speed = 0.f;
	}
}

template <Player::Sheet S>
void altKeyResponse(bool key1, bool key2, bool key3, Player::Sheet & sheetIndex, bool collision, float & speed) {
	if (key1) {
		sheetIndex = S;
		if (!collision) {
			if (key2 || key3) {
				speed = 1.40f;
			} else {
				speed = 1.80f;
			}
		} else {
			speed = 0.f;
		}
	} else {
		speed = 0.f;
	}
}

template <Player::Sheet S, uint8_t maxIndx>
void onKeyReleased(bool key1, bool key2, bool key3, bool key4, bool keyprev, bool x, Player::Sheet & shIndex, uint8_t & frmIndex) {
	if (!key1 && keyprev) {
		if (!key2 && !key3 && !key4) {
			if (!x) {
				shIndex = S;
				frmIndex = maxIndx;
			} else {
				compareSheetIndex(shIndex);
			}
		}
	}
}

void Player::update(GameMap * pGM, const sf::Time & elapsedTime) {
	InputController * pInput {pGM->getPInput()};
	tileController & tiles {pGM->getTileController()};
	detailController & details {pGM->getDetails()};
	bool x {pInput->xPressed()};
	bool up {pInput->upPressed()};
	bool down {pInput->downPressed()};
	bool left {pInput->leftPressed()};
	bool right {pInput->rightPressed()};
    bool collisionUp {false};
	bool collisionDown {false};
	bool collisionLeft {false};
	bool collisionRight {false};
	
	checkCollisionWall(tiles.walls, collisionDown, collisionUp, collisionRight, collisionLeft, yPos, xPos);
	checkCollisionChest(details.getChests(), collisionDown, collisionUp, collisionRight, collisionLeft, yPos, xPos);
	
	switch (state) {
	case State::deactivated:
		sheetIndex = Sheet::stillDown;
		frameIndex = 5;
		lSpeed = 0.f;
		rSpeed = 0.f;
		uSpeed = 0.f;
		dSpeed = 0.f;
		break;

	case State::nominal:
		if (!x) {
			regKeyResponse<Sheet::walkUp>(up, down, left, right, sheetIndex, uSpeed, collisionUp);
			regKeyResponse<Sheet::walkDown>(down, up, left, right, sheetIndex, dSpeed, collisionDown);
			regKeyResponse<Sheet::walkLeft>(left, right, down, up, sheetIndex, lSpeed, collisionLeft);
			regKeyResponse<Sheet::walkRight>(right, left, down, up, sheetIndex, rSpeed, collisionRight);
		} else {
			if (sheetIndex == Sheet::walkUp || sheetIndex == Sheet::stillUp) {
				altKeyResponse<Sheet::walkUp>(up, left, right, sheetIndex, collisionUp, uSpeed);
				altKeyResponse<Sheet::walkUp>(down, left, right, sheetIndex, collisionDown, dSpeed);
				altKeyResponse<Sheet::walkUp>(left, up, down, sheetIndex, collisionLeft, lSpeed);
				altKeyResponse<Sheet::walkUp>(right, up, down, sheetIndex, collisionRight, rSpeed);
			}
			if (sheetIndex == Sheet::walkDown || sheetIndex == Sheet::stillDown) {
				altKeyResponse<Sheet::walkDown>(up, left, right, sheetIndex, collisionUp, uSpeed);
				altKeyResponse<Sheet::walkDown>(down, left, right, sheetIndex, collisionDown, dSpeed);
				altKeyResponse<Sheet::walkDown>(left, up, down, sheetIndex, collisionLeft, lSpeed);
				altKeyResponse<Sheet::walkDown>(right, up, down, sheetIndex, collisionRight, rSpeed);
			}
			if (sheetIndex == Sheet::walkRight || sheetIndex == Sheet::stillRight) {
				altKeyResponse<Sheet::walkRight>(up, left, right, sheetIndex, collisionUp, uSpeed);
				altKeyResponse<Sheet::walkRight>(down, left, right, sheetIndex, collisionDown, dSpeed);
				altKeyResponse<Sheet::walkRight>(left, up, down, sheetIndex, collisionLeft, lSpeed);
				altKeyResponse<Sheet::walkRight>(right, up, down, sheetIndex, collisionRight, rSpeed);
			}
			if (sheetIndex == Sheet::walkLeft || sheetIndex == Sheet::stillLeft) {
				altKeyResponse<Sheet::walkLeft>(up, left, right, sheetIndex, collisionUp, uSpeed);
				altKeyResponse<Sheet::walkLeft>(down, left, right, sheetIndex, collisionDown, dSpeed);
				altKeyResponse<Sheet::walkLeft>(left, up, down, sheetIndex, collisionLeft, lSpeed);
				altKeyResponse<Sheet::walkLeft>(right, up, down, sheetIndex, collisionRight, rSpeed);
			}
		}
		onKeyReleased<Player::Sheet::stillLeft, 5>(left, right, up, down, leftPrevious, x, sheetIndex, frameIndex);
		onKeyReleased<Player::Sheet::stillRight, 5>(right, left, up, down, rightPrevious, x, sheetIndex, frameIndex);
		onKeyReleased<Player::Sheet::stillUp, 4>(up, left, right, down, upPrevious, x, sheetIndex, frameIndex);
		onKeyReleased<Player::Sheet::stillDown, 4>(down, left, right, up, downPrevious, x, sheetIndex, frameIndex);
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

	colorTimer = 0; // TODO: This is for -Wall -Wnounused, but does need to be correctly set!
	
	worldOffsetX += (lSpeed + -rSpeed) * (elapsedTime.asMilliseconds() / 17.6);
	worldOffsetY += (uSpeed + -dSpeed) * (elapsedTime.asMilliseconds() / 17.6);
	
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
		    updateAnimation(elapsedTime, 9, 100);
			gameObjects.emplace_back(walkDown[verticalAnimationDecoder(frameIndex)], yPos, renderType, colorAmount);
			gameShadows.emplace_back(shadowSprite, 0.f, Rendertype::shadeDefault, 0.f);
			break;

		case Sheet::walkUp:
			updateAnimation(elapsedTime, 9, 100);
			gameObjects.emplace_back(walkUp[verticalAnimationDecoder(frameIndex)], yPos, renderType, colorAmount);
			gameShadows.emplace_back(shadowSprite, 0.f, Rendertype::shadeDefault, 0.f);
			break;

		case Sheet::walkLeft:
			updateAnimation(elapsedTime, 5, 100);
			gameObjects.emplace_back(walkLeft[frameIndex], yPos, renderType, colorAmount);
			gameShadows.emplace_back(shadowSprite, 0.f, Rendertype::shadeDefault, 0.f);
			break;

		case Sheet::walkRight:
			updateAnimation(elapsedTime, 5, 100);
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

void Player::updateAnimation(const sf::Time & elapsedTime, uint8_t maxIndex, uint8_t count) {
	animationTimer += elapsedTime.asMilliseconds();
	if (animationTimer > count) {
		frameIndex++;
		animationTimer -= count; 
	}
	if (frameIndex > maxIndex) {
		frameIndex = 0;
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

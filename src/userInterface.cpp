//
//  userInterface.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/22/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "userInterface.hpp"
#include <cmath>
#include "player.hpp"

UserInterface::UserInterface(float _xPos, float _yPos) :
	state{State::closed},
	xPos{_xPos},
	yPos{_yPos + 16},
	timer{0},
	timerAlt{0},
	textAlpha{0.f},
	blurAmount{0.1f},
	desaturateAmount{0.f}
{
}

void UserInterface::setView(sf::View * pView) {
	pWorldView = pView;
	cachedView = *pView;
}

bool UserInterface::isOpen() const {
	return state != State::closed;
}

const UserInterface::State UserInterface::getState() const {
	return state;
}

void UserInterface::update(sf::RenderWindow& window, Player & player, FontController & fonts, InputController * pInput, const sf::Time & elapsed) {
	bool z = pInput->zPressed();
	bool up = pInput->upPressed();
	bool down = pInput->downPressed();
	bool escape = pInput->escapePressed();
	
	switch (state) {
	case State::closed:
		if (escape) {
			state = State::menuScreenEntry;
			player.setState(Player::State::deactivated);
			fonts.setTextAlpha(0, FontController::Text::waypointText);
			fonts.setTextAlpha(0, FontController::Text::healthNumText);
			fonts.setTextAlpha(0, FontController::Text::scoreText);
			fonts.setTextAlpha(0, FontController::Text::heart);
			fonts.setTextAlpha(0, FontController::Text::coin);
		}
		break;
			
	case State::menuScreenEntry:
		timer += elapsed.asMilliseconds();
		if (timer > 20) {
			timer -= 20;
			blurAmount *= 1.2f;
			// These are loopable, but casting the loop index to a scoped enum would be less readable IMO...
			fonts.setTextAlpha(255 * blurAmount, FontController::Text::resumeText);
			fonts.setTextAlpha(255 * blurAmount, FontController::Text::settingsText);
			fonts.setTextAlpha(255 * blurAmount, FontController::Text::quitText);
			fonts.setTextOffset(0, -0.01 * blurAmount, FontController::Text::resumeText);
			fonts.setTextOffset(0, -0.01 * blurAmount, FontController::Text::settingsText);
			fonts.setTextOffset(0, -0.01 * blurAmount, FontController::Text::quitText);
			if (blurAmount > 0.99999f) {
				blurAmount = 0.99999f;
				state = State::menuScreen;
				fonts.setTextAlpha(255, FontController::Text::resumeText);
				fonts.setTextAlpha(255, FontController::Text::settingsText);
				fonts.setTextAlpha(255, FontController::Text::quitText);
			}
		}
		break;

	case State::menuScreen:
		if (escape) {
			timer = 0;
			state = State::menuScreenExit;
		} else if (up) {
			// TODO
		} else if (down) {
			// TODO
		} else if (z) {
			// TODO
		}
		break;
		
	case State::menuScreenExit:
		timer += elapsed.asMilliseconds();
		if (timer > 20) {
			timer -= 20;
			blurAmount *= 0.9f;
			fonts.setTextAlpha(255 * blurAmount, FontController::Text::resumeText);
			fonts.setTextAlpha(255 * blurAmount, FontController::Text::settingsText);
			fonts.setTextAlpha(255 * blurAmount, FontController::Text::quitText);
			fonts.setTextOffset(0, -0.01 * blurAmount, FontController::Text::resumeText);
			fonts.setTextOffset(0, -0.01 * blurAmount, FontController::Text::settingsText);
			fonts.setTextOffset(0, -0.01 * blurAmount, FontController::Text::quitText);
			if (blurAmount < 0.1f) {
				blurAmount = 0.1f;
				state = State::closed;
				player.activate();
				fonts.setTextAlpha(0, FontController::Text::resumeText);
				fonts.setTextAlpha(0, FontController::Text::settingsText);
				fonts.setTextAlpha(0, FontController::Text::quitText);
			}
		}
		break;
			
	case State::deathScreenEntry:
		timer += elapsed.asMilliseconds();
		if (timer > 20) {
			timer -= 20;
			desaturateAmount += 0.01f;
			sf::Vector2f size = pWorldView->getSize();
			float temp = size.x;
			size.x -= 0.5 * (size.y / size.x);
			size.y -= 0.5 * (size.y / temp);
			pWorldView->setSize(size);
		}
			
		if (desaturateAmount > 0.65f) {
			desaturateAmount = 0.65f;
			state = State::deathScreen;
			timerAlt = 0.f;
		}
		textAlpha = desaturateAmount * 255 + 89.25f;
		fonts.drawDeathText(static_cast<unsigned char>(textAlpha), window);
		break;
			
	case State::deathScreen:
		fonts.drawDeathText(255, window);
		timer += elapsed.asMilliseconds();
		timerAlt += elapsed.asMilliseconds();
		if (timer > 20) {
			timer -= 20;
			if (timerAlt < 1400) {
				sf::Vector2f size = pWorldView->getSize();
				float temp = size.x;
				size.x -= 0.25f * (size.y / size.x);
				size.y -= 0.25f * (size.y / temp);
				pWorldView->setSize(size);
			} else {
				timer = 0;
				state = State::deathScreenExit;
			}
		}
		break;
			
	case State::deathScreenExit:
		timer += elapsed.asMilliseconds();
		if (timer > 20) {
			timer -= 20;
			if (textAlpha > 15.f) {
				textAlpha -= 15.f;
			}
			blurAmount *= 1.2f;
		}
			
		fonts.drawDeathText(static_cast<unsigned char>(textAlpha), window);
			
		if (blurAmount > 0.99999f) {
			blurAmount = 0.99999f;
			state = State::statsScreen;
		}
		break;
			
	case State::statsScreen:
		if (z) {
			state = State::complete;
			*pWorldView = cachedView;
		}
		break;
			
	case State::complete:
		break;
	}
}

void UserInterface::addItem(char newItem, EffectGroup & ef, float xStart, float yStart, FontController& fonts, Player& player) {
	// TODO...
}

void UserInterface::dispDeathSeq() {
	if (state == UserInterface::State::closed) {
		timer = 0;
		state = UserInterface::State::deathScreenEntry;
	}
}

bool UserInterface::isComplete() {
	return state == State::complete;
}

float UserInterface::getBlurAmount() {
	return blurAmount;
}

void UserInterface::reset() {
	state = State::closed;
	desaturateAmount = 0.f;
	blurAmount = 0.1f;
}

float UserInterface::getDesaturateAmount() {
	return desaturateAmount;
}

bool UserInterface::blurEnabled() {
	return blurAmount != 0.1f;
}

bool UserInterface::desaturateEnabled() {
	return desaturateAmount > 0.f;
}

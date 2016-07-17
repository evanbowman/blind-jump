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

void UserInterface::update(sf::RenderWindow& window, Player & player, FontController & fonts, InputController * pInput, const sf::Time & elapsed) {
	bool z = pInput->zPressed();
	bool escape = pInput->escapePressed();
	
	switch (state) {
	case State::closed:
		if (escape) {
			state = State::menuScreenEntry;
			player.setState(Player::State::deactivated);
		}
		break;
			
	case State::menuScreenEntry:
		timer += elapsed.asMilliseconds();
		if (timer > 20) {
			timer -= 20;
			blurAmount *= 1.2f;
		    if (blurAmount > 0.99999f) {
				blurAmount = 0.99999f;
				state = State::menuScreen;
			}
		}
		break;

	case State::menuScreen:
		if (escape) {
			timer = 0;
			state = State::menuScreenExit;
		}
		break;
		
	case State::menuScreenExit:
		timer += elapsed.asMilliseconds();
		if (timer > 20) {
			timer -= 20;
			blurAmount *= 0.9f;
			if (blurAmount < 0.1f) {
				blurAmount = 0.1f;
				state = State::closed;
				player.activate();
			}
		}
		break;
			
	case State::deathScreenEntry:
		timer += elapsed.asMilliseconds();
		if (timer > 20.f) {
			timer -= 20.f;
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
		if (timer > 20.f) {
			timer -= 20.f;
			if (timerAlt < 1400.f) {
				sf::Vector2f size = pWorldView->getSize();
				float temp = size.x;
				size.x -= 0.25f * (size.y / size.x);
				size.y -= 0.25f * (size.y / temp);
				pWorldView->setSize(size);
			} else {
				timer = 0.f;
				state = State::deathScreenExit;
			}
		}
		break;
			
	case State::deathScreenExit:
		timer += elapsed.asMilliseconds();
		if (timer > 20.f) {
			timer -= 20.f;
			if (textAlpha > 15.f)
				textAlpha -= 15.f;
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
	if (newItem == 90) {
		fonts.updateMaxHealth(fonts.getMaxHealth() + 1);
	} else {
		//// TODO
	}
}

void UserInterface::dispDeathSeq() {
	if (state == UserInterface::State::closed) {
		timer = 0.f;
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

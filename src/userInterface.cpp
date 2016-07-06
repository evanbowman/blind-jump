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

userInterface::userInterface(float _xPos, float _yPos) :
	state{State::closed},
	xPos{_xPos},
	yPos{_yPos + 16},
	timer{0},
	timerAlt{0},
	textAlpha{0.f},
	zoomDegree{0.f},
	blurAmount{0.1f},
	desaturateAmount{0.f}
{
}

void userInterface::setView(sf::View * pView) {
	pWorldView = pView;
	cachedView = *pView;
}

void userInterface::drawMenu(sf::RenderWindow& window, Player* player, FontController& f, effectsController& ef, float xOffset, float yOffset, InputController* pInput, sf::Time& elapsed) {
	bool z = pInput->zPressed();
	
	switch (state) {
		case State::closed:
			break;
			
		case State::deathScreenEntry:
			timer += elapsed.asMilliseconds();
			if (timer > 20.f) {
				timer -= 20.f;
				desaturateAmount += 0.01f;
				zoomDegree += 0.000007f;
				pWorldView->zoom(zoomDegree);
			}
			
			if (desaturateAmount > 0.65f) {
				desaturateAmount = 0.65f;
				state = State::deathScreen;
				timerAlt = 0.f;
			}
			textAlpha = desaturateAmount * 255 + 89.25f;
			f.drawDeathText(static_cast<unsigned char>(textAlpha), window);
			break;
			
		case State::deathScreen:
			f.drawDeathText(255, window);
			timer += elapsed.asMilliseconds();
			timerAlt += elapsed.asMilliseconds();
			if (timer > 20.f) {
				timer -= 20.f;
				if (timerAlt < 1400.f) {
					zoomDegree += 0.000007f;
					pWorldView->zoom(zoomDegree);
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
			
			f.drawDeathText(static_cast<unsigned char>(textAlpha), window);
			
			if (blurAmount > 0.99999f) {
				blurAmount = 0.99999f;
				state = State::statsScreen;
				// Blurring is heavy on the graphics card
				window.setFramerateLimit(30);
			}
			break;
			
		case State::statsScreen:
			if (z) {
				state = State::complete;
				window.setFramerateLimit(60);
				*pWorldView = cachedView;
				zoomDegree = 0.999f;
			}
			break;
			
		case State::complete:
			break;
	}
}

void userInterface::addItem(char newItem, effectsController& ef, float xStart, float yStart, FontController& fonts, Player& player) {
	if (newItem == 90) {
		fonts.updateMaxHealth(fonts.getMaxHealth() + 1);
	} else {
		//// TODO
	}
}

void userInterface::dispDeathSeq() {
	if (state == userInterface::State::closed) {
		timer = 0.f;
		state = userInterface::State::deathScreenEntry;
	}
}

bool userInterface::isComplete() {
	return state == State::complete;
}

float userInterface::getBlurAmount() {
	return blurAmount;
}

void userInterface::reset() {
	state = State::closed;
	desaturateAmount = 0.f;
	blurAmount = 0.1f;
}

float userInterface::getDesaturateAmount() {
	return desaturateAmount;
}

bool userInterface::blurEnabled() {
	return blurAmount != 0.1f;
}

bool userInterface::desaturateEnabled() {
	return desaturateAmount > 0.f;
}

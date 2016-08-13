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

#include "userInterface.hpp"
#include <cmath>
#include "player.hpp"

UserInterface::UserInterface() :
	state(State::closed),
	selectorPosition(0),
	timer(0),
	timerAlt(0),
	powerupTimer(0),
	dispPowerupBar(false),
	blurAmount(0.f),
	desaturateAmount(0.f)
{
}

void UserInterface::setView(sf::View * pView) {
	pWorldView = pView;
	cachedView = *pView;
}

bool UserInterface::isOpen() const {
	return state != State::closed;
}

UserInterface::State UserInterface::getState() const {
	return state;
}

void UserInterface::draw(sf::RenderWindow & window, FontController & fonts) {
	switch (state) {
	case State::deathScreenEntry:
		{
			uint8_t textAlpha = desaturateAmount * 255 + 89.25f;
			fonts.drawDeathText(static_cast<unsigned char>(textAlpha), window);
		}
		break;

	case State::menuScreenEntry:
		fonts.setTextAlpha(255 * blurAmount, FontController::Text::resumeText);
		fonts.setTextAlpha(255 * blurAmount, FontController::Text::settingsText);
		fonts.setTextAlpha(255 * blurAmount, FontController::Text::quitText);
		fonts.setTextOffset(0, -0.01 * blurAmount, FontController::Text::resumeText);
		fonts.setTextOffset(0, -0.01 * blurAmount, FontController::Text::settingsText);
		fonts.setTextOffset(0, -0.01 * blurAmount, FontController::Text::quitText);
		break;

	case State::menuScreenExit:
		fonts.setTextAlpha(255 * blurAmount, FontController::Text::resumeText);
		fonts.setTextAlpha(255 * blurAmount, FontController::Text::settingsText);
		fonts.setTextAlpha(255 * blurAmount, FontController::Text::quitText);
		fonts.setTextOffset(0, -0.01 * blurAmount, FontController::Text::resumeText);
		fonts.setTextOffset(0, -0.01 * blurAmount, FontController::Text::settingsText);
		fonts.setTextOffset(0, -0.01 * blurAmount, FontController::Text::quitText);
		break;
		
	case State::deathScreen:
		fonts.drawDeathText(255, window);
		break;

	case State::deathScreenExit:
		{
			uint8_t textAlpha = Easing::easeOut<3>(timer, 300) * 255;
			if (textAlpha > 0) {
				fonts.drawDeathText(textAlpha, window);
			}
		}
		break;

	default:
		break;
	}
}

void UserInterface::resetPowerupBar(Powerup _powerup) {
	dispPowerupBar = true;
	powerup = _powerup;
	powerupTimer = 0;
}

Powerup UserInterface::getCurrentPowerup() const {
	return powerup;
}

void UserInterface::update(Player & player, FontController & fonts, InputController * pInput, const sf::Time & elapsed) {
	bool action = pInput->actionPressed();
	bool up = pInput->upPressed();
	bool down = pInput->downPressed();
	bool pause = pInput->pausePressed();
	switch (state) {
	case State::closed:
		if (dispPowerupBar) {
			const static int64_t powerupTimerCeil = 18000000;
			powerupTimer += elapsed.asMicroseconds();
			float barWidth = Easing::easeOut<1>(powerupTimer, powerupTimerCeil);
			fonts.setBarWidth(barWidth);
			if (powerupTimer > powerupTimerCeil) {
				dispPowerupBar = false;
				powerup = Powerup::nil;
			}
		}
		if (pause) {
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
		blurAmount = Easing::easeIn<3>(timer, 280);
		if (blurAmount == 1.f) {
			state = State::menuScreen;
			fonts.setTextAlpha(255, FontController::Text::resumeText);
			fonts.setTextAlpha(255, FontController::Text::settingsText);
			fonts.setTextAlpha(255, FontController::Text::quitText);
		}
		break;
		
	case State::menuScreen:
		if (pause) {
			timer = 0;
			selectorPosition = 0;
			state = State::menuScreenExit;
		} else if (up) {
			if (selectorPosition > 0) {
				--selectorPosition;
			}
		} else if (down) {
		    if (selectorPosition < 2) {
				++selectorPosition;
			}
		} else if (action) {
			switch (selectorPosition) {
			case 0:
				selectorPosition = 0;
				state = State::menuScreenExit;
				timer = 0;
				break;

			case 1:
				// TODO: settings screen
				break;

			case 2:
				throw ShutdownSignal();
				break;
			}
		}
		break;
		
	case State::menuScreenExit:
		timer += elapsed.asMilliseconds();
		blurAmount = Easing::easeOut<3>(timer, 280);
		if (blurAmount == 0.f) {
			state = State::closed;
			timer = 0;
			player.activate();
			fonts.setTextAlpha(0, FontController::Text::resumeText);
			fonts.setTextAlpha(0, FontController::Text::settingsText);
			fonts.setTextAlpha(0, FontController::Text::quitText);
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
		break;
			
	case State::deathScreen:
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
		blurAmount = Easing::easeIn<3>(timer, 300);
		if (timer >= 300) {
			timer = 0;
			blurAmount = 1.f;
			state = State::statsScreen;
		}
		break;
			
	case State::statsScreen:
		if (action) {
			state = State::complete;
			*pWorldView = cachedView;
		}
		break;
			
	case State::complete:
		break;

	case State::settingsScreen:
		// TODO: Display various settings, go to customization screens...
		// if (...) -> selectorPosition = 0, state := customizeKeyboardScreen
		// if (...) -> selectorposition = 0, state := customizeJoystickScreen
		break;

	case State::customizeKeyboardScreen:
		// TODO: while in this state display text and select each heading accordingly
		break;

	case State::customizeJoystickScreen:
		// TODO: while in this state display text and select each heading accordingly
		break;
	}
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
	blurAmount = 0.f;
	timer = 0;
}

float UserInterface::getDesaturateAmount() {
	return desaturateAmount;
}

bool UserInterface::blurEnabled() {
	return blurAmount != 0.f;
}

bool UserInterface::desaturateEnabled() {
	return desaturateAmount > 0.f;
}

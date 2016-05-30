//
//  inputController.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/10/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "inputController.hpp"
#include <cmath>

InputController::InputController() {
	sf::Joystick::update();
	
	if (sf::Joystick::isConnected(0)) {
		connectedJoystick = true;
	}
}

void InputController::update() {
	if (connectedJoystick) {
		// First get the axis position of the joystick
		float joystickX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		float joystickY = -sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		if (joystickX < 30 && joystickX > -20) {
			joystickX = 0;
		}
		
		if (joystickY < 30 && joystickY > -20) {
			joystickY = 0;
		}
		
		up = false;
		down = false;
		left = false;
		right = false;
		c = false;
		z = false;
		x = false;
		
		if (sf::Joystick::isButtonPressed(0, 9)) {
			c = true;
		}
		
		if (sf::Joystick::isButtonPressed(0, 15)) {
			x = true;
		}
		
		if (sf::Joystick::isButtonPressed(0, 14)) {
			z = true;
		}
		
		if (joystickX != 0 || joystickY != 0) {
			// Now calculate the angle of the joystick based on axis positions
			int angle = (int) (atan2f(joystickY, joystickX) * 180 / 3.14159265);
			if (angle < 0) {
				angle += 360;
			}
			// The player can move in 8 directions, so round the number to the nearest multiple of 45
			angle = ((angle + 45 / 2) / 45) * 45;
			switch (angle) {
				case 0:
					right = true;
					break;
					
				case 360:
					right = true;
					break;
					
				case 45:
					right = true;
					up = true;
					break;
					
				case 90:
					up = true;
					break;
					
				case 135:
					up = true;
					left = true;
					break;
					
				case 180:
					left = true;
					break;
					
				case 225:
					left = true;
					down = true;
					break;
					
				case 270:
					down = true;
					break;
					
				case 315:
					down = true;
					right = true;
					break;
					
				default:
					break;
			}
		}
	}
	
	else {
		// Check for keyboard inputs
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			left = true;
		}
		else {
			left = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			right = true;
		}
		else {
			right = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			up = true;
		}
		else {
			up = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			down = true;
		}
		else {
			down = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			x = true;
		}
		else {
			x = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			z = true;
		}
		else {
			z = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
			c = true;
		}
		else {
			c = false;
		}
	}
}

bool InputController::xPressed() const {
	return x;
}

bool InputController::zPressed() const {
	return z;
}

bool InputController::leftPressed() const {
	return left;
}

bool InputController::rightPressed() const {
	return right;
}

bool InputController::upPressed() const {
	return up;
}

bool InputController::downPressed() const {
	return down;
}

bool InputController::cPressed() const {
	return c;
}

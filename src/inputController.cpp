//
//  inputController.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/10/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "inputController.hpp"
#include <cmath>

InputController::InputController()
	: left{false},
	  right{false},
	  up{false},
	  down{false},
	  x{false},
	  z{false},
	  c{false}
{}

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

void InputController::update(sf::RenderWindow & window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::KeyPressed) {
			switch(event.key.code) {
			case sf::Keyboard::Escape:
				window.close();
				break;

			case sf::Keyboard::Left:
				left = true;
				break;

			case sf::Keyboard::Right:
				right = true;
				break;

			case sf::Keyboard::Up:
				up = true;
				break;

			case sf::Keyboard::Down:
				down = true;
				break;

			case sf::Keyboard::X:
				x = true;
				break;

			case sf::Keyboard::Z:
				z = true;
				break;

			case sf::Keyboard::C:
				c = true;
				break;

			default:
				break;
			}
		} else if (event.type == sf::Event::KeyReleased) {
			switch(event.key.code) {
			case sf::Keyboard::Left:
				left = false;
				break;

			case sf::Keyboard::Right:
				right = false;
				break;

			case sf::Keyboard::Up:
				up = false;
				break;

			case sf::Keyboard::Down:
				down = false;
				break;

			case sf::Keyboard::X:
				x = false;
				break;

			case sf::Keyboard::Z:
				z = false;
				break;

			case sf::Keyboard::C:
				c = false;
				break;

			default:
				break;
			}
		}
	}
}

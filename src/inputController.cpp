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

#include "inputController.hpp"
#include <cmath>
#include <iostream>

InputController::InputController()
	: left{false},
	  right{false},
	  up{false},
	  down{false},
	  x{false},
	  z{false},
	  c{false},
	  focused{true},
	  escape{false}
{}

bool InputController::isFocused() const {
	return focused;
}

bool InputController::escapePressed() const {
	return escape;
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

void InputController::update(sf::RenderWindow & window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		} else if (event.type == sf::Event::KeyPressed) {
			switch(event.key.code) {
			case sf::Keyboard::Escape:
			    escape = true;
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
			case sf::Keyboard::Escape:
				escape = false;
				break;
				
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
		} else if (event.type == sf::Event::GainedFocus) {
			focused = true;
		} else if (event.type == sf::Event::LostFocus) {
			focused = false;
		} else if (event.type == sf::Event::JoystickButtonPressed) {
			// TODO
		} else if (event.type == sf::Event::JoystickButtonReleased) {
			// TODO
		} else if (event.type == sf::Event::JoystickMoved) {
			// TODO
		}
	}
}

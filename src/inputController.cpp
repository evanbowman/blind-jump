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
	: keyMask{0},
	  joystickMask{0},
	  joystickXMap{15},
	  joystickZMap{14},
	  joystickCMap{9},
	  joystickEscMap{3}
{
	init();
}

void InputController::init() {
	// Load joystick config file
}

bool InputController::isFocused() const {
	return keyMask & 0x0080 || joystickMask & 0x0080;
}

bool InputController::escapePressed() const {
	return keyMask & 0x0100 || joystickMask & 0x0100;
}

bool InputController::xPressed() const {
	return keyMask & 0x0010 || joystickMask & 0x0010;
}

bool InputController::zPressed() const {
	return keyMask & 0x0020 || joystickMask & 0x0020;
}

bool InputController::leftPressed() const {
	return keyMask & 0x0001 || joystickMask & 0x0001;
}

bool InputController::rightPressed() const {
	return keyMask & 0x0002 || joystickMask & 0x0002;
}

bool InputController::upPressed() const {
	return keyMask & 0x0004 || joystickMask & 0x0004;
}

bool InputController::downPressed() const {
	return keyMask & 0x0008 || joystickMask & 0x0008;
}

bool InputController::cPressed() const {
	return keyMask & 0x0040 || joystickMask & 0x0040;
}

void InputController::update(sf::RenderWindow & window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		} else if (event.type == sf::Event::KeyPressed) {
			switch(event.key.code) {
			case sf::Keyboard::Escape:
			    keyMask |= 0x0100;
				break;

			case sf::Keyboard::Left:
				keyMask |= 0x0001;
				break;

			case sf::Keyboard::Right:
				keyMask |= 0x0002;
				break;

			case sf::Keyboard::Up:
				keyMask |= 0x0004;
				break;

			case sf::Keyboard::Down:
				keyMask |= 0x0008;
				break;

			case sf::Keyboard::X:
				keyMask |= 0x0010;
				break;

			case sf::Keyboard::Z:
				keyMask |= 0x0020;
				break;

			case sf::Keyboard::C:
				keyMask |= 0x0040;
				break;

			default:
				break;
			}
		} else if (event.type == sf::Event::KeyReleased) {
			switch(event.key.code) {
			case sf::Keyboard::Escape:
				keyMask &= 0xFEFF;
				break;
				
			case sf::Keyboard::Left:
				keyMask &= 0xFFFE;
				break;

			case sf::Keyboard::Right:
				keyMask &= 0xFFFD;
				break;

			case sf::Keyboard::Up:
				keyMask &= 0xFFFB;
				break;

			case sf::Keyboard::Down:
				keyMask &= 0xFFF7;
				break;

			case sf::Keyboard::X:
				keyMask &= 0xFFEF;
				break;

			case sf::Keyboard::Z:
				keyMask &= 0xFFDF;
				break;

			case sf::Keyboard::C:
				keyMask &= 0xFFBF;
				break;

			default:
				break;
			}
		} else if (event.type == sf::Event::GainedFocus) {
			keyMask |= 0x0080;
		} else if (event.type == sf::Event::LostFocus) {
			keyMask &= 0xFF7F;
		} else if (event.type == sf::Event::JoystickButtonPressed) {
			if (event.joystickButton.joystickId == 0) {
				if (event.joystickButton.button == joystickXMap) {
					joystickMask |= 0x0010;
				} else if (event.joystickButton.button == joystickZMap) {
					joystickMask |= 0x0020;
				} else if (event.joystickButton.button == joystickCMap) {
					joystickMask |= 0x0040;
				} else if (event.joystickButton.button == joystickEscMap) {
					joystickMask |= 0x0100;
				}
			}
		} else if (event.type == sf::Event::JoystickButtonReleased) {
			if (event.joystickButton.joystickId == 0) {
				if (event.joystickButton.button == joystickXMap) {
					joystickMask &= 0xFFEF;
				} else if (event.joystickButton.button == joystickZMap) {
					joystickMask &= 0xFFDF;
				} else if (event.joystickButton.button == joystickCMap) {
					joystickMask &= 0xFFBF;
				} else if (event.joystickButton.button == joystickEscMap) {
					joystickMask &= 0xFEFF;
				}
			}
		} else if (event.type == sf::Event::JoystickMoved) {
 			if (event.joystickMove.axis == sf::Joystick::Axis::X) {
				float position = event.joystickMove.position;
				if (position > 30) {
 					joystickMask &= 0xFFFE;
					joystickMask |= 0x0002;
				} else if (position < -30) {
					joystickMask &= 0xFFFD;
					joystickMask |= 0x0001;
				} else {
					joystickMask &= 0xFFFC;
				}
			} else if (event.joystickMove.axis == sf::Joystick::Axis::Y) {
				float position = event.joystickMove.position;
				if (position < -30) {
					joystickMask &= 0xFFF7;
					joystickMask |= 0x0004;
				} else if (position > 30) {
					joystickMask &= 0xFFFB;
					joystickMask |= 0x0008;
				} else {
					joystickMask &= 0xFFF3;
				}
			}
		} else if (event.type == sf::Event::JoystickConnected) {
			if (event.joystickConnect.joystickId == 0) {
				sf::Joystick::Identification joystickInfoStruct = sf::Joystick::getIdentification(0);
				// Use the joystick info to load the proper configuration
			}
		}
	}
}

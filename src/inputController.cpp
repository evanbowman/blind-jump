//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "inputController.hpp"
#include <cmath>
#include <iostream>

InputController::InputController()
	: keyMask{0},
	  joystickMask{0}, 
	  keyboardMappings{
		  { sf::Keyboard::X,
		    sf::Keyboard::Z,
		    sf::Keyboard::Escape,
		    sf::Keyboard::Left,
		    sf::Keyboard::Right,
		    sf::Keyboard::Up,
			sf::Keyboard::Down }
	  }
{
	if (sf::Joystick::isConnected(0)) {
		mapJsById();
	}
}

void InputController::mapJsById() {
	enum Vendor {
		Sony = 0x054C,
		Microsoft = 0x045E
	};
	enum Product {
		PS3Controller = 0x0268,
		PS4Controller = 0x05C4,
		XBOneController = 0x02D1
	};
	sf::Joystick::Identification ident = sf::Joystick::getIdentification(0);
	if (ident.vendorId == Sony && ident.productId == PS3Controller) {
		joystickMappings[ButtonShoot] = 11;
		joystickMappings[ButtonAction] = 14;
		joystickMappings[ButtonPause] = 16;
	} else if (ident.vendorId == Sony && ident.productId == PS4Controller) {
		joystickMappings[ButtonShoot] = 5;
		joystickMappings[ButtonAction] = 1;
		joystickMappings[ButtonPause] = 12;
	} else if (ident.vendorId == Microsoft && ident.productId == XBOneController) {
		// TODO: Test XBOne Controller
	} else {
		joystickMappings[ButtonShoot] = 0;
		joystickMappings[ButtonAction] = 1;
		joystickMappings[ButtonPause] = 2;
	}
}

void InputController::mapKeyboardKey(sf::Keyboard::Key key, uint8_t indx) {
	keyboardMappings[indx] = key;
}

void InputController::mapJoystickButton(uint32_t button, uint8_t indx) {
	joystickMappings[indx] = button;
}

bool InputController::isFocused() const {
	return keyMask & 0x0080;
}

bool InputController::pausePressed() const {
	return keyMask & 0x0100 || joystickMask & 0x0100;
}

bool InputController::shootPressed() const {
	return keyMask & 0x0010 || joystickMask & 0x0010;
}

bool InputController::actionPressed() const {
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

void InputController::update(sf::RenderWindow & window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
			throw ShutdownSignal();
		} else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == keyboardMappings[ButtonPause]) {
				keyMask |= 0x0100;
			} else if (event.key.code == keyboardMappings[ButtonLeft]) {
				keyMask |= 0x0001;
			} else if (event.key.code == keyboardMappings[ButtonRight]) {
				keyMask |= 0x0002;
			} else if (event.key.code == keyboardMappings[ButtonUp]) {
				keyMask |= 0x0004;
			} else if (event.key.code == keyboardMappings[ButtonDown]) {
				keyMask |= 0x0008;
			} else if (event.key.code == keyboardMappings[ButtonShoot]) {
				keyMask |= 0x0010;
			} else if (event.key.code == keyboardMappings[ButtonAction]) {
				keyMask |= 0x0020;
			}
		} else if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == keyboardMappings[ButtonPause]) {
				keyMask &= 0xFEFF;
			} else if (event.key.code == keyboardMappings[ButtonLeft]) {
				keyMask &= 0xFFFE;
			} else if (event.key.code == keyboardMappings[ButtonRight]) {
				keyMask &= 0xFFFD;
			} else if (event.key.code == keyboardMappings[ButtonUp]) {
				keyMask &= 0xFFFB;
			} else if (event.key.code == keyboardMappings[ButtonDown]) {
				keyMask &= 0xFFF7;
			} else if (event.key.code == keyboardMappings[ButtonShoot]) {
				keyMask &= 0xFFEF;
			} else if (event.key.code == keyboardMappings[ButtonAction]) {
				keyMask &= 0xFFDF;
			}
		} else if (event.type == sf::Event::GainedFocus) {
			keyMask |= 0x0080;
		} else if (event.type == sf::Event::LostFocus) {
			keyMask &= 0xFF7F;
		} else if (event.type == sf::Event::JoystickButtonPressed) {
			if (event.joystickButton.joystickId == 0) {
				if (event.joystickButton.button == joystickMappings[ButtonShoot]) {
					joystickMask |= 0x0010;
				} else if (event.joystickButton.button == joystickMappings[ButtonAction]) {
					joystickMask |= 0x0020;
				} else if (event.joystickButton.button == joystickMappings[ButtonPause]) {
					joystickMask |= 0x0100;
				}
			}
		} else if (event.type == sf::Event::JoystickButtonReleased) {
			if (event.joystickButton.joystickId == 0) {
				if (event.joystickButton.button == joystickMappings[ButtonShoot]) {
					joystickMask &= 0xFFEF;
				} else if (event.joystickButton.button == joystickMappings[ButtonAction]) {
					joystickMask &= 0xFFDF;
				} else if (event.joystickButton.button == joystickMappings[ButtonPause]) {
					joystickMask &= 0xFEFF;
				}
			}
		} else if (event.type == sf::Event::JoystickMoved) {
			static const int deadZone = 30;
			if (event.joystickMove.axis == sf::Joystick::Axis::X) {
				float position = event.joystickMove.position;
				if (position > deadZone) {
 					joystickMask &= 0xFFFE;
					joystickMask |= 0x0002;
				} else if (-position > deadZone) {
					joystickMask &= 0xFFFD;
					joystickMask |= 0x0001;
				} else {
					joystickMask &= 0xFFFC;
				}
			} else if (event.joystickMove.axis == sf::Joystick::Axis::Y) {
				float position = event.joystickMove.position;
				if (-position > deadZone) {
					joystickMask &= 0xFFF7;
					joystickMask |= 0x0004;
				} else if (position > deadZone) {
					joystickMask &= 0xFFFB;
					joystickMask |= 0x0008;
				} else {
					joystickMask &= 0xFFF3;
				}
			}
		} else if (event.type == sf::Event::JoystickConnected) {
			if (event.joystickConnect.joystickId == 0) {
				this->mapJsById();
				joystickMask = 0x0000;
			}
		} else if (event.type == sf::Event::JoystickDisconnected) {
			if (event.joystickConnect.joystickId == 0) {
				joystickMask = 0x0000; // In case buttons pressed when disconnected
			}
		}
	}
}

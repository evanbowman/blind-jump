#include "inputController.hpp"
#include <cmath>
#include <iostream>

static std::unordered_map<std::string, sf::Keyboard::Key> translator {
    {"esc", sf::Keyboard::Escape},
    {"up", sf::Keyboard::Up},
    {"down", sf::Keyboard::Down},
    {"left", sf::Keyboard::Left},
    {"right", sf::Keyboard::Right},
    {"a", sf::Keyboard::A},
    {"b", sf::Keyboard::B},
    {"c", sf::Keyboard::C},
    {"d", sf::Keyboard::D},
    {"e", sf::Keyboard::E},
    {"f", sf::Keyboard::F},
    {"g", sf::Keyboard::G},
    {"h", sf::Keyboard::H},
    {"i", sf::Keyboard::I},
    {"j", sf::Keyboard::J},
    {"k", sf::Keyboard::K},
    {"l", sf::Keyboard::L},
    {"m", sf::Keyboard::M},
    {"n", sf::Keyboard::N},
    {"o", sf::Keyboard::O},
    {"p", sf::Keyboard::P},
    {"q", sf::Keyboard::Q},
    {"r", sf::Keyboard::R},
    {"s", sf::Keyboard::S},
    {"t", sf::Keyboard::T},
    {"u", sf::Keyboard::U},
    {"v", sf::Keyboard::V},
    {"w", sf::Keyboard::W},
    {"x", sf::Keyboard::X},
    {"y", sf::Keyboard::Y},
    {"z", sf::Keyboard::Z}
};

static sf::Keyboard::Key toSfKey(const std::string & strKey) {
    return ::translator[strKey];
}

InputController::InputController(nlohmann::json & config) {
    try {
	auto it = config.find("Keyboard");
	const auto mapKey = [this, it](const int keyIndex, const char * jsonStr) {
				keyboardMappings[keyIndex] =
				    toSfKey(it->find(jsonStr)->get<std::string>());
			    };
	mapKey(indexShoot, "Shoot");
	mapKey(indexAction, "Action");
	mapKey(indexPause, "Pause");
	mapKey(indexLeft, "Left");
	mapKey(indexRight, "Right");
	mapKey(indexUp, "Up");
	mapKey(indexDown, "Down");
    } catch (const std::exception & ex) {
	throw std::runtime_error("JSON error: " + std::string(ex.what()));
    }
    if (sf::Joystick::isConnected(0)) {
        mapJsById();
    }
}

void InputController::mapJsById() {
    // TODO: move this metadata stuff to JSON config files?
    enum Vendor { Sony = 0x054C, Microsoft = 0x045E };
    enum Product {
        PS3Controller = 0x0268,
        PS4Controller = 0x05C4,
        XBOneController = 0x02D1
    };
    sf::Joystick::Identification ident = sf::Joystick::getIdentification(0);
    if (ident.vendorId == Sony && ident.productId == PS3Controller) {
        joystickMappings[indexShoot] = 11;
        joystickMappings[indexAction] = 14;
        joystickMappings[indexPause] = 16;
    } else if (ident.vendorId == Sony && ident.productId == PS4Controller) {
        joystickMappings[indexShoot] = 5;
        joystickMappings[indexAction] = 1;
        joystickMappings[indexPause] = 12;
    } else if (ident.vendorId == Microsoft &&
               ident.productId == XBOneController) {
        // TODO: Test XBOne Controller
    } else {
        joystickMappings[indexShoot] = 0;
        joystickMappings[indexAction] = 1;
        joystickMappings[indexPause] = 2;
    }
}

void InputController::mapKeyboardKey(const sf::Keyboard::Key key,
                                     const uint8_t indx) {
    keyboardMappings[indx] = key;
}

void InputController::mapJoystickButton(const uint32_t button,
                                        const uint8_t indx) {
    joystickMappings[indx] = button;
}

bool InputController::pausePressed() const {
    return keyMask[indexPause] || joystickMask[indexPause];
}

bool InputController::shootPressed() const {
    return keyMask[indexShoot] || joystickMask[indexShoot];
}

bool InputController::actionPressed() const {
    return keyMask[indexAction] || joystickMask[indexAction];
}

bool InputController::leftPressed() const {
    return keyMask[indexLeft] || joystickMask[indexLeft];
}

bool InputController::rightPressed() const {
    return keyMask[indexRight] || joystickMask[indexRight];
}

bool InputController::upPressed() const {
    return keyMask[indexUp] || joystickMask[indexUp];
}

bool InputController::downPressed() const {
    return keyMask[indexDown] || joystickMask[indexDown];
}

void InputController::recordEvent(const sf::Event & event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == keyboardMappings[indexPause]) {
            keyMask[indexPause] = true;
        } else if (event.key.code == keyboardMappings[indexLeft]) {
            keyMask[indexLeft] = true;
        } else if (event.key.code == keyboardMappings[indexRight]) {
            keyMask[indexRight] = true;
        } else if (event.key.code == keyboardMappings[indexUp]) {
            keyMask[indexUp] = true;
        } else if (event.key.code == keyboardMappings[indexDown]) {
            keyMask[indexDown] = true;
        } else if (event.key.code == keyboardMappings[indexShoot]) {
            keyMask[indexShoot] = true;
        } else if (event.key.code == keyboardMappings[indexAction]) {
            keyMask[indexAction] = true;
        }
    } else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == keyboardMappings[indexPause]) {
            keyMask[indexPause] = false;
        } else if (event.key.code == keyboardMappings[indexLeft]) {
            keyMask[indexLeft] = false;
        } else if (event.key.code == keyboardMappings[indexRight]) {
            keyMask[indexRight] = false;
        } else if (event.key.code == keyboardMappings[indexUp]) {
            keyMask[indexUp] = false;
        } else if (event.key.code == keyboardMappings[indexDown]) {
            keyMask[indexDown] = false;
        } else if (event.key.code == keyboardMappings[indexShoot]) {
            keyMask[indexShoot] = false;
        } else if (event.key.code == keyboardMappings[indexAction]) {
            keyMask[indexAction] = false;
        }
    } else if (event.type == sf::Event::JoystickButtonPressed) {
        if (event.joystickButton.joystickId == 0) {
            if (event.joystickButton.button == joystickMappings[indexShoot]) {
                joystickMask[indexShoot] = true;
            } else if (event.joystickButton.button ==
                       joystickMappings[indexAction]) {
                joystickMask[indexAction] = true;
            } else if (event.joystickButton.button ==
                       joystickMappings[indexPause]) {
                joystickMask[indexPause] = true;
            }
        }
    } else if (event.type == sf::Event::JoystickButtonReleased) {
        if (event.joystickButton.joystickId == 0) {
            if (event.joystickButton.button == joystickMappings[indexShoot]) {
                joystickMask[indexShoot] = false;
            } else if (event.joystickButton.button ==
                       joystickMappings[indexAction]) {
                joystickMask[indexAction] = false;
            } else if (event.joystickButton.button ==
                       joystickMappings[indexPause]) {
                joystickMask[indexPause] = false;
            }
        }
    } else if (event.type == sf::Event::JoystickMoved) {
        static const int deadZone = 30;
        if (event.joystickMove.axis == sf::Joystick::Axis::X) {
            float position = event.joystickMove.position;
            if (position > deadZone) {
                joystickMask[indexRight] = true;
                joystickMask[indexLeft] = false;
            } else if (-position > deadZone) {
                joystickMask[indexLeft] = true;
                joystickMask[indexRight] = false;
            } else {
                joystickMask[indexLeft] = false;
                joystickMask[indexRight] = false;
            }
        } else if (event.joystickMove.axis == sf::Joystick::Axis::Y) {
            float position = event.joystickMove.position;
            if (-position > deadZone) {
                joystickMask[indexUp] = true;
                joystickMask[indexDown] = false;
            } else if (position > deadZone) {
                joystickMask[indexDown] = true;
                joystickMask[indexUp] = false;
            } else {
                joystickMask[indexDown] = false;
                joystickMask[indexUp] = false;
            }
        }
    } else if (event.type == sf::Event::JoystickConnected) {
        if (event.joystickConnect.joystickId == 0) {
            this->mapJsById();
            joystickMask.reset();
        }
    } else if (event.type == sf::Event::JoystickDisconnected) {
        if (event.joystickConnect.joystickId == 0) {
            joystickMask.reset();
        }
    }
}

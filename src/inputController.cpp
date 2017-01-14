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
	for (it = config.find("Joystick")->begin();
	     it != config.find("Joystick")->end(); ++it) {
	    JoystickInfo info;
	    info.vendorId = it->find("VendorId")->get<int>();
	    info.productId = it->find("ProductId")->get<int>();
	    auto jsBtnMappings = it->find("ButtonMappings");
	    info.shoot = jsBtnMappings->find("Shoot")->get<int>();
	    info.action = jsBtnMappings->find("Action")->get<int>();
	    info.pause = jsBtnMappings->find("Pause")->get<int>();
	    this->joysticks.push_back(info);
	}
	it = config.find("Joystick")->begin();
    } catch (const std::exception & ex) {
	throw std::runtime_error("JSON error: " + std::string(ex.what()));
    }
    if (sf::Joystick::isConnected(0)) {
        remapJoystick();
    }
}

void InputController::remapJoystick() {
    sf::Joystick::Identification ident = sf::Joystick::getIdentification(0);
    for (auto & jsInfo : joysticks) {
	if (jsInfo.vendorId == ident.vendorId &&
	    jsInfo.productId == ident.productId) {
	    joystickMappings[indexShoot] = jsInfo.shoot;
	    joystickMappings[indexAction] = jsInfo.action;
	    joystickMappings[indexPause] = jsInfo.pause;
	}
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
            this->remapJoystick();
            joystickMask.reset();
        }
    } else if (event.type == sf::Event::JoystickDisconnected) {
        if (event.joystickConnect.joystickId == 0) {
            joystickMask.reset();
        }
    }
}

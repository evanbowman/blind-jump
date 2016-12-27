#include "inputController.hpp"
#include <cmath>
#include <iostream>

InputController::InputController() : m_keyStates{{}} {}

void InputController::recordEvent(const sf::Event & event) {
    switch (event.type) {
    case sf::Event::KeyPressed:
	m_keyStates[event.key.code] = 1;
	break;
	
    case sf::Event::KeyReleased:
	m_keyStates[event.key.code] = 0;
	break;
    }
}

int InputController::getKeyState(const int which) const {
    return m_keyStates[which];
}

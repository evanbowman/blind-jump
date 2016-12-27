//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "inputController.hpp"
#include <cmath>
#include <iostream>

InputController::InputController() {}

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

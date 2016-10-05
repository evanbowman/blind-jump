//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <SFML/Graphics.hpp>
#include "shutdownSignal.hpp"
#include <array>

class InputController {
public:
	enum Button {
		ButtonShoot,
		ButtonAction,
		ButtonPause,
		ButtonLeft,
		ButtonRight,
		ButtonUp,
		ButtonDown
	};
	InputController();
	void mapJsById();
	bool isFocused() const;
	bool pausePressed() const;
	bool leftPressed() const;
	bool rightPressed() const;
	bool upPressed() const;
	bool downPressed() const;
	bool shootPressed() const;
	bool actionPressed() const;
	void update(sf::RenderWindow &);
	void mapKeyboardKey(sf::Keyboard::Key, uint8_t);
	void mapJoystickButton(uint32_t, uint8_t);
	
private:
	uint32_t keyMask;
	uint32_t joystickMask;
	std::array<uint32_t, 3> joystickMappings;
	std::array<sf::Keyboard::Key, 7> keyboardMappings;
};

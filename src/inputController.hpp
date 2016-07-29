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

#pragma once

#include <SFML/Graphics.hpp>
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
	void mapJoystickFromId();
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
	void mapJoystickButton(unsigned int, uint8_t);
	
private:
	uint32_t keyMask;
	uint32_t joystickMask;
	std::array<unsigned int, 3> joystickMappings;
	std::array<sf::Keyboard::Key, 7> keyboardMappings;
};

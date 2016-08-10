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

#include <SFML/Audio.hpp>
#include <vector>
#include <deque>
#include "resourceHandler.hpp"

class SoundController {
public:
	explicit SoundController(ResourceHandler * _pRH) : pRH(_pRH) {}
	// The function that updates the sound controller is called poll and
	// not update because it does not run in the game's update function
	// like a lot of the other controller code. Some operating systems
	// require graphics and sound related stuff to happen on the main
	// thread, it may not be necessary, but just to be safe...
	void poll();
	void play(ResourceHandler::Music);
	void play(ResourceHandler::Sound);

private:
	ResourceHandler * pRH;
	std::vector<sf::Sound> sounds;
	std::vector<ResourceHandler::Sound> soundIdxQueue;
};

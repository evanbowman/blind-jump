//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include <deque>
#include "resourceHandler.hpp"

class SoundController {
public:
	// The function that updates the sound controller is called poll and
	// not update because it does not run in the game's update function
	// like a lot of the other controller code. Some operating systems
	// require graphics and sound related stuff to happen on the main
	// thread, it may not be necessary, but just to be safe...
	void poll();
	void play(ResHandler::Music);
	void play(ResHandler::Sound);

private:
	std::vector<sf::Sound> sounds;
	std::vector<ResHandler::Sound> soundIdxQueue;
};

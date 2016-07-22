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

#include "SFML/Audio.hpp"
#include <array>

class SoundController {
private:
	// Effect sounds
	std::array<sf::SoundBuffer, 1> laserSounds;
	std::array<sf::SoundBuffer, 1> stepEffects;
	std::array<sf::SoundBuffer, 2> machineSounds;
	std::array<sf::Sound, 3> sounds;
	int currentSong;
	
public:
	enum class Effect {
		step,
		gunshot,
		coin
	};
	
	SoundController();
	// Game objects can pass a value to the music controller to
	void playEffect(Effect);
	void playMusic(unsigned char);
	void stopMusic();
};

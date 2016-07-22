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

#include "soundController.hpp"
#include "ResourcePath.hpp"
#include <cmath>
#include "SFML/Graphics.hpp"

SoundController::SoundController() {
	
	// Load the soundtrack and play the first song
	//soundtrack[0].openFromFile(resourcePath() + "julia-florida.ogg"); /* Composed by Augustin Barrios Mangore, performed by Edson Lopez */
	//soundtrack[0].setLoop(true);
	//soundtrack[1].openFromFile(resourcePath() + "deep_blue_sea_blues.ogg");
	//soundtrack[2].openFromFile(resourcePath() + "mister_moon_man.ogg");
	
	// Load effects
	stepEffects[0].loadFromFile(resourcePath() + "step.wav");
	stepEffects[1].loadFromFile(resourcePath() + "grassStep.ogg");
	laserSounds[0].loadFromFile(resourcePath() + "laser.wav");
}

void SoundController::playMusic(unsigned char musicIndex) {
	/*for (int i = 0; i < SOUNDTRACK_LENGTH; i++) {
		// Stop all the other songs
		soundtrack[i].stop();
	}
	// Play the selected one
	soundtrack[musicIndex].play();*/
}

void SoundController::playEffect(SoundController::Effect index) {
	sf::Sound sound;
	switch (index) {
		case SoundController::Effect::step:
			sounds[0].setBuffer(stepEffects[0]);
			sounds[0].setVolume(40);
			sounds[0].play();
			break;
			
		case SoundController::Effect::gunshot:
			sounds[1].setBuffer(laserSounds[0]);
			sounds[1].setVolume(80);
			sounds[1].play();
			break;
			
		case SoundController::Effect::coin:
			//sounds[2].setBuffer(<#const sf::SoundBuffer &buffer#>);
			break;
			
		default:
			//std::cerr << "Unexpected effect index in playEffect" << std::endl;
			break;
	}
}

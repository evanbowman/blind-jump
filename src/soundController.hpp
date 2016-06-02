//
//  musicController.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/28/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef soundController_hpp
#define soundController_hpp

#include <stdio.h>
#include "sfml/audio.hpp"
#include <array>

class SoundController {
private:
	static constexpr int SOUNDTRACK_LENGTH = 3;
	// Game soundtrack
	sf::Music soundtrack[SOUNDTRACK_LENGTH];
	
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

#endif /* musicController_hpp */

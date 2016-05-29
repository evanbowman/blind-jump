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

static constexpr int SOUNDTRACK_LENGTH = 3;

class SoundController {
private:    
    // Game soundtrack
    sf::Music soundtrack[SOUNDTRACK_LENGTH];
    
    // Effect sounds
    std::array<sf::SoundBuffer, 1> laserSounds;
    std::array<sf::SoundBuffer, 1> stepEffects;
    std::array<sf::SoundBuffer, 2> machineSounds;
    sf::Sound sounds[4];
    int currentSong;
    
public:
    SoundController();
    // Game objects can pass a value to the music controller to
    void playEffect(unsigned char);
    void playMusic(unsigned char);
    void stopMusic();
};

#endif /* musicController_hpp */

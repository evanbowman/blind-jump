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

#define SOUNDTRACK_LENGTH 3

class SoundController {
private:    
    // Game soundtrack
    sf::Music soundtrack[SOUNDTRACK_LENGTH];
    
    // Effect sounds
    sf::SoundBuffer laserSounds[1];
    sf::SoundBuffer stepEffects[2];
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

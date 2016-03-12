//
//  musicController.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/28/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef soundController_hpp
#define soundController_hpp

#include <stdio.h>
#include "sfml/audio.hpp"

#define SOUNDTRACK_LENGTH 3

class SoundController {
private:
    // Ambient background music for the game
    /* Ambient music plays all the time, but the soundtrack plays depending
     on the player's distance from a sound source*/
    sf::Music ambientBkg;
    
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
    void updateSoundtrack(float, float, float, float);
    void stopMusic();
};

#endif /* musicController_hpp */

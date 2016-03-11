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

class SoundController {
private:
    // Ambient background music for the game
    sf::Music ambientBkg;
    
    // Effect sounds
    sf::SoundBuffer stepEffects[2];
    sf::Sound sound;

    
public:
    SoundController();
    // Game objects can pass a value to the music controller to
    void playEffect(unsigned char);
    void playMusic(unsigned char);
    void stopMusic();
};

#endif /* musicController_hpp */

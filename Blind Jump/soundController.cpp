//
//  musicController.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/28/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "soundController.hpp"
#include "ResourcePath.hpp"
#include <iostream>

SoundController::SoundController() {
    // Load game music
    ambientBkg.openFromFile(resourcePath() + "cylinder_five.ogg");
    // Set the music to loop
    ambientBkg.setLoop(true);
    ambientBkg.setVolume(20);
    
    // Load effects
    stepEffects[0].loadFromFile(resourcePath() + "step.wav");
    stepEffects[1].loadFromFile(resourcePath() + "step2.wav");
}

void SoundController::playMusic(unsigned char musicIndex) {
    switch (musicIndex) {
        case 0:
            ambientBkg.play();
            break;
            
        default:
            // Don't play any sounds
            break;
    }
}

void SoundController::playEffect(unsigned char effectIndex) {
    switch (effectIndex) {
        case 0:
            //sound.setBuffer(stepEffects[0]);
            //sound.setVolume(68);
            //sound.play();
            break;
            
        default:
            break;
    }
}
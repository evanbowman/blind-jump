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
#include <cmath>
#include "SFML/Graphics.hpp"

SoundController::SoundController() {
    // Load game music
    ambientBkg.openFromFile(resourcePath() + "cylinder_five.ogg");
    // Set the music to loop
    //ambientBkg.setLoop(true);
    //ambientBkg.setVolume(10);
    
    // Load the soundtrack and play the first song
    soundtrack[0].openFromFile(resourcePath() + "poor_me_blues.ogg");
    soundtrack[1].openFromFile(resourcePath() + "deep_blue_sea_blues.ogg");
    soundtrack[2].openFromFile(resourcePath() + "mister_moon_man.ogg");
    currentSong = rand() % SOUNDTRACK_LENGTH;
    //soundtrack[currentSong].play();
    
    // Load effects
    stepEffects[0].loadFromFile(resourcePath() + "step.wav");
    stepEffects[1].loadFromFile(resourcePath() + "grassStep.ogg");
    laserSounds[0].loadFromFile(resourcePath() + "laser.wav");
}

void SoundController::playMusic(unsigned char musicIndex) {
    switch (musicIndex) {
        case 0:
            //ambientBkg.play();
            break;
            
        default:
            // Don't play any sounds
            break;
    }
}

void SoundController::updateSoundtrack(float playerPosX, float playerPosY, float sourceX, float sourceY) {
    /*float distance = sqrtf((playerPosX - sourceX) * (playerPosX - sourceX) + (playerPosY - sourceY) * (playerPosY - sourceY));
    float volume = 100 - sqrt(distance) * 4;
    if (volume < 0) {
        volume = 0;
    }
    ambientBkg.setVolume(fmax(60 - volume, 0));
    soundtrack[currentSong].setVolume(volume);
    if (soundtrack[currentSong].getStatus() == sf::SoundSource::Status::Stopped) {
        currentSong++;
        if (currentSong > SOUNDTRACK_LENGTH - 1) {
            currentSong = 0;
        }
        soundtrack[currentSong].play();
    }*/
}

void SoundController::playEffect(unsigned char effectIndex) {
    sf::Sound sound;
    switch (effectIndex) {
        case 0:
            sounds[0].setBuffer(stepEffects[0]);
            sounds[0].setVolume(40);
            sounds[0].play();
            break;
            
        case 1:
            sounds[1].setBuffer(laserSounds[0]);
            sounds[1].setVolume(80);
            sounds[1].play();
            break;
            
        case 2:
            sounds[0].setBuffer(stepEffects[1]);
            sounds[0].setVolume(80);
            sounds[0].play();
            break;
            
        default:
            break;
    }
}
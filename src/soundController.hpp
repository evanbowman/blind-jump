//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "resourceHandler.hpp"
#include <SFML/Audio.hpp>
#include <queue>
#include <vector>

class SoundController {
public:
    // The function that updates the sound controller is called poll and
    // not update because it does not run in the game's update function
    // like a lot of the other controller code. Some operating systems
    // require graphics and sound related stuff to happen on the main
    // thread, it may not be necessary, but just to be safe...
    void update();
    void play(ResHandler::Sound);
    
private:
    std::mutex soundsGuard;
    sf::Music currentSong;
    std::queue<sf::Sound> sounds;
    std::vector<ResHandler::Sound> soundIdQueue;
};

//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "resourceHandler.hpp"
#include <SFML/Audio.hpp>
#include <queue>
#include <vector>

struct reqInfo {
    ResHandler::Sound soundIdx;
    sf::Vector3f position;
    float minDistance;
    float attenuation;
    bool relative;
};

class SoundController {
public:
    void update();
    void play(ResHandler::Sound indx,
              const sf::Vector3f & position = {0.f, 0.f, 0.f},
              float minDistance = 1.f, float attenuation = 0.f,
              bool relative = true);

private:
    std::mutex soundsGuard;
    sf::Music currentSong;
    std::queue<sf::Sound> runningSounds;
    std::vector<reqInfo> soundRequests;
};

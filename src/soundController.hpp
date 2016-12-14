//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "resourceHandler.hpp"
#include <SFML/Audio.hpp>
#include <list>
#include <vector>
#include <memory>
#include "framework/framework.hpp"

struct reqInfo {
    ResHandler::Sound soundIdx;
    float minDistance;
    float attenuation;
    bool spatialized;
    std::weak_ptr<framework::Object> source;
};

struct runningData {
    std::weak_ptr<framework::Object> source;
    bool spatialized;
};

class SoundController {
public:
    void update();
    void play(ResHandler::Sound);
    void play(ResHandler::Sound indx, std::shared_ptr<framework::Object>, float minDistance, float attenuation);
    
private:
    std::mutex soundsGuard;
    sf::Music currentSong;
    std::deque<sf::Sound> runningSounds;
    std::deque<runningData> runningData;
    std::vector<reqInfo> soundRequests;
};

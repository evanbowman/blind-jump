#pragma once

#include "framework/framework.hpp"
#include "resourceHandler.hpp"
#include <SFML/Audio.hpp>
#include <list>
#include <memory>
#include <vector>

struct reqInfo {
    ResHandler::Sound soundIdx;
    float minDistance;
    float attenuation;
    bool spatialized;
    bool loop;
    std::weak_ptr<framework::Object> source;
};

struct runningData {
    std::weak_ptr<framework::Object> source;
    bool spatialized;
};

class SoundController {
public:
    enum { Sound, Music };
    SoundController();
    void update();
    void pause(int);
    void unpause(int);
    void play(ResHandler::Sound);
    // Note: sounds MUST be transient. Although this member function
    // has a loop parameter, this is designed for sounds that should
    // loop for the duration of a SHORT LIVED visual effect. Deallocation
    // of running sounds works like a queue, so if you play a long running
    // looping one, sounds behind it will not be deallocated, and adding
    // new ones will eventually use up all available sound resources.
    void play(ResHandler::Sound indx, std::shared_ptr<framework::Object>,
              float minDistance, float attenuation, bool loop = false);

private:
    std::mutex soundsGuard;
    sf::Music currentSong;
    std::deque<sf::Sound> runningSounds;
    std::deque<runningData> runningData;
    std::vector<reqInfo> soundRequests;
};

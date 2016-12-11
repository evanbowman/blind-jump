//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "soundController.hpp"

void SoundController::update() {
    if (!soundIdQueue.empty()) {
        std::lock_guard<std::mutex> lk(soundsGuard);
        for (auto soundId : soundIdQueue) {
            sounds.emplace(getgResHandlerPtr()->getSound(soundId));
            sounds.back().play();
        }
        soundIdQueue.clear();
    }
    if (sounds.size() > 0) {
        if (sounds.front().getStatus() == sf::Sound::Stopped) {
            sounds.pop();
        }
    }
}

void SoundController::play(ResHandler::Sound indx) {
    std::lock_guard<std::mutex> lk(soundsGuard);
    soundIdQueue.push_back(indx);
}

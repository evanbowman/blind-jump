//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "soundController.hpp"

void SoundController::update() {
    if (!soundRequests.empty()) {
        std::lock_guard<std::mutex> lk(soundsGuard);
        for (auto req : soundRequests) {
            runningSounds.emplace(getgResHandlerPtr()->getSound(req.soundIdx));
            runningSounds.back().setMinDistance(req.minDistance);
            runningSounds.back().setAttenuation(req.attenuation);
            runningSounds.back().setRelativeToListener(req.relative);
            runningSounds.back().setPosition(req.position);
            runningSounds.back().play();
        }
        soundRequests.clear();
    }
    if (runningSounds.size() > 0) {
        if (runningSounds.front().getStatus() == sf::Sound::Stopped) {
            runningSounds.pop();
        }
    }
}

void SoundController::play(ResHandler::Sound indx,
                           const sf::Vector3f & position, float minDistance,
                           float attenuation, bool relative) {
    std::lock_guard<std::mutex> lk(soundsGuard);
    soundRequests.push_back(
        {indx, position, minDistance, attenuation, relative});
}

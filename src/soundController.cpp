//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "soundController.hpp"

#include <iostream>

void SoundController::update() {
    if (!soundRequests.empty()) {
        std::lock_guard<std::mutex> lk(soundsGuard);
        for (const auto req : soundRequests) {
            runningSounds.emplace_back(getgResHandlerPtr()->getSound(req.soundIdx));
            runningSounds.back().setMinDistance(req.minDistance);
            runningSounds.back().setAttenuation(req.attenuation);
            runningData.push_back({req.source, req.spatialized});
            if (req.spatialized) {
                if (auto sp = req.source.lock()) {
                    const auto pos = sp.get()->getPosition();
                    runningSounds.back().setPosition(pos.x, pos.y, 0.f);
                }
            } else {
                runningSounds.back().setRelativeToListener(true);
            }
            runningSounds.back().setLoop(req.loop);
            runningSounds.back().play();
        }
        soundRequests.clear();
    }
    while (true) {
        if (runningSounds.size() > 0) {
            if (runningSounds.front().getStatus() != sf::Sound::Playing) {
                runningSounds.pop_front();
                runningData.pop_front();
            } else {
                break;
            }
        } else {
            break;
        }
    }
    for (auto iters = std::make_pair(runningSounds.begin(), runningData.begin());
         iters.first != runningSounds.end();
         ++iters.first, ++iters.second) {
        if (iters.second->spatialized) {
            if (auto sp = iters.second->source.lock()) {
                const auto pos = sp.get()->getPosition();
                iters.first->setPosition(pos.x, pos.y, 0.f);
            } else {
                iters.second->spatialized = false;
                iters.first->pause();
            }
        }
    }
}

void SoundController::play(ResHandler::Sound indx) {
    std::lock_guard<std::mutex> lk(soundsGuard);
    soundRequests.push_back({indx, 1.f, 0.f, false, false /*, nullptr not
                                                            convertible to 
                                                            weak_ptr*/});
}

void SoundController::play(ResHandler::Sound indx,
                           std::shared_ptr<framework::Object> source,
                           float minDistance,
                           float attenuation, bool loop) {
    std::lock_guard<std::mutex> lk(soundsGuard);
    soundRequests.push_back({indx, minDistance, attenuation, true, loop, source});
}

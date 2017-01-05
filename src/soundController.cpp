#include "soundController.hpp"
#include "rng.hpp"

static const std::string musicPaths[] = {"music/Frostellar.ogg"};

SoundController::SoundController() {
    sf::Listener::setGlobalVolume(75.f);
    // currentSong.openFromFile(resourcePath() + musicPaths[0]);
    // currentSong.setLoop(true);
    // currentSong.play();
}

void SoundController::pause(int options) {
    std::lock_guard<std::mutex> lk(soundsGuard);
    if (options & Sound) {
        for (auto & sound : runningSounds) {
            if (sound.getStatus() == sf::Sound::Playing) {
                sound.pause();
            }
        }
    }
    if (options & Music) {
        currentSong.pause();
    }
}

void SoundController::unpause(int options) {
    std::lock_guard<std::mutex> lk(soundsGuard);
    if (options & Sound) {
        for (auto & sound : runningSounds) {
            if (sound.getStatus() == sf::Sound::Paused) {
                sound.play();
            }
        }
    }
    if (options & Music) {
        currentSong.play();
    }
}

void SoundController::update() {
    std::lock_guard<std::mutex> lk(soundsGuard);
    if (!soundRequests.empty()) {
        for (const auto req : soundRequests) {
            runningSounds.emplace_back(
                getgResHandlerPtr()->getSound(req.soundIdx));
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
            if (req.loop) {
                // For some variety in looped sounds, set random playing offset
                sf::Time loopedTrackLength =
                    runningSounds.back().getBuffer()->getDuration();
                auto randomOffset =
                    rng::random(loopedTrackLength.asMilliseconds());
                sf::Time playingOffset = sf::milliseconds(randomOffset);
                runningSounds.back().setPlayingOffset(playingOffset);
                runningSounds.back().setLoop(true);
            }
            runningSounds.back().play();
        }
        soundRequests.clear();
    }
    while (true) {
        if (runningSounds.size() > 0) {
            if (runningSounds.front().getStatus() == sf::Sound::Stopped) {
                runningSounds.pop_front();
                runningData.pop_front();
            } else {
                break;
            }
        } else {
            break;
        }
    }
    for (auto
             iters = std::make_pair(runningSounds.begin(), runningData.begin());
         iters.first != runningSounds.end(); ++iters.first, ++iters.second) {
        if (iters.second->spatialized) {
            if (auto sp = iters.second->source.lock()) {
                const auto pos = sp.get()->getPosition();
                iters.first->setPosition(pos.x, pos.y, 0.f);
            } else {
                iters.second->spatialized = false;
                iters.first->stop();
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
                           float minDistance, float attenuation, bool loop) {
    std::lock_guard<std::mutex> lk(soundsGuard);
    soundRequests.push_back(
        {indx, minDistance, attenuation, true, loop, source});
}

//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "soundController.hpp"

void SoundController::poll() {
	if (!soundIdxQueue.empty()) {
		for (auto & element : soundIdxQueue) {
			sounds.emplace_back(global::resHandlerPtr->getSound(element));
			sounds.back().play();
		}
		soundIdxQueue.clear();
	}
	for (auto it = sounds.begin(); it != sounds.end();) {
		if (it->getStatus() == sf::Sound::Status::Stopped) {
			it = sounds.erase(it);
		} else {
			++it;
		}
	}
}

void SoundController::play(ResHandler::Sound indx) {
	soundIdxQueue.push_back(indx);
}

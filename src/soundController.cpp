//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
//                                                                        //
// This program is free software: you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or      //
// (at your option) any later version.                                    //
//                                                                        //
// This program is distributed in the hope that it will be useful,        //
// but WITHOUT ANY WARRANTY; without even the implied warranty of         //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
// GNU General Public License for more details.                           //
//                                                                        //
// You should have received a copy of the GNU General Public License      //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
//========================================================================//

#include "soundController.hpp"

void SoundController::poll() {
	if (!soundIdxQueue.empty()) {
		for (auto & element : soundIdxQueue) {
			sounds.emplace_back(globalResourceHandlerPtr->getSound(element));
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

void SoundController::play(ResourceHandler::Sound indx) {
	soundIdxQueue.push_back(indx);
}

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

#include "feedback.hpp"
#include "player.hpp"

bool Feedback::isAsleep{false};

namespace {
	float globalShakeIntensity{0.f};
	bool globalShakeActive{false};
	int64_t shakeDuration{0};
	int64_t timer{0};
}
	
void Feedback::Shake::shake(const float intensity, const int64_t duration) {
	if (!globalShakeActive) {
		globalShakeIntensity = intensity;
		shakeDuration = duration;
		globalShakeActive = true;
	}
}

void Feedback::Shake::update(Player & player, const sf::Time & elaspedTime) {
	if (globalShakeActive) {
		timer += elapsedTime.asMicroseconds();
		const static float PI{3.1415926535};
		// Interpolates a damped sinusoid
		float yOffset = Easing::easeOut<2>(timer, 50000) * globalShakeIntensity * std::sin(2 * PI * timer * 0.001f + 180);
		if (timer < 50000) {
			globalShakeActive = false;
			timer = 0;
		}
	}
}

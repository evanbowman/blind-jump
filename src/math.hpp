//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once
#include <SFML/Graphics.hpp>

namespace math {
	inline sf::Vector2f lerp(const sf::Vector2f & A, const sf::Vector2f & B, float t) {
		return A * t + (1 - t) * B;
	}
	inline float clamp(const float floor, float val, const float ceil) {
		if (val < floor) {
			val = floor;
		} else if (val > ceil) {
			val = ceil;
		}
		return val;
	}
}

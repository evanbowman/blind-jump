//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <SFML/Graphics.hpp>
#include <exception>
#include <cmath>

inline sf::Vector2f getDrawableRegionSize() {
	// First try a bunch of common resolutions--always good to provide reasonable default values
	// The ideal area of the region is something near 389000 pixels
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	float aspectRatio = static_cast<float>(desktop.width) / static_cast<float>(desktop.height);
	if (aspectRatio == 16.f / 9.f) {          // 16:9
		return sf::Vector2f(832.f, 468.f);
	} else if (aspectRatio == 16.f / 10.f) {  // 16:10
		return sf::Vector2f(784.f, 490.f);
	} else if (aspectRatio == 4.f / 3.f) {    // 4:3
		return sf::Vector2f(720.f, 540.f);
	} else if (aspectRatio == 5.f / 4.f) {    // 5:4
		return sf::Vector2f(695.f, 556.f);
	} else if (aspectRatio == 9.f / 16.f) {   // 9:16
		return sf::Vector2f(468.f, 832.f);
	} else if (aspectRatio == 10.f / 16.f) {  // 10:16 
		return sf::Vector2f(490.f, 784.f);
	} else if (aspectRatio == 3.f / 4.f) {    // 3:4
		return sf::Vector2f(540.f, 720.f);
	} else if (aspectRatio == 4.f / 5.f) {    // 4:5
		return sf::Vector2f(556.f, 695.f);
	}
    throw std::runtime_error("Your aspect ratio is unsupported. Available options are:\n16:9, 16:10, 4:3, 5:4, 9:16, 10:16, 3:4, 4:5");
}

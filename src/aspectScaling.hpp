//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

inline sf::Vector2f getDrawableRegionSize() {
	// First try a bunch of common resolutions--always good to provide reasonable default values
	// The ideal area of the region is something near 200000 pixels
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	float aspectRatio = static_cast<float>(desktop.width) / static_cast<float>(desktop.height);
	if (aspectRatio == 16.f / 9.f) {          // 16:9
		return sf::Vector2f(608.f, 342.f);
	} else if (aspectRatio == 16.f / 10.f) {  // 16:10
		return sf::Vector2f(576.f, 360.f);
	} else if (aspectRatio == 4.f / 3.f) {    // 4:3
		return sf::Vector2f(524.f, 393.f);
	} else if (aspectRatio == 5.f / 4.f) {    // 5:4
		return sf::Vector2f(500.f, 400.f);
	} else if (aspectRatio == 9.f / 16.f) {   // 9:16
		return sf::Vector2f(342.f, 608.f);
	} else if (aspectRatio == 10.f / 16.f) {  // 10:16 
		return sf::Vector2f(360.f, 576.f);
	} else if (aspectRatio == 3.f / 4.f) {    // 3:4
		return sf::Vector2f(393.f, 534.f);
	} else if (aspectRatio == 4.f / 5.f) {    // 4:5
		return sf::Vector2f(400.f, 500.f);
	}
	// If the user has a weird desktop setup, approximate a good view size
	sf::Vector2f drawableRegionSize;
	drawableRegionSize.x = 450.f;
	drawableRegionSize.y = 450.f;
	float windowAspect;
	// TODO: Binary search
	if (aspectRatio > 1.f) {
		do {
			drawableRegionSize.x += 0.025f;
			drawableRegionSize.y -= 0.025f;
			windowAspect = drawableRegionSize.x / drawableRegionSize.y;
		}
		while (std::fabs(aspectRatio - windowAspect) > 0.005f);
	} else {
		do {
			drawableRegionSize.x -= 0.025f;
			drawableRegionSize.y += 0.025f;
			windowAspect = drawableRegionSize.x / drawableRegionSize.y;
		}
		while (std::fabs(aspectRatio - windowAspect) > 0.005f);
	}
	return drawableRegionSize;
}

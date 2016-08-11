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

#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

inline sf::Vector2f getDrawableRegionSize() {
	// First try a bunch of common resolutions
	// The ideal area of the region is something near 200000 pixels
	// First try a bunch of common resolutions
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	float aspectRatio = static_cast<float>(desktop.width) / static_cast<float>(desktop.height);
	if (aspectRatio == 16.f / 9.f) {
		return sf::Vector2f(608.f, 342.f);
	} else if (aspectRatio == 16.f / 10.f) {
		return sf::Vector2f(576.f, 360.f);
	} else if (aspectRatio == 4.f / 3.f) {
		return sf::Vector2f(524.f, 393.f);
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

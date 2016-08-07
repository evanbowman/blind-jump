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

#include "camera.hpp"

inline sf::Vector2f lerp(const sf::Vector2f & A, const sf::Vector2f & B, float t) {
	return A * t + (1 - t) * B;
}

void Camera::update(const sf::Time & elapsedTime) {
	float trackingRate;
	if (pTarget->getGun().timeout == 0) {
		trackingRate = 0.000005f;
	} else {
		trackingRate = 0.0000025f;
	}
	float lerpSpeed = elapsedTime.asMicroseconds() * trackingRate;
	if (lerpSpeed > 1.f) lerpSpeed = 1.f;
	view.setCenter(lerp(pTarget->getCameraTarget(view), view.getCenter(), lerpSpeed));
}

const sf::View & Camera::getView() const {
	return view;
}

void Camera::reset() {
	float placementOffset = pTarget->getPosition().y / 4;
	view.setCenter(sf::Vector2f(pTarget->getPosition().x, placementOffset));
}

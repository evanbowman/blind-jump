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

Camera::Camera(Player * _pTarget, const sf::Vector2f & viewPort)  :
		pTarget(_pTarget),
		view(sf::Vector2f(viewPort.x / 2, viewPort.y / 2), viewPort),
		isShaking(false),
		shakeIndex(0),
		timer(0),
		shakeIntensity(0.f)
	{
		startPosition = view.getCenter();
	}

void Camera::update(const sf::Time & elapsedTime, const std::vector<sf::Vector2f> & targets) {
	float lerpSpeed;
	sf::Vector2f cameraPos;
	if (targets.empty()) {
		lerpSpeed = std::min(1.f, elapsedTime.asMicroseconds() * 0.0000055f);
		cameraPos = lerp(pTarget->getPosition(), view.getCenter(), lerpSpeed);
	} else if (pTarget->getState() != Player::State::deactivated) {
		// This bit does some math and makes the camera track the midpoint of the
		// player and the average position of all other significant objects in the
		// window
		lerpSpeed = std::min(1.f, elapsedTime.asMicroseconds() * 0.0000020f);
		sf::Vector2f aggregate;
		float divisor = 0;
		for (auto & vec : targets) {
			aggregate += vec;
			++divisor;
		}
		aggregate /= divisor;
		sf::Vector2f midpoint = lerp(pTarget->getPosition(), aggregate, 0.78f);
		cameraPos = lerp(midpoint, view.getCenter(), lerpSpeed);
	} else {
		lerpSpeed = std::min(1.f, elapsedTime.asMicroseconds() * 0.0000055f);
		cameraPos = lerp(pTarget->getPosition(), view.getCenter(), lerpSpeed);
	}
	if (isShaking) {
		timer += elapsedTime.asMicroseconds();
		if (timer > 50000) {
			timer = 0;
			shakeIndex += 1;
			if (shakeIndex > 4) {
				shakeIndex = 4;
				isShaking = false;
				timer = 0;
			}
		}
		const static std::array<int, 5> shakeConstants = {{3, -5, 3, -2, 1}};
		float shakeOffset = shakeConstants[shakeIndex];
		cameraPos.y += shakeOffset * shakeIntensity;
	}
	view.setCenter(cameraPos);
}

const sf::View & Camera::getView() const {
	return view;
}

void Camera::reset() {
	float placementOffset = pTarget->getPosition().y / 4;
	view.setCenter(sf::Vector2f(pTarget->getPosition().x, placementOffset));
	startPosition = view.getCenter();
}

void Camera::shake(float _shakeIntensity) {
	if (!isShaking) {
		shakeIntensity = _shakeIntensity;
		isShaking = true;
		shakeIndex = 0;
	}
}

sf::Vector2f Camera::getOffset() const {
	return view.getCenter() - startPosition;
}

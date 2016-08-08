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
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <utility>
#include <vector>
#include "player.hpp"

class Camera {
	Player * pTarget;
	sf::View view;
	sf::Vector2f startPosition, midpoint, buffer;
	bool isShaking;
	uint8_t shakeIndex;
	int64_t shakeTimer, trackingTimer;
	float shakeIntensity;
	enum class State {
		trackMidpoint, followPlayer, foundEnemy
    };
	State state;
	
public:
	Camera(Player * _pTarget, const sf::Vector2f & viewPort);
	void update(const sf::Time &, const std::vector<sf::Vector2f> &);
	void reset();
	const sf::View & getView() const;
	void shake(float);
	sf::Vector2f getOffset() const;
};

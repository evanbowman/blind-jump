//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <utility>
#include <vector>
#include "player.hpp"
#include "math.hpp"

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
	void snapToTarget();
	void panDown();
	const sf::View & getView() const;
	void shake(float);
	void setView(const sf::View &);
	bool moving() const;
	sf::Vector2f getOffset() const;
};

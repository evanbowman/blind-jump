//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "SFML/Graphics.hpp"
#include "wall.hpp"
#include "effectsController.hpp"
#include <vector>
#include <cmath>
#include "Framework/framework.hpp"

class Enemy {
protected:
	bool killFlag, colored;
	float xPos, yPos, colorAmount;
	uint8_t frameIndex, health;
	uint32_t colorTimer, frameTimer;
	uint_fast8_t checkWallCollision(const std::vector<wall> &, float, float);
	bool wallInPath(const std::vector<wall> &, float, float, float);
	void updateColor(const sf::Time &);
	void facePlayer();
	~Enemy() {};
	
public:
	Enemy(float, float);
	bool getKillFlag() const;
	bool isColored() const;
	float getXpos() const;
	float getYpos() const;
	float getColorAmount() const;
	void setKillFlag(bool);
};

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
#ifndef enemy_hpp
#define enemy_hpp

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

#endif /* enemyParent_hpp */

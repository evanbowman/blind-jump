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

//
// TODO: I made these functions virtual to enforce a design pattern when making this.
// They really shouldn't be.
//

class Enemy {
protected:
	virtual void onDeath(EffectGroup &) = 0;
	bool killFlag, colored;
	float xInit, yInit, playerPosX, playerPosY, xPos, yPos, colorAmount;
	uint8_t frameIndex, health;
	uint32_t colorTimer, frameTimer;
	uint_fast8_t checkWallCollision(const std::vector<wall> &, float, float, float);
	bool wallInPath(const std::vector<wall> &, float, float, float);
	void checkShotCollision(EffectGroup & ef, float rad);
	void updateColor(const sf::Time &);
	void facePlayer();
	
public:
	Enemy(float, float, float, float);
	virtual const sf::Sprite & getSprite() const = 0;
	virtual const sf::Sprite & getShadow() const = 0;
	virtual void update(float, float, const std::vector<wall> &, EffectGroup & ef,  const sf::Time &);
	bool getKillFlag() const;
	bool isColored() const;
	float getXinit() const;
	float getYinit() const;
	float getXpos() const;
	float getYpos() const;
	float getColorAmount() const;
	void setKillFlag(bool);
};

#endif /* enemyParent_hpp */

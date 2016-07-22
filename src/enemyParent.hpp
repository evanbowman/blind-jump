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

#include "SFML/Graphics.hpp"
#include "wall.hpp"

class EnemyParent {
public:
	void setInitPosition(float, float);
	void setPosition(float, float);
	void setPlayerPos(float, float);
	bool getKillFlag() const;
	EnemyParent(sf::Sprite*);
	float getXinit() const;
	float getYinit() const;
	float getXpos() const;
	float getYpos() const;
	bool checkCollisionWall(std::vector<wall>, float);
	float xInit;
	float yInit;
	float xPos;
	float yPos;
	float playerPosX;
	float playerPosY;
	float xOffset;
	float yOffset;
	unsigned char frameIndex;
	bool killFlag;
	bool isColored;
	int32_t colorTimer;
	float colorAmount;
	uint8_t health;
	bool colored();

};

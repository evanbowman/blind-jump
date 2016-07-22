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

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "turret.hpp"
#include "fontController.hpp"
#include "effectsController.hpp"
#include "resourceHandler.hpp"
#include "Framework/framework.hpp"

//
// TODO: Urgent: refactor
//

class Turret {
private:
	using HBox = Framework::HitBox<16, 32>;
	HBox hitBox;
	double xPos;
	double yPos;
	double xInit;
	double yInit;
	double playerPosX;
	double playerPosY;
	uint8_t imageIndex;
	char spriteIndex;
	short disableCountdown;
	bool visibility;
	sf::Sprite turretSprites[10];
	//Set the duration between animation frame transitions
	char animationCount;
	bool active;
	int activateTimer;
	short shotCountdown;
	short shotsFired;
	double xOffset;
	double yOffset;
	float hp;
	bool killFlag;
	char colorTimer;
	bool isColored;
	float colorAmount;
	
public:
	Turret(sf::Sprite spr[10]);
	const HBox & getHitBox() const;
	void setPosition(double, double);
	sf::Sprite* getShadow();
	sf::Sprite* getSprite(sf::Time &);
	void updateShots(EffectGroup &, FontController&);
	double getXinit();
	double getYinit();
	bool getKillFlag();
	void setInitPosition(double, double);
	double getPlayerPosX();
	double getPlayerPosY();
	void setPlayerPos(double, double);
	double getXpos();
	double getYpos();
	bool colored();
	float getColorAmount();
};

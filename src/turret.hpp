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
#include "effectsController.hpp"
#include "resourceHandler.hpp"
#include "Framework/framework.hpp"
#include "spriteSheet.hpp"

//
// TODO: Urgent: refactor
//

class Turret {
private:
	using HBox = Framework::HitBox<16, 32>;
	HBox hitBox;
	float xPos;
	float yPos;
	uint8_t imageIndex;
	int16_t disableCountdown;
	sf::Sprite turretSprites[10];
	SpriteSheet<0, 0, 16, 32> turretSheet;
	SpriteSheet<0, 32, 16, 26> shadowSheet;
	char animationCount;
	bool active;
	int activateTimer;
	int16_t shotCountdown;
	int16_t shotsFired;
	float hp;
	bool killFlag;
	char colorTimer;
	bool isColored;
	float colorAmount;
	
public:
	Turret(const sf::Texture &, float, float);
	const HBox & getHitBox() const;
	void setPosition(float, float);
	const sf::Sprite & getShadow();
	const sf::Sprite & getSprite();
	void update(const sf::Time &, float, float);
	void updateShots(EffectGroup &, float, float);
	bool getKillFlag();
	float getXpos();
	float getYpos();
	bool colored();
	float getColorAmount();
};

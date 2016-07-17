//
//  turret.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/19/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef turret_hpp
#define turret_hpp

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

#endif /* turret_hpp */

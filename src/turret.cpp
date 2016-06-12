//
//  turret.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/19/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "turret.hpp"
#include <cmath>
#include "angleFunction.hpp"
#include <iostream>

turret::turret(sf::Sprite spr[10]) {
	xPos = 0;
	yPos = 0;
	xInit = 0;
	yInit = 0;
	visibility = 1;
	imageIndex = 0;
	//Save all the input sprites, we'll need to return them later for drawing to the game window
	for (int i = 0; i < 10; i++) {
		turretSprites[i] = spr[i];
	}
	playerPosX = 0;
	playerPosY = 0;
	//What stage of the animation is the turret in? Lets keep track of it:
	animationCount = 0;
	active = 0;
	//How long the sprite waits before turning on, in case the player spawns nearby
	activateTimer = 120;
	shotCountdown = 40;
	shotsFired = 0;
	hp = 6;
	killFlag = 0;
	isColored = 0;
	colorTimer = 0.f;
	colorAmount = 0.f;
}

//Returns the turret's sprite based on its animation sequence
sf::Sprite* turret::getSprite(sf::Time & elapsedTime) {
	if (isColored) {
		colorTimer += elapsedTime.asMilliseconds();
		if (colorTimer > 20.f) {
			colorTimer -= 20.f;
			colorAmount -= 0.1f;
		}
		
		if (colorAmount <= 0.f) {
			isColored = false;
		}
	}
	if (active) {
		if (sqrt(pow((xPos - playerPosX + 8), 2) + pow((yPos - playerPosY + 16), 2)) > 174) {
			if (imageIndex != 0 && sqrt(pow((xPos - playerPosX + 8), 2) + pow((yPos - playerPosY + 16), 2)) > 228) {	//If the player is far enough away de-activate it
				if (animationCount == 1) {
					imageIndex -= 1;
					animationCount = 0;
				}
				animationCount += 1;
				//Lets have the time until the turret shoots after upening be the same every time:
				shotCountdown = 20;
				shotsFired = 0;
			}
			else {
				animationCount = 0;
			}
		}
		else {							  //If the player is close activate the turret
			if (imageIndex != 4) {
				if (animationCount == 3) {
					imageIndex += 1;
					animationCount = 0;
				}
				animationCount += 1;
			
			}
			else {
				animationCount = 0;
				disableCountdown = 50;
			}
		}
	}
	else {
		if (--activateTimer == 0) {
			active = 1;
		}
	}
	return &turretSprites[imageIndex];
}

//Fairly self-explanitory, updates the position of the turret when called
void turret::setPosition(double x, double y) {
	xPos = x;
	yPos = y;
	xOffset = x - xInit;
	yOffset = y - yInit;
	for (int i = 0; i < 10; i++) {
		if (i > 4) {
			turretSprites[i].setPosition(x, y + 18);
		}
		else {
			turretSprites[i].setPosition(x, y);
		}
		
	}
}

//Returns the turret's shadow sprite
sf::Sprite* turret::getShadow() {
	return &turretSprites[imageIndex + 5];
}

void turret::updateShots(effectsController& ef, FontController& fonts) {
	//If the turret is open...
	if (imageIndex == 4) {
		//And the shot coundown timer has decremented far enough
		if (--shotCountdown == 0) {
			//Add a shot flash effect to the effects controller
			ef.addTurretFlash(xInit, yInit);
			//Create a shot object with an angle equal to the angle between the player and the turret
			ef.addEnemyShot(xInit, yInit, angleFunction(xPos + 18, yPos, playerPosX, playerPosY));
			//Increment the number of shots fired
			shotsFired++;
			//Reset the countdown timer
			if (shotsFired != 3) {
				shotCountdown = 8;
			}
			else {
				shotCountdown = 60;
				shotsFired = 0;
			}
		}
		
	//Check collisions with player's shots, but only if the shot vectors aren't empty
	if (!ef.getBulletLayer1().empty()) {
		for (auto & element : ef.getBulletLayer1()) {
			if (std::abs(element.getXpos() - xPos) < 8 && std::abs(element.getYpos() - (yPos + 6)) < 15) {
				element.setKillFlag();		   // Kill the bullet if there's a collision between the bullet and the enemy
				// Tons of effects in one place is distracting, so don't draw another one if the enemy is about to explode
				if (hp == 1) {
					element.disablePuff();
				}
				hp -= 1;
				isColored = true;
				colorAmount = 1.f;
			}
		}
	}
	
	}
	
	if (hp == 0) {
		killFlag = 1;
		if ((rand() % 4) == 0) {
			ef.addHearts(xInit + 4, yInit + 4);
		} else {
			ef.addCoins(xInit + 4, yInit + 4);
		}
		ef.addFireExplosion(xInit + 6, yInit + 10);
	}
}

bool turret::getKillFlag() {
	return killFlag;
}

double turret::getXinit() {
	return xInit;
}

double turret::getYinit() {
	return yInit;
}

void turret::setInitPosition(double x, double y) {
	xInit = x;
	yInit = y;
}

double turret::getPlayerPosX() {
	return playerPosX;
}

double turret::getPlayerPosY() {
	return playerPosY;
}

void turret::setPlayerPos(double x, double y) {
	playerPosX = x / 2;
	playerPosY = y / 2;
}

double turret::getXpos() {
	return xPos;
}

double turret::getYpos() {
	return yPos;
}

bool turret::colored() {
	return isColored;
}

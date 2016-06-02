//
//  wall.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/17/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "wall.hpp"

wall::wall() {
	//Besides existing for the player to run into, the walls do not need to have any functionality
	xPosInitial = 0;
	yPosInitial = 0;
	xPos = 0;
	yPos = 0;
	width = 32;
	height = 26;
	insideWindow = false;
}

float wall::getPosY() {
	return yPos;
}

float wall::getPosX() {
	return xPos;
}

void wall::setPosition(float x, float y) {
	xPos = x;
	yPos = y;
}

void wall::setXinit(float x) {
	xPosInitial = x;
}

void wall::setYinit(float y) {
	yPosInitial = y;
}

float wall::getXinit() {
	return xPosInitial;
}

float wall::getYinit() {
	return yPosInitial;
}

void wall::setInsideWindow(bool cond) {
	insideWindow = cond;
}

bool wall::isInsideWindow() const {
	return insideWindow;
}

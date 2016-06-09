//
//  detailParent.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/29/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "detailParent.hpp"

detailParent::detailParent(float xStart, float yStart, int len, float width, float height) {
	xInit = xStart;
	yInit = yStart;
	xPos = xInit;
	yPos = yInit;
	windowCenterX = width;
	windowCenterY = height;
}

detailParent::detailParent() {
	// Empty constructor for simpler derived classes that only need the member fns
}

void detailParent::setInitPosition(float x, float y) {
	xInit = x;
	yInit = y;
}

void detailParent::setPosition(float x, float y) {
	xPos = x;
	yPos = y;
}

float detailParent::getxPos() {
	return xPos;
}

float detailParent::getyPos() {
	return yPos;
}

float detailParent::getWindowCenterX() {
	return windowCenterX;
}

float detailParent::getWindowCenterY() {
	return windowCenterY;
}

float detailParent::getxInit() {
	return xInit;
}

float detailParent::getyInit() {
	return yInit;
}

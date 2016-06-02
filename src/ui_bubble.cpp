//
//  ui_bubble.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/6/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "ui_bubble.hpp"

UIBubble::UIBubble(float xPos, float yPos, sf::Sprite* inpSpr) {
	this->xPos = xPos;
	this->yPos = yPos;
	spr = *inpSpr;
	killFlag = false;
	timeout = 200;
	bubbleOutline.setFillColor(sf::Color(44,57,83,230));
	bubbleOutline.setRadius(1);
	xStep = (xPos + 124) / 35;
	yStep = (yPos - 84) / 35;
}

bool UIBubble::getKillFlag() {
	return killFlag;
}

void UIBubble::update(sf::RenderWindow &window) {
	// Do something here...
	float radius = bubbleOutline.getRadius();
	if (radius < 35) {
		float newRadius = radius * 1.2;
		if (newRadius > 35) {
			newRadius = 35;
		}
		bubbleOutline.setRadius(newRadius);
		yPos *= 0.92;
		yPos -= yStep;
		xPos -= (newRadius - radius);
		xPos += xStep;
	}
	
	timeout--;
	// If the object has timed out, tell the ui controller to get rid of it
	if (timeout == 0) {
		killFlag = true;
	}
	spr.setPosition(xPos, yPos + 20);
	bubbleOutline.setPosition(xPos, yPos);
	window.draw(bubbleOutline);
	if (radius >= 35) {
		window.draw(spr);
	}
}

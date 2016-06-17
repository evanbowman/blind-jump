//
//  damagedRobot.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/5/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "damagedRobot.hpp"

DamagedRobot::DamagedRobot(float xStart, float yStart, const sf::Texture & inpTxtr, int len, float width, float height) : detailParent(xStart, yStart, len, width, height) {
	robotSheet.setTexture(inpTxtr);
	robotSheet[rand() % 2];
	// TODO: flip the sprite for more variety
}

void DamagedRobot::update(float xOffset, float yOffset) {
	// Update the object's position
	xPos = xOffset + xInit;
	yPos = yOffset + yInit;
	robotSheet.setPosition(xPos, yPos);
}

sf::Sprite* DamagedRobot::getSprite() {
	return robotSheet.getSpritePtr();
}

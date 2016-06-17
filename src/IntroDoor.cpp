//
//  Pillar.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/15/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "IntroDoor.hpp"
#include <cmath>
#include "screenShakeController.hpp"

IntroDoor::IntroDoor(float xStart, float yStart, const sf::Texture & inpTxtr, int len, float width, float height) : detailParent(xStart, yStart, len, width / 2, height / 2) {
	doorSheet.setTexture(inpTxtr);
	frameIndex = 0;
	timer = 0;
	state = State::dormant;
}

bool checkBulletCollision(float xPos, float yPos, effectsController & ef) {
	for (auto & element : ef.getBulletLayer1()) {
		if (std::abs(element.getXpos() - xPos) < 4 && std::abs(element.getYpos() - yPos) < 4) {
			element.setKillFlag();
			return true;
		}
	}
	return false;
}

void IntroDoor::update(float xOffset, float yOffset, ScreenShakeController * pscr, effectsController & ef, const sf::Time & elapsedTime) {
	switch (state) {
		case State::dormant:
		    if (checkBulletCollision(xOffset + xInit + 124, yPos + 62, ef)) {
				state = State::opening;
			}
			break;
			
		case State::opening:
			timer += elapsedTime.asMilliseconds();
			if (timer > 52) {
				timer -= 52;
				frameIndex++;
				if (frameIndex > 3) {
					frameIndex = 3;
					state = State::opened;
					pscr->rumble();
				}
			}
			break;
			
		case State::opened:
			// Does nothing
			break;
	}
    
	yPos = yOffset + yInit;
	doorSheet.setPosition(xOffset + xInit, yPos);
}

sf::Sprite * IntroDoor::getSprite() {
	doorSheet[frameIndex];
	return doorSheet.getSpritePtr();
}

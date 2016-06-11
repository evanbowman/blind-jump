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
#include <iostream>

IntroDoor::IntroDoor(float xStart, float yStart, sf::Texture * inpTxtr, int len, float width, float height) : detailParent(xStart, yStart, len, width / 2, height / 2) {
	doorSheet.setTexture(inpTxtr);
	frameIndex = 0;
	timer = 0;
	state = State::dormant;
}

void IntroDoor::update(float xOffset, float yOffset, InputController * pInput, ScreenShakeController * pscr, const sf::Time & elapsedTime) {
	switch (state) {
		case State::dormant:
			// If the player presses the button by the door, go to the opening state
			if (pInput->zPressed() && fabsf(windowCenterX - (xOffset + xInit + 130)) < 6 && fabsf(windowCenterY - (yPos + 70)) < 10) {
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

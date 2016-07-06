//
//  screenShakeController.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/19/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "screenShakeController.hpp"

ScreenShakeController::ScreenShakeController() {
	active = false;
	updateCounter = 1;
	shakeIndex = 0;
	shakeMode = 0;
}

void ScreenShakeController::update(Player & p) {
	if (!active) {
		return;
	} else {
		switch (shakeMode) {
			case 0:
				if (--updateCounter == 0) {
					updateCounter = 4;
					p.setPosition(p.getXpos(), p.getYpos() + shakeArray[shakeIndex]);
					p.setWorldOffsetY(p.getWorldOffsetY() + shakeArray[shakeIndex]);
					shakeIndex++;
				}
				if (shakeIndex > 5) {
					shakeIndex = 0;
					active = false;
					updateCounter = 1;
				}
				break;
				
			case 1:
				if (--updateCounter == 0) {
					updateCounter = 4;
					p.setPosition(p.getXpos(), p.getYpos() + shakeArray2[shakeIndex]);
					p.setWorldOffsetY(p.getWorldOffsetY() + shakeArray2[shakeIndex]);
					shakeIndex++;
				}
				if (shakeIndex > 4) {
					shakeIndex = 0;
					active = false;
					updateCounter = 1;
				}
				break;
				
			
			default:
				break;
		}
	}
}

void ScreenShakeController::shake() {
	if (!active) {
		active = true;
		shakeMode = 0;
	}
}

void ScreenShakeController::rumble() {
	if (!active) {
		active = true;
		shakeMode = 1;
	}
}


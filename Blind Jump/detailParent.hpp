//
//  detailParent.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/29/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef detailParent_hpp
#define detailParent_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"

class detailParent {
public:
	float xInit;
	float yInit;
	float xPos;
	float yPos;
	float windowCenterX;
	float windowCenterY;
	detailParent();
	detailParent(float, float, sf::Sprite*, int, float, float);
	bool getDrawOrder();
	void setDrawOrder(bool);
	void setPosition(float, float);
	void setInitPosition(float, float);
	float getxPos();
	float getyPos();
	float getxInit();
	float getyInit();
	float getWindowCenterX();
	float getWindowCenterY();
};

#endif /* detailParent_hpp */

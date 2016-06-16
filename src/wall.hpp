//
//  wall.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/17/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef wall_hpp
#define wall_hpp

#include <stdint.h>

class wall {
private:
	float xPosInitial, yPosInitial,  xPos, yPos;

public:
	float getPosX() const;
	float getPosY() const;
	
	constexpr int8_t getWidth() const {
		return 32;
	}

	constexpr int8_t getHeight() const {
		return 26;
	}

	wall();
	void setPosition(float, float);
	void setYinit(float);
	void setXinit(float);
	float getXinit() const;
	float getYinit() const;
};
#endif /* wall_hpp */

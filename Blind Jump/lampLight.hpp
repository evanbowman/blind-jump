//
//  lampLight.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/16/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef lampLight_hpp
#define lampLight_hpp

#include <stdio.h>
#include "detailParent.hpp"

class LampLight : public detailParent {
public:
	LampLight(float, float, sf::Sprite, sf::Sprite, int, float, float);
	sf::Sprite* getSprite();
	sf::Sprite* getGlow();
	void update(float, float);
	bool getKillFlag();
	void setKillFlag(bool);
	
private:
	sf::Sprite lampSprite;
	sf::Sprite glowSprite;
	bool killflag;
	
};

#endif /* lampLight_hpp */

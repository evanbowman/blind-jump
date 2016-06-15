//
//  damagedRobot.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/5/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef damagedRobot_hpp
#define damagedRobot_hpp

#include "detailParent.hpp"
#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"

class DamagedRobot : public detailParent {
public:
	DamagedRobot(float, float, sf::Texture *, int, float, float);
	void update(float, float);
	sf::Sprite * getSprite();
	
private:
	SpriteSheet<40, 43> robotSheet;
	
};

#endif /* damagedRobot_hpp */

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

class DamagedRobot : public Detail {
public:
	DamagedRobot(float, float, const sf::Texture &);
	void update(float, float, const sf::Time &);
	const sf::Sprite & getSprite() const;
	
private:
	mutable SpriteSheet<88, 102, 40, 43> robotSheet;
};

#endif /* damagedRobot_hpp */

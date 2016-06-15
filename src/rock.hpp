//
//  rock.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/5/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef rock_hpp
#define rock_hpp

#include "detailParent.hpp"
#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"

class Rock : public detailParent {
private:
	SpriteSheet<32, 64> rockSheet;
	
public:
	void update(float, float);
	Rock(float, float, sf::Texture *, int, float, float);
	sf::Sprite * getSprite();
};

#endif /* rock_hpp */

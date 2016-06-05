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

#include <stdio.h>
#include "detailParent.hpp"
#include "SFML/Graphics.hpp"

class Rock : public detailParent {
private:
	sf::Sprite sprite;
	
public:
	void update(float, float);
	Rock(float, float, sf::Sprite*, int, float, float);
	sf::Sprite* getSprite();
};

#endif /* rock_hpp */

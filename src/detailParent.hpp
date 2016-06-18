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

#include "SFML/Graphics.hpp"

class Detail {
protected:
	float xInit, yInit, yPos;

public:
	Detail(float, float);
	virtual const sf::Sprite & getSprite() const = 0;
	virtual void update(float, float, const sf::Time &) = 0;
	virtual float getYpos();
};

#endif /* detailParent_hpp */

//
//  generalDetail.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/11/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "generalDetail.hpp"

GeneralDetail::GeneralDetail(float _xInit, float _yInit, sf::Sprite & _spr):
	Detail{_xInit, _yInit}
{
	spr = _spr;
}

void GeneralDetail::update(float xOffset, float yOffset, const sf::Time & elapsedTime) {
	setPosition(xInit + xOffset, yInit + yOffset);
	spr.setPosition(position.x, position.y);
}

const sf::Sprite & GeneralDetail::getSprite() const {
	return spr;
}

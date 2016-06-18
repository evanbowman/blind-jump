//
//  detailParent.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/29/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "detailParent.hpp"

Detail::Detail(float _xInit, float _yInit)
	: xInit{_xInit},
	  yInit{_yInit},
	  yPos{0.f}
{}

float Detail::getYpos() {
	return yPos;
}

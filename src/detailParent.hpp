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

#include <SFML/Graphics.hpp>
#include "Framework/framework.hpp"

class Detail : public Framework::Object {
protected:
    float xInit, yInit;

public:
	Detail(float _xInit, float _yInit) : Object{0, 0}, xInit{_xInit}, yInit{_yInit} {}
};

#endif /* detailParent_hpp */

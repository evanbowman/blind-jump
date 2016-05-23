//
//  generalDetail.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/11/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef generalDetail_hpp
#define generalDetail_hpp

#include <stdio.h>
#include "detailParent.hpp"

class GeneralDetail : public detailParent {
public:
    GeneralDetail(float, float, sf::Sprite*, int, float, float);
    sf::Sprite* getSprite();
    void update(float, float);
    
private:
    sf::Sprite spr;
};

#endif /* generalDetail_hpp */

//
//  Pillar.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/15/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef Pillar_hpp
#define Pillar_hpp

#include "detailParent.hpp"

class Pillar : public detailParent {
private:
    sf::Sprite sprite;
    
public:
    void update(float, float);
    Pillar(float, float, sf::Sprite*, int, float, float);
    sf::Sprite* getSprite();
};

#endif /* Pillar_hpp */

//
//  Pillar.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/15/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef IntroDoor_hpp
#define IntroDoor_hpp

#include "detailParent.hpp"
#include "inputController.hpp"

class ScreenShakeController;

class IntroDoor : public detailParent {
    
    enum class State { dormant, opening, opened };
    
private:
    sf::Sprite sprite[4];
    char frameIndex, frameRate;
    State state;
    
public:
    void update(float, float, InputController * pInput, ScreenShakeController * pscr);
    IntroDoor(float, float, sf::Sprite*, int, float, float);
    sf::Sprite* getSprite();
};

#endif /* Pillar_hpp */

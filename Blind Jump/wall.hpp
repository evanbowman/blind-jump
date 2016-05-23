//
//  wall.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/17/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef wall_hpp
#define wall_hpp

#include <stdio.h>
class wall {
private:
    bool insideWindow;
    float xPos;
    float yPos;

public:
    bool isInsideWindow() const;
    void setInsideWindow(bool);
    float getPosX();
    float getPosY();
    float xPosInitial;
    float yPosInitial;
    int width;
    int height;
    wall();
    void setPosition(float, float);
    void setYinit(float);
    void setXinit(float);
    float getXinit();
    float getYinit();
};
#endif /* wall_hpp */

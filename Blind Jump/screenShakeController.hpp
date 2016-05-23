//
//  screenShakeController.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/19/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef screenShakeController_hpp
#define screenShakeController_hpp

#include <stdio.h>
#include "player.hpp"

class ScreenShakeController {
public:
    ScreenShakeController();
    void update(Player&);
    void shake();
    void rumble();
    
private:
    bool active;
    const char shakeArray[6] = {4, -8, 6, -4, 3, -1};
    const char shakeArray2[5] = {3, -5, 3, -2, 1};
    char shakeMode;
    unsigned char shakeIndex;
    unsigned char updateCounter;
};

#endif /* screenShakeController_hpp */

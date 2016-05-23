//
//  ui_bubble.hpp
//  Blind Jump
//
//  The UI bubble class. When the player opens a chest, the UI controller
//  puts the image in a bubble and floats it to the top of the screen.
//  When the effect times out, it sets a 'killflag' that tells its controller
//  to remove it.
//
//  Created by Evan Bowman on 3/6/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef ui_bubble_hpp
#define ui_bubble_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"

class UIBubble {
private:
    sf::CircleShape bubbleOutline;
    float xPos;
    float yPos;
    bool killFlag;
    sf::Sprite spr;
    int timeout;
    float xStep;
    float yStep;
    
public:
    UIBubble(float, float, sf::Sprite*);
    void update(sf::RenderWindow&);
    bool getKillFlag();
    
};

#endif /* ui_bubble_hpp */

//
//  Hearts.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 4/2/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef Hearts_hpp
#define Hearts_hpp

#include "SFML/Graphics.hpp"

class Hearts {
private:
    float xInit, yInit, xPos, yPos;
    sf::Sprite spr, glow;
    bool killFlag;
    
public:
    Hearts(sf::Sprite*, sf::Sprite, float, float);
    bool getKillFlag();
    void setKillFlag(bool);
    sf::Sprite getSprite();
    sf::Sprite* getGlow();
    void update(float, float);
    float getXpos();
    float getYpos();
};

#endif /* Hearts_hpp */

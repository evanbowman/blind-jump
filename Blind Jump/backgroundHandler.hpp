//
//  backgroundHandler.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/11/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef backgroundHandler_hpp
#define backgroundHandler_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class backgroundHandler {
private:
    sf::Texture bkgLayer[3];
    sf::Texture bkgStars;
    sf::Sprite bkgSprite[3];
    sf::Sprite stars[81];
    float xOffset;
    float yOffset;
    float posX;
    float posY;
    float windowW;
    float windowH;
    unsigned char workingSet;
    
public:
    backgroundHandler();
    void drawBackground(sf::RenderWindow&);
    void setOffset(float, float);
    void setPosition(float, float);
    void giveWindowSize(float, float);
    void setBkg(unsigned char);
};

#endif /* backgroundHandler_hpp */

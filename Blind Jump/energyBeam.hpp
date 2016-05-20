//
//  energyBeam.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/10/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef energyBeam_hpp
#define energyBeam_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include <cmath>

class EnergyBeam {
    
    enum class State { entering, leaving, running };
    
private:
    double xInit, yInit, xPos, yPos;
    State state;
    char frameIndex, frameRate;
    sf::Sprite sprites[6];
    sf::RectangleShape beamShape;
    bool killFlag;
    bool valid;
    float rotationDir;
    
public:
    void update(float, float);
    EnergyBeam(float, float, sf::Sprite*, float, float);
    void draw(sf::RenderTexture&);
    bool getKillFlag();
    float getX1();
    float getY1();
    float getX2();
    float getY2();
    // To stop beam after it's hit player
    void invalidate();
    bool isValid();
    float getDir();
    void setDir(float);
};

#endif /* energyBeam_hpp */

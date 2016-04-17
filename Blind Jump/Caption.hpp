//
//  Caption.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 4/16/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef Caption_hpp
#define Caption_hpp

#include "SFML/Graphics.hpp"

// Define states for the state machine
#define OPENING 'o'
#define OPENED 'O'
#define CLOSING 'c'
#define CLOSED 'C'
#define FORCE_CLOSE 'F'
#define LOCKED 'L'

class Caption {
private:
    // Position information
    float xInit, yInit, xPos, yPos, windowCenterX, windowCenterY;
    // Store the string to display
    std::string msgString, msgHeader, msgFooter, workingString;
    // Store the text to be output
    sf::Text msgText;
    // The current state of the object
    char state;
    int desiredDelay;
    sf::Clock clock, animationTimer;
    
public:
    void setWindowCenter(float, float);
    void update(float, float);
    sf::Text * getText();
    void setText(const char *);
    Caption(float, float, sf::Font&);
    bool isClosed();
    void setCharacterSize(float);
    void forceClose();
};

#endif /* Caption_hpp */

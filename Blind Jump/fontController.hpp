//
//  FontController.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/21/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef fontController_hpp
#define fontController_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"

class FontController {
private:
    sf::Texture texture;
    float alpha;
    sf::CircleShape healthFull[10];
    sf::CircleShape healthEmpty[10];
    sf::View fontView;
    char health;
    char maxHealth;
    bool doRecolor;
    char colorState;
    float width;
    float height;
    int score;
    
public:
    FontController(sf::View);
    void setWaypointText(int, float, float);
    void setZoneText(char);
    void print(sf::RenderWindow&);
    void updateHealth(char);
    void updateMaxHealth(char);
    char getMaxHealth();
};
#endif /* FontController_hpp */

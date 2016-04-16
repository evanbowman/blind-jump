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
    // The fonts to be used by the font controller
    sf::Font cornerstone;
    sf::Text waypointText;
    sf::Text healthText;
    sf::Text titleText;
    sf::Text test;
    char health;
    char maxHealth;
    float width;
    float height;
    int score;
    
public:
    FontController(sf::View);
    void setWaypointText(int);
    void setZoneText(char);
    void print(sf::RenderWindow&);
    void updateHealth(char);
    void updateMaxHealth(char);
    void drawTitle(unsigned char, sf::RenderWindow&);
    char getMaxHealth();
    sf::Text* getTitle();
};
#endif /* FontController_hpp */

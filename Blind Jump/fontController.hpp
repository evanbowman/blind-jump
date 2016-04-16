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
#include "Caption.hpp"

class FontController {
private:
    sf::Texture texture;
    float alpha;
    sf::CircleShape healthFull[10];
    sf::CircleShape healthEmpty[10];
    sf::View fontView;
    // The fonts to be used by the font controller
    sf::Font cornerstone;
    sf::Text waypointText, healthText, titleText;
    char health;
    char maxHealth;
    float width;
    float height;
    int score;
    float windowCenterX, windowCenterY;
    std::vector<Caption> captions;
    
public:
    FontController(sf::View, float, float);
    void update(sf::RenderWindow&, float, float);
    void setWaypointText(int);
    void setZoneText(char);
    void print(sf::RenderWindow&);
    void updateHealth(char);
    void updateMaxHealth(char);
    void drawTitle(unsigned char, sf::RenderWindow&);
    char getMaxHealth();
    sf::Text* getTitle();
    void addCaption(float, float, const char *);
    std::vector<sf::Text *>* getCaptions();
    void terminateCaptions();
};
#endif /* FontController_hpp */

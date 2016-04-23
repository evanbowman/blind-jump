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
    sf::Font museo;
    sf::Text waypointText, healthText, titleText, credit, deathText;
    char health;
    char maxHealth;
    float width;
    float height;
    int score;
    float windowCenterX, windowCenterY;
    std::vector<Caption> captions;
    sf::Clock wpTextDisplayTimer, healthDisplayTimer;
    int wpTextFadeSeconds, healtTextFadeSeconds;
    
public:
    FontController(sf::View, float, float);
    void update(sf::RenderWindow&, float, float);
    void setWaypointText(int);
    void setZoneText(char);
    void print(sf::RenderWindow&);
    void updateHealth(char);
    void updateMaxHealth(char);
    void drawTitle(unsigned char, sf::RenderWindow&);
    void drawDeathText(unsigned char, sf::RenderWindow&);
    char getMaxHealth() const;
    sf::Text * getTitle();
    sf::Text * getDeathText();
    void addCaption(float, float, const char *);
    std::vector<sf::Text *>* getCaptions();
    void terminateCaptions();
    void resetWPText();
    void resetHPText();
};
#endif /* FontController_hpp */

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
    sf::Texture zoneTextTxtr[2];
    sf::Sprite zoneTextSpr;
    sf::Texture nums[11];
    sf::Texture scoreNums[10];
    std::vector<sf::Sprite> scoreString;
    sf::Texture healthText;
    sf::Texture limiterText;
    std::vector<sf::Sprite> textCharacters;
    std::vector<sf::Sprite> textNums;
    sf::Sprite sprHealthText;
    sf::Sprite sprLimiterText;
    sf::Texture energyTxtr;
    sf::Sprite energySprite;
    float alpha;
    sf::Texture healthTexture[2];
    sf::CircleShape healthFull[10];
    sf::CircleShape healthEmpty[10];
    char health;
    char maxHealth;
    bool doRecolor;
    char colorState;
    float width;
    float height;
    int score;
    
public:
    FontController();
    void setWaypointText(int, float, float);
    void setZoneText(char);
    void print(sf::RenderWindow&);
    void clear();
    void updateHealth(char);
    void updateMaxHealth(char);
    void recolor(char);
    void updateScore(int);
    int getScore();
    void zeroScore();
    char getMaxHealth();
};
#endif /* FontController_hpp */

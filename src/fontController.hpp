//
//  FontController.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/21/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef fontController_hpp
#define fontController_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include "ResourcePath.hpp"

class FontController {
private:
	sf::Texture texture;
	sf::View fontView;
	// The fonts to be used by the font controller
	sf::Font cornerstone;
	sf::Text waypointText, titleText, credit, deathText, scoreText, continueText, healthNumText;
	char health;
	char maxHealth;
	int score;
	float windowCenterX, windowCenterY;
	sf::Clock wpTextDisplayTimer, healthDisplayTimer, scoreDisplayTimer;
	sf::ConvexShape heart;
	
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
        void reset();
	void resetWPText();
	void resetHPText();
	void resetSCText();
	void updateScore(int);
	int getScore();
};
#endif /* FontController_hpp */

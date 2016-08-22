//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once
#ifndef fontController_hpp
#define fontController_hpp

#include <SFML/Graphics.hpp>
#include "resourceHandler.hpp"
#include "colors.hpp"

//
// TODO: Urgent: Refactor, put in ui:: namespace, and rename to FrontEnd
//

class FontController {
private:
	sf::Texture texture;
	sf::View fontView;
	sf::Text waypointText, titleText, deathText, scoreText, healthNumText;
	sf::Text resumeText, settingsText, quitText;
	char maxHealth, health;
	bool healthModified, scoreModified;
	int score;
	float windowCenterX, windowCenterY;
	sf::Clock wpTextDisplayTimer, healthDisplayTimer, scoreDisplayTimer;
	sf::ConvexShape heart;
	sf::CircleShape coin;
	float barWidth;
	sf::RectangleShape powerupBarFront, powerupBarBack;
	
public:
	enum class Text {
		resumeText, settingsText, quitText, healthNumText, scoreText, waypointText, heart, coin
	};
	FontController(sf::View, float, float);
	void setWaypointText(int);
	void setZoneText(char);
	void print(sf::RenderWindow &);
	void setTextAlpha(uint8_t, Text);
	void setTextOffset(float, float, Text);
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
	void setBarWidth(float);
};
#endif /* FontController_hpp */

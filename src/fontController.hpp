//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
//                                                                        //
// This program is free software: you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or      //
// (at your option) any later version.                                    //
//                                                                        //
// This program is distributed in the hope that it will be useful,        //
// but WITHOUT ANY WARRANTY; without even the implied warranty of         //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
// GNU General Public License for more details.                           //
//                                                                        //
// You should have received a copy of the GNU General Public License      //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
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

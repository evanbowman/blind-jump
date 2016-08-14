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
#include <SFML/Graphics.hpp>
#include "camera.hpp"
#include "resourceHandler.hpp"

#define STARMAP_SIZE 7

class backgroundHandler {
private:
	sf::Texture foregroundTreesTxtr;
	sf::Sprite foregroundTreesSpr;
	sf::Texture bkgStars;
	sf::Texture bkgStarsFar;
	sf::Sprite bkgSprite;
	sf::Sprite stars[STARMAP_SIZE][STARMAP_SIZE];
	sf::Sprite starsFar[STARMAP_SIZE][STARMAP_SIZE];
	sf::CircleShape planet[2];
	sf::RectangleShape solidBkg;
	float xOffset, xOffPrev;
	float yOffset, yOffPrev;
	float posX;
	float posY;
	float windowW;
	float windowH;
	unsigned char workingSet;
	sf::RenderTexture rt;
	
public:
	backgroundHandler();
	void drawBackground(sf::RenderTexture&, const sf::View &, const Camera &);
	void drawForeground(sf::RenderTexture&);
	void setOffset(float, float);
	void setPosition(float, float);
	void giveWindowSize(float, float);
	void setBkg(unsigned char);
};

//
//  backgroundHandler.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/11/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef backgroundHandler_hpp
#define backgroundHandler_hpp

#include <SFML/Graphics.hpp>

#define STARMAP_SIZE 7

class backgroundHandler {
private:
	sf::Texture foregroundTreesTxtr;
	sf::Sprite foregroundTreesSpr;
	sf::Texture bkgLayer[3];
	sf::Texture bkgStars;
	sf::Texture bkgStarsFar;
	sf::Sprite bkgSprite[3];
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
	void drawBackground(sf::RenderTexture&);
	void drawForeground(sf::RenderTexture&);
	void setOffset(float, float);
	void setPosition(float, float);
	void giveWindowSize(float, float);
	void setBkg(unsigned char);
};

#endif /* backgroundHandler_hpp */

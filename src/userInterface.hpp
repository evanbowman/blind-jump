//
//  userInterface.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/22/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef userInterface_hpp
#define userInterface_hpp

#include "SFML/Graphics.hpp"
#include "fontController.hpp"
#include "effectsController.hpp"
#include "inputController.hpp"
#include <array>

// This part of the code is so tied to the aesthetic appearance of the game,
// making it difficult to describe. If there is a constant and you can't tell
// where it came from, it't purpose is that it makes an effect move across
// the screen or fade in at a rate that I think looks good
class Player;

class userInterface {	
public:
	userInterface(float, float);
	void drawMenu(sf::RenderWindow&, Player*, FontController&, effectsController&, float, float, InputController*, sf::Time&);
	void addItem(char, effectsController&, float, float, FontController&, Player&);
	
	uint8_t selectedColumn;
	std::array<unsigned char, 3> rowIndices;
	
	// Function to display the death sequence
	void dispDeathSeq();
	bool isComplete();
	bool canHeal;
	
	float getDesaturateAmount();
	
	bool isVisible();
	
	// Function to reset the ui controller
	void reset();
	void setEnemyValueCount(int);

	bool blurEnabled();
	bool desaturateEnabled();
	float getBlurAmount();

	void setView(sf::View *);
	
private:
	enum class State {
		closed,
		deathScreenEntry,
		deathScreen,
		deathScreenExit,
		statsScreen,
		complete
	};
	State state;
	float xPos, yPos;
	
	int32_t timer, timerAlt;

	float textAlpha;
	
	float zoomDegree;
	
	float blurAmount, desaturateAmount;

	sf::View * pWorldView, cachedView;
	
	sf::Texture selectorShadowTexture;
	sf::Sprite selectorShadowSprite;
	
	std::vector<sf::Sprite> textToDisplay;
};
#endif /* userInterface_hpp */

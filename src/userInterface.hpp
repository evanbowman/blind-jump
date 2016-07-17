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

class Player;

class UserInterface {	
public:
	UserInterface(float, float);
	void update(sf::RenderWindow &, Player &, FontController &, InputController *, const sf::Time &);
	void addItem(char, EffectGroup &, float, float, FontController &, Player &);
	
	void dispDeathSeq();
	bool isComplete();
	bool canHeal;

	bool isOpen() const;
	
	float getDesaturateAmount();
	
	bool isVisible();
	
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
		complete,
		menuScreenEntry,
		menuScreenExit,
		menuScreen
	};
	State state;
	float xPos, yPos;
	
	int32_t timer, timerAlt;

	float textAlpha;
	
	float blurAmount, desaturateAmount;

	sf::View * pWorldView, cachedView;
	
	sf::Texture selectorShadowTexture;
	sf::Sprite selectorShadowSprite;
	
	std::vector<sf::Sprite> textToDisplay;
};
#endif /* userInterface_hpp */

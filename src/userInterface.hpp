//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "fontController.hpp"
#include "effectsController.hpp"
#include "inputController.hpp"
#include "easingTemplates.hpp"
#include "shutdownSignal.hpp"
#include "powerup.hpp"

class Player;

class UserInterface {	
public:
	enum class State {
		closed,
		deathScreenEntry,
		deathScreen,
		deathScreenExit,
		statsScreen,
		complete,
		menuScreenEntry,
		menuScreenExit,
		menuScreen,
		customizeKeyboardScreen,
		customizeJoystickScreen,
		settingsScreen
	};
	UserInterface();
	void update(Player &, FontController &, InputController *, const sf::Time &);
	void draw(sf::RenderWindow &, FontController &);
	void dispDeathSeq();
	bool isComplete();
	bool canHeal;
	bool isOpen() const;
	float getDesaturateAmount();
	State getState() const;
	void reset();
	void setEnemyValueCount(int);
	bool blurEnabled();
	bool desaturateEnabled();
	float getBlurAmount();
	void resetPowerupBar(Powerup);
	Powerup getCurrentPowerup() const;
	
private:
	State state;
	Powerup powerup;
	int selectorPosition;
	int32_t timer, timerAlt;
	int64_t powerupTimer;
	bool dispPowerupBar;
	float blurAmount, desaturateAmount;
};

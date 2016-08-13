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
	void setView(sf::View *);
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
	sf::View * pWorldView, cachedView;
};

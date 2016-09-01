//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "effectsController.hpp"
#include "inputController.hpp"
#include "easingTemplates.hpp"
#include "shutdownSignal.hpp"
#include "powerup.hpp"
#include "resourceHandler.hpp"
#include "colors.hpp"

class Player;

namespace ui {
	class Frontend {
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
			resumeText,
			settingsText,
			quitText,
			healthNumText,
			scoreText,
			waypointText,
			heart,
			coin
	    };
		Frontend(sf::View, float, float);
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

	class Backend {	
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
		Backend();
		void update(Player &, ui::Frontend &, InputController *, const sf::Time &);
		void draw(sf::RenderWindow &, ui::Frontend &);
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
}

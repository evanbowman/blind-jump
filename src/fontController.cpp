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

#include "fontController.hpp"

#define healthLimit 10
#define HEALTH_TEXT_FADE_SECONDS 3
#define SCORE_TEXT_FADE_SECONDS 3
#define WAYPOINT_TEXT_FADE_SECONDS 3

FontController::FontController(sf::View fontView, float x, float y) {
	// Store the view to use when drawing fonts
	this->fontView = fontView;
	
	windowCenterX = x;
	windowCenterY = y;
	
	maxHealth = 4;
	score = 0;

	float scale;
	if (fontView.getSize().y < fontView.getSize().x) {
		scale = fontView.getSize().y;
	} else {
		scale = fontView.getSize().x;
	}
	
	// A heart shape!
	heart.setPointCount(20);
	heart.setPoint(0, sf::Vector2f(38, 72));
	heart.setPoint(1, sf::Vector2f(8, 44));
	heart.setPoint(2, sf::Vector2f(4, 38));
	heart.setPoint(3, sf::Vector2f(0, 30));
	heart.setPoint(4, sf::Vector2f(0, 20));
	heart.setPoint(5, sf::Vector2f(2, 8));
	heart.setPoint(6, sf::Vector2f(8, 2));
	heart.setPoint(7, sf::Vector2f(18, 0));
	heart.setPoint(8, sf::Vector2f(24, 0));
	heart.setPoint(9, sf::Vector2f(32, 4));
	heart.setPoint(10, sf::Vector2f(38, 10));
	heart.setPoint(11, sf::Vector2f(44, 4));
	heart.setPoint(12, sf::Vector2f(52, 0));
	heart.setPoint(13, sf::Vector2f(58, 0));
	heart.setPoint(14, sf::Vector2f(68, 2));
	heart.setPoint(15, sf::Vector2f(74, 8));
	heart.setPoint(16, sf::Vector2f(76, 20));
	heart.setPoint(17, sf::Vector2f(76, 30));
	heart.setPoint(18, sf::Vector2f(72, 38));
	heart.setPoint(19, sf::Vector2f(68, 44));
	heart.setScale(0.0005f * scale, 0.0005f * scale);
	heart.setOrigin(heart.getLocalBounds().width / 2, heart.getLocalBounds().height / 2);
	
	coin.setFillColor(sf::Color::White);
	coin.setPointCount(20);
	coin.setRadius(0.018f * scale);
	coin.setOrigin(coin.getLocalBounds().width / 2, coin.getLocalBounds().height / 2);
	
	const sf::Font & cornerstone = globalResourceHandler.getFont(ResourceHandler::Font::cornerstone);

	auto initText = [](const sf::Font & font, sf::Text & text, const std::string string, float size) {
		text.setFont(font);
		text.setCharacterSize(size);
		text.setString(string);
	};

	// Worth noting that cornerstone is an all caps font anyway, but in case I change it...
	
	initText(cornerstone, waypointText, std::string("WAYPOINT-1"), 0.055f * scale);
	waypointText.setPosition(16, 0);

	initText(cornerstone, scoreText, std::string("0: "), 0.032f * scale);
	
	healthNumText.setString(std::to_string(4) + " / " + std::to_string(static_cast<int>(maxHealth)) + ": ");
	healthNumText.setCharacterSize(0.032 * scale);
	healthNumText.setFont(cornerstone);

	initText(cornerstone, resumeText, std::string("RESUME"), 0.085f * scale);
	resumeText.setColor(sf::Color(255, 255, 255, 0));
	
	initText(cornerstone, settingsText, std::string("SETTINGS"), 0.085 * scale);
	settingsText.setColor(sf::Color(255, 255, 255, 0));
	
	initText(cornerstone, quitText, std::string("QUIT"), 0.085 * scale);
	quitText.setColor(sf::Color(255, 255, 255, 0));
	
	initText(cornerstone, titleText, std::string("BLIND JUMP"), 0.115f * scale);
	titleText.setPosition(fontView.getSize().x / 2 - titleText.getLocalBounds().width / 2, fontView.getSize().y / 8 - titleText.getLocalBounds().height / 2);
	titleText.setColor(sf::Color(255, 255, 255, 0));

	initText(cornerstone, deathText, std::string("YOU DIED"), 0.115 * scale);
	deathText.setColor(sf::Color(231, 26, 83));
	deathText.setPosition(fontView.getSize().x / 2 - deathText.getLocalBounds().width / 2, fontView.getSize().y / 12 - deathText.getLocalBounds().height / 2);
}

void FontController::setTextOffset(float xOffset, float yOffset, FontController::Text text) {
	float scale;
	if (fontView.getSize().y < fontView.getSize().x) {
		scale = fontView.getSize().y;
	} else {
		scale = fontView.getSize().x;
	}
	switch (text) {
	case Text::resumeText:
		resumeText.setPosition(xOffset * scale + fontView.getSize().x / 2 - resumeText.getLocalBounds().width / 2, fontView.getSize().y / 2.8f - resumeText.getLocalBounds().height / 2 + yOffset * scale);
		break;

	case Text::settingsText:
		settingsText.setPosition(xOffset * scale + fontView.getSize().x / 2 - settingsText.getLocalBounds().width / 2, resumeText.getPosition().y + settingsText.getLocalBounds().height * 2 + yOffset * scale);
		break;

	case Text::quitText:
		quitText.setPosition(xOffset * scale + fontView.getSize().x / 2 - quitText.getLocalBounds().width / 2, settingsText.getPosition().y + quitText.getLocalBounds().height * 2 + yOffset * scale);
		break;

	default:
		// TODO: handle other cases...
		break;
	}
}

void FontController::setTextAlpha(uint8_t alpha, FontController::Text text) {
	switch (text) {
	case Text::resumeText:
		resumeText.setColor(sf::Color(255, 255, 255, alpha));
		break;

	case Text::settingsText:
		settingsText.setColor(sf::Color(255, 255, 255, alpha));
		break;

	case Text::quitText:
		quitText.setColor(sf::Color(255, 255, 255, alpha));
		break;

	case Text::healthNumText:
		healthNumText.setColor(sf::Color(255, 255, 255, alpha));
		break;

	case Text::scoreText:
		scoreText.setColor(sf::Color(255, 255, 255, alpha));
		break;

	case Text::waypointText:
		waypointText.setColor(sf::Color(255, 255, 255, alpha));
		break;

	case Text::heart:
		heart.setFillColor(sf::Color(255, 255, 255, alpha));
		break;

	case Text::coin:
		coin.setFillColor(sf::Color(255, 255, 255, alpha));
		break;
	}
}

void FontController::reset() {
	score = 0;
}

void FontController::setWaypointText(int level) {
	heart.setPosition(fontView.getSize().x - heart.getLocalBounds().width / 2, heart.getLocalBounds().height / 1.8);
	//coin.setPosition(fontView.getSize().x - coin.getLocalBounds().width, heart.getPosition().y + coin.getLocalBounds().height);
	coin.setPosition(heart.getPosition().x, heart.getPosition().y + coin.getLocalBounds().height * 1.25);
	coin.setFillColor(sf::Color(255, 255, 255, 0));
	healthNumText.setPosition(fontView.getSize().x - healthNumText.getLocalBounds().width - heart.getLocalBounds().width, healthNumText.getLocalBounds().height);
	healthNumText.setColor(sf::Color(255, 255, 255, 0));
	heart.setFillColor(sf::Color(255, 255, 255, 0));
	scoreText.setPosition(fontView.getSize().x - scoreText.getLocalBounds().width - fontView.getSize().x * 0.015 - heart.getLocalBounds().width, scoreText.getLocalBounds().height * 3);
	std::string str = "WAYPOINT-";
	str += std::to_string(level);
	waypointText.setString(str);
	// Reset the color, it will fade out
	waypointText.setColor(sf::Color::White);
	scoreText.setColor(sf::Color(255, 255, 255, 4));
	if (level != 0) {
		wpTextDisplayTimer.restart();
		healthDisplayTimer.restart();
		scoreDisplayTimer.restart();
	}
}

int FontController::getScore() {
	return score;
}

void FontController::print(sf::RenderWindow & window) {
	// Set the correct view, so not to blur the fonts
	window.setView(fontView);
	// Slowly fade out the  waypoint text
	sf::Color c = waypointText.getColor();
	if (c.a > 5) {
		if (wpTextDisplayTimer.getElapsedTime().asSeconds() > WAYPOINT_TEXT_FADE_SECONDS) {
			c.a -= 4;
			waypointText.setColor(c);
		}
		window.draw(waypointText);
	}

	c = healthNumText.getColor();
	if (c.a > 5) {
		if (healthDisplayTimer.getElapsedTime().asSeconds() > HEALTH_TEXT_FADE_SECONDS) {
			c.a -= 4;
			healthNumText.setColor(c);
			heart.setFillColor(c);
			heart.setOutlineColor(c);
		}
		
		window.draw(healthNumText);
		window.draw(heart);
	}
	
	c = scoreText.getColor();
	if (c.a > 5) {
		if (scoreDisplayTimer.getElapsedTime().asSeconds() > SCORE_TEXT_FADE_SECONDS) {
			c.a -= 4;
			scoreText.setColor(c);
			coin.setFillColor(c);
		}
		window.draw(scoreText);
		window.draw(coin);
	}

	c = resumeText.getColor();
	if (c.a > 0) {
		window.draw(resumeText);
	}

	c = settingsText.getColor();
	if (c.a > 0) {
		window.draw(settingsText);
	}

	c = quitText.getColor();
	if (c.a > 0) {
		window.draw(quitText);
	}
}

void FontController::resetWPText() {
	waypointText.setColor(sf::Color::White);
	wpTextDisplayTimer.restart();
}

void FontController::resetSCText() {
	scoreText.setColor(sf::Color::White);
	coin.setFillColor(sf::Color::White);
	scoreDisplayTimer.restart();
}

void FontController::updateScore(int offset) {
	score += offset;
	scoreText.setString(std::to_string(score) + " :");
	scoreText.setPosition(fontView.getSize().x - scoreText.getLocalBounds().width - fontView.getSize().x * 0.015 - heart.getLocalBounds().width, scoreText.getLocalBounds().height * 3);
	resetSCText();
}

void FontController::resetHPText() {
	healthNumText.setColor(sf::Color::White);
	heart.setFillColor(sf::Color::White);
	heart.setOutlineColor(sf::Color::White);
	healthDisplayTimer.restart();
}

void FontController::update(sf::RenderWindow & window, float xOffset, float yOffset) {
	window.setView(fontView);
	// hmmm... maybe some of FontController::print() should be here... TODO
}

void FontController::drawTitle(unsigned char alpha, sf::RenderWindow& window) {
	titleText.setColor(sf::Color(255, 255, 255, alpha));
	window.setView(fontView);
	window.draw(titleText);
}

void FontController::drawDeathText(unsigned char alpha, sf::RenderWindow & window) {
	deathText.setColor(sf::Color(231, 26, 83, alpha));
	window.setView(fontView);
	window.draw(deathText);
}

sf::Text* FontController::getTitle() {
	return &titleText;
}

void FontController::updateHealth(char health) {
	healthNumText.setString(std::to_string(static_cast<int>(health)) + " / " + std::to_string(static_cast<int>(maxHealth)) + " :");
	healthNumText.setPosition(fontView.getSize().x - healthNumText.getLocalBounds().width - fontView.getSize().x * 0.015 - heart.getLocalBounds().width, healthNumText.getLocalBounds().height);
}

void FontController::updateMaxHealth(char _maxHealth, char health) {
	maxHealth = _maxHealth;
	healthNumText.setString(std::to_string(static_cast<int>(health)) + " / " + std::to_string(static_cast<int>(maxHealth)) + " :");
	resetHPText();
}

char FontController::getMaxHealth() const {
	return maxHealth;
}

sf::Text * FontController::getDeathText() {
	return &deathText;
}

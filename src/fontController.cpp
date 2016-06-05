//
//  FontController.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/21/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//
//

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

	// Load all of the game fonts into memory
	cornerstone.loadFromFile(resourcePath() + "Cornerstone.ttf");
	
	health = 4;
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

	coin.setFillColor(sf::Color::White);
	coin.setPointCount(20);
	coin.setRadius(0.018f * scale);
	
	// Set the waypoint text
	waypointText.setFont(cornerstone);
	waypointText.setString("WAYPOINT-1");
	waypointText.setCharacterSize(0.055 * scale);
	waypointText.setPosition(16, 0);
	
	scoreText.setString("0 :");
	scoreText.setCharacterSize(0.032 * scale);
	scoreText.setFont(cornerstone);
	
	healthNumText.setString(std::to_string(static_cast<int>(health)) + " / " + std::to_string(static_cast<int>(maxHealth)) + ": ");
	healthNumText.setCharacterSize(0.032 * scale);
	healthNumText.setFont(cornerstone);
	
	continueText.setString("Press z to continue");
	continueText.setCharacterSize(0.026 * scale);
	continueText.setFont(cornerstone);
	
	titleText.setString("Blind Jump");
	titleText.setCharacterSize(0.115 * scale);
	titleText.setFont(cornerstone);
	titleText.setPosition(fontView.getSize().x / 2 - titleText.getLocalBounds().width / 2, fontView.getSize().y / 8 - titleText.getLocalBounds().height / 2);
	titleText.setColor(sf::Color(255, 255, 255, 0));
	
	deathText.setCharacterSize(0.115 * scale);
	deathText.setFont(cornerstone);
	deathText.setString("YOU DIED");
	deathText.setColor(sf::Color(231, 26, 83));
	deathText.setPosition(fontView.getSize().x / 2 - deathText.getLocalBounds().width / 2, fontView.getSize().y / 12 - deathText.getLocalBounds().height / 2);
}

void FontController::reset() {
  score = 0;
}

void FontController::setWaypointText(int level) {
	heart.setPosition(fontView.getSize().x - heart.getLocalBounds().width, heart.getLocalBounds().height / 2.5);
	//coin.setPosition(fontView.getSize().x - coin.getLocalBounds().width, heart.getPosition().y + coin.getLocalBounds().height);
	coin.setPosition(fontView.getSize().x - coin.getLocalBounds().width * 1.75f, heart.getLocalBounds().height);
	coin.setFillColor(sf::Color(255, 255, 255, 0));
	healthNumText.setPosition(fontView.getSize().x - healthNumText.getLocalBounds().width - fontView.getSize().x * 0.015 - heart.getLocalBounds().width, healthNumText.getLocalBounds().height);
	healthNumText.setColor(sf::Color(255, 255, 255, 0));
	heart.setFillColor(sf::Color(255, 255, 255, 0));
	scoreText.setPosition(fontView.getSize().x - scoreText.getLocalBounds().width - fontView.getSize().x * 0.015 - heart.getLocalBounds().width, scoreText.getLocalBounds().height * 3);
	std::string str = "WAYPOINT-";
	str += std::to_string(level);
	waypointText.setString(str);
	// Reset the color, it will fade out
	waypointText.setColor(sf::Color::White);
	scoreText.setColor(sf::Color(255, 255, 255, 4));
	wpTextDisplayTimer.restart();
	healthDisplayTimer.restart();
	scoreDisplayTimer.restart();
}

void FontController::setZoneText(char zone) {
	switch (zone) {
		case 0:
			//zoneTextSpr.setTexture(zoneTextTxtr[0]);
			break;
			
		case 1:
			//zoneTextSpr.setTexture(zoneTextTxtr[1]);
			break;
			
		default:
			break;
	}
}

int FontController::getScore() {
	return score;
}

void FontController::print(sf::RenderWindow& window) {
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
	// Set health equal to the input parameter or the max health, depending on which is lower
	this->health = std::min(health, maxHealth);
	healthNumText.setString(std::to_string(static_cast<int>(health)) + " / " + std::to_string(static_cast<int>(maxHealth)) + " :");
	healthNumText.setPosition(fontView.getSize().x - healthNumText.getLocalBounds().width - fontView.getSize().x * 0.015 - heart.getLocalBounds().width, healthNumText.getLocalBounds().height);
}

void FontController::updateMaxHealth(char health) {
	maxHealth = health;
	healthNumText.setString(std::to_string(static_cast<int>(health)) + " / " + std::to_string(static_cast<int>(maxHealth)) + " :");
	resetHPText();
}

char FontController::getMaxHealth() const {
	return maxHealth;
}

sf::Text * FontController::getDeathText() {
	return &deathText;
}

//
//  main.cpp
//  BlindJump
//
//  Created by Evan Bowman on 10/9/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.hpp"
#include "backgroundHandler.hpp"
#include <cmath>
#include <SFML/Window.hpp>
#include "gameMap.hpp"
#include "ResourcePath.hpp"
#include "inputController.hpp"
	
int main(int, char const**) {
	srand(static_cast<unsigned int>(time(0)));

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	
	float aspectRatio = static_cast<float>(desktop.width) / static_cast<float>(desktop.height);
	float windowWidth = 450.f;
	float windowHeight = 450.f;
	if (aspectRatio > 1.f) {
		float windowAspect;
		do {
			windowWidth += 0.025f;
			windowHeight -= 0.025f;
			windowAspect = windowWidth / windowHeight;
		}
		while (fabs(aspectRatio - windowAspect) > 0.005f);
	} else {
		float windowAspect;
		do {
			windowWidth -= 0.025f;
			windowHeight += 0.025f;
			windowAspect = windowWidth / windowHeight;
		}
		while (fabs(aspectRatio - windowAspect) > 0.005f);
	}
	
	sf::Texture vignetteTexture;
	vignetteTexture.loadFromFile(resourcePath() + "vignetteMask.png");
	vignetteTexture.setSmooth(true);
	
	// Wraps input from keyboard and gamepad
	InputController input;
	
	// Don't want the fonts to be scaled and blurry, so define another view for drawing them
	sf::View fontView(sf::FloatRect(0, 0, desktop.width, desktop.height));
	sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));
	FontController fonts(fontView, windowWidth / 2, windowHeight / 2);
	
	//Initialize the map
	GameMap Map(windowWidth, windowHeight, &vignetteTexture, &input, &fonts);
	
	// Set up the window context settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 6;
	
	sf::RenderWindow window(sf::VideoMode(desktop.width, desktop.height), "Blind Jump", sf::Style::Fullscreen, settings);
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	// Set the Icon
	sf::Image icon;
	if (!icon.loadFromFile(resourcePath() + "icon.png")) {
		return EXIT_FAILURE;
	}
	
	// Set the game icon
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
	sf::Clock gameClock;
	sf::Time elapsedTime;
	
	// Start the game loop
	while (window.isOpen()) {
		// Process events
		sf::Event event;
		while (window.pollEvent(event)) {
			// Close window: exit
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			// Escape pressed: exit
			if (event.type == sf::Event::KeyPressed/* && event.key.code == sf::Keyboard::Escape*/) {
				switch(event.key.code) {
				case sf::Keyboard::Escape:
					window.close();
					break;

				case sf::Keyboard::Left:
					input.setLeft(true);
					break;

				case sf::Keyboard::Right:
					input.setRight(true);
					break;

				case sf::Keyboard::Up:
					input.setUp(true);
					break;

				case sf::Keyboard::Down:
					input.setDown(true);
					break;

				case sf::Keyboard::X:
					input.setX(true);
					break;

				case sf::Keyboard::Z:
					input.setZ(true);
					break;

				case sf::Keyboard::C:
					input.setC(true);
					break;

				default:
					break;
				}
			} else if (event.type == sf::Event::KeyReleased) {
				switch(event.key.code) {
				case sf::Keyboard::Left:
					input.setLeft(false);
					break;

				case sf::Keyboard::Right:
					input.setRight(false);
					break;

				case sf::Keyboard::Up:
					input.setUp(false);
					break;

				case sf::Keyboard::Down:
					input.setDown(false);
					break;

				case sf::Keyboard::X:
					input.setX(false);
					break;

				case sf::Keyboard::Z:
					input.setZ(false);
					break;

				case sf::Keyboard::C:
					input.setC(false);
					break;

				default:
					break;
				}
			}
		}
		
		// Clear screen
		window.clear();

		window.setView(view);
		
		elapsedTime = gameClock.restart();
		Map.update(window, elapsedTime);
		
		if (Map.getTeleporterCond()) {
			Map.Reset();
		}
		
		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}


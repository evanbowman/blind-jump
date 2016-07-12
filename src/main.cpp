
//
//  main.cpp
//  BlindJump
//
//  Created by Evan Bowman on 10/9/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "backgroundHandler.hpp"
#include <cmath>
#include <SFML/Window.hpp>
#include "scene.hpp"
#include "ResourcePath.hpp"
#include "inputController.hpp"
#include "resourceHandler.hpp"
#include <iostream>

// Many classes need to access the resource handler, and its accessors return only const references
ResourceHandler globalResourceHandler;

int main(int argc, char * argv[]) {
	srand(static_cast<unsigned int>(time(0)));

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	
	float aspectRatio = static_cast<float>(sf::VideoMode::getDesktopMode().width) / static_cast<float>(sf::VideoMode::getDesktopMode().height);
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
	
	if(!globalResourceHandler.load()) {
		return EXIT_FAILURE;
	}
	
	// Wraps input from keyboard and gamepad
	InputController input;
	
	// Don't want the fonts to be scaled and blurry, so define another view for drawing them
	sf::View fontView(sf::FloatRect(0, 0, desktop.width, desktop.height));
	sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));
	FontController fonts(fontView, windowWidth / 2, windowHeight / 2);
	
	//Initialize the map
	Scene Map(windowWidth, windowHeight, &input, &fonts);
	
	// Set up the window context settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 6;
	
	sf::RenderWindow window(sf::VideoMode(desktop.width, desktop.height), "Blind Jump", sf::Style::Fullscreen, settings);
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(80);
	
	sf::Image icon;
	if (!icon.loadFromFile(resourcePath() + "gameIcon.png")) {
		return EXIT_FAILURE;
	}
	
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
	sf::Clock gameClock;
	sf::Time elapsedTime;

	while (window.isOpen()) {
		input.update(window);
		
		window.clear();
		
		window.setView(view);
		
		elapsedTime = gameClock.restart();
		if (input.isFocused()) {
			Map.update(window, elapsedTime);
		}
		
		if (Map.getTeleporterCond()) {
			Map.Reset();
		}

		window.display();
	}

	return EXIT_SUCCESS;
}


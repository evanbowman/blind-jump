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

// Start Date: 10/9/15
// End Date: 

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "backgroundHandler.hpp"
#include <cmath>
#include <SFML/Window.hpp>
#include "game.hpp"
#include "ResourcePath.hpp"
#include "inputController.hpp"
#include "resourceHandler.hpp"
#include <iostream>
#include "rng.hpp"
#include <thread>

// Many classes need to access the resource handler, and its accessors return only const references
ResourceHandler globalResourceHandler;

std::mt19937 globalRNG;

int main(int argc, char * argv[]) {
	seedRNG();
	
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	
	float aspectRatio = static_cast<float>(sf::VideoMode::getDesktopMode().width) / static_cast<float>(sf::VideoMode::getDesktopMode().height);
	float windowWidth = 450.f;
	float windowHeight = 450.f;
	
	float windowAspect;

	if (aspectRatio > 1.f) {
		do {
			windowWidth += 0.025f;
			windowHeight -= 0.025f;
			windowAspect = windowWidth / windowHeight;
		}
		while (fabs(aspectRatio - windowAspect) > 0.005f);
	} else {
		do {
			windowWidth -= 0.025f;
			windowHeight += 0.025f;
			windowAspect = windowWidth / windowHeight;
		}
		while (fabs(aspectRatio - windowAspect) > 0.005f);
	}
	
	if (globalResourceHandler.load()) {
		return EXIT_FAILURE;
	}
	
	// Wraps input from keyboard and gamepad
	InputController input;
	
	// Don't want the fonts to be scaled and blurry, so define another view for drawing them
	sf::View fontView(sf::FloatRect(0, 0, desktop.width, desktop.height));
	sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));
	FontController fonts(fontView, windowWidth / 2, windowHeight / 2);
	
	//Initialize the map
	Game game(windowWidth, windowHeight, &input, &fonts);
	
	// Set up the window context settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 6;
	
	sf::RenderWindow window(sf::VideoMode(desktop.width, desktop.height), "Blind Jump", sf::Style::Fullscreen, settings);
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(80);

	if (sf::Joystick::isConnected(0)) {
		input.mapJsById();
	}
	
	sf::Image icon;
	if (!icon.loadFromFile(resourcePath() + "gameIcon.png")) {
		return EXIT_FAILURE;
	}
	
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
	sf::Clock gameClock;
	sf::Time elapsedTime;

	// TODO: update visuals on a separate thread (sounds tough!)
	// auto updateVisuals = [](Game * pGame, sf::RenderWindow * pWindow) {
	// 	while (pWindow->isOpen()) {
	// 		pGame->draw(*pWindow);
	// 	}
	// };
	
	// std::thread graphicsThread(updateVisuals, &game, &window);
	
	while (window.isOpen()) {
		// Do not update the inputController to check for input while the user is re-mapping the keys
		if (game.getUI().getState() != UserInterface::State::customizeKeyboardScreen &&
			game.getUI().getState() != UserInterface::State::customizeJoystickScreen) {
			input.update(window);
		}
		
		window.clear();
		
		window.setView(view);
		
		elapsedTime = gameClock.restart();
		if (input.isFocused()) {
			game.update(window, elapsedTime);
			game.draw(window, elapsedTime);
		}
		
		if (game.getTeleporterCond()) {
			game.Reset();
		}

		window.display();
	}

	// graphicsThread.join();

	return 0;
}


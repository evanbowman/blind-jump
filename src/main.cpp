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
#include <thread>
#include <cmath>
#include <SFML/Window.hpp>
#include "player.hpp"
#include "backgroundHandler.hpp"
#include "game.hpp"
#include "ResourcePath.hpp"
#include "inputController.hpp"
#include "resourceHandler.hpp"
#include "rng.hpp"
#include "aspectScaling.hpp"
#include "alias.hpp"

ResourceHandler globalResourceHandler;

std::mt19937 globalRNG;

int main(int argc, char * argv[]) {
	seedRNG();
	if (globalResourceHandler.load()) return EXIT_FAILURE;
	// Since the graphics are pixel art it's okay to use upsampled textures for everything except font rendering
	sf::Vector2f drawableRegionSize = getDrawableRegionSize();
	sf::ContextSettings settings;
	settings.antialiasingLevel = 6;
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Blind Jump", sf::Style::Fullscreen, settings);
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);
	InputController input;
	sf::View fontView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	sf::View view(sf::FloatRect(0, 0, drawableRegionSize.x, drawableRegionSize.y));
	FontController fonts(fontView, drawableRegionSize.x / 2, drawableRegionSize.y / 2);
	Game game(drawableRegionSize.x, drawableRegionSize.y, &input, &fonts);
	sf::Clock gameClock;
	duration logicUpdateDelta;
	try {
		std::thread graphicsThread([](Game * pGame, sf::RenderWindow * pWindow, sf::View * pView) {
		    while (pWindow->isOpen()) {
				pWindow->clear();
				pWindow->setView(*pView);
				pGame->draw(*pWindow);
				pWindow->display();
			}
		}, &game, &window, &view);
		while (window.isOpen()) {
			time_point start = high_resolution_clock::now();
			sf::Time elapsedTime = gameClock.restart(); // TODO: use chrono clock instead
			// Do not update the inputController to check for input while the user is re-mapping the keys
			if (game.getUI().getState() != UserInterface::State::customizeKeyboardScreen &&
				game.getUI().getState() != UserInterface::State::customizeJoystickScreen) {
				input.update(window);
			}
			if (input.isFocused()) {
				game.update(window, elapsedTime);
			}
			time_point stop = high_resolution_clock::now();
			logicUpdateDelta = std::chrono::duration_cast<nanoseconds>(stop - start);
			static const microseconds logicUpdateDelay(1000);
			std::this_thread::sleep_for(logicUpdateDelay - logicUpdateDelta);
		}
		graphicsThread.join();
	} catch (std::system_error err) {
		// TODO: Handle possible error in thread construction
	} catch (...) {
		// TODO: Handle other exceptional cases
	}
	return 0;
}


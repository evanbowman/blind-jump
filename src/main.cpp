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
#include <cmath>
#include <SFML/Window.hpp>
#include <exception>
#include <iostream>
#include <stdexcept>
#include "smartThread.hpp"
#include "player.hpp"
#include "backgroundHandler.hpp"
#include "game.hpp"
#include "ResourcePath.hpp"
#include "inputController.hpp"
#include "resourceHandler.hpp"
#include "rng.hpp"
#include "aspectScaling.hpp"
#include "alias.hpp"
#include "util.hpp"
#include "shutdownSignal.hpp"
#ifdef LINUX
#include <X11/Xlib.h>
#endif

namespace global {
	std::mt19937 RNG;
	ResourceHandler * resourceHandlerPtr = nullptr;
	std::exception_ptr pWorkerException = nullptr;
}

int main() {
	try { // The rest of the code is exception safe, but loading resources and creating threads can't be
		ResourceHandler resourceHandler;
		resourceHandler.load();
		global::resourceHandlerPtr = &resourceHandler;
		seedRNG();
		sf::Vector2f drawableRegionSize = getDrawableRegionSize();
		sf::ContextSettings settings;
		settings.antialiasingLevel = 6;
		sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Blind Jump", sf::Style::Fullscreen, settings);
		window.setMouseCursorVisible(false);
		window.setVerticalSyncEnabled(true);
		window.setFramerateLimit(120);
		InputController input;
		sf::View hudView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
		sf::View worldView(drawableRegionSize / 2.f, drawableRegionSize);
		FontController fonts(hudView, drawableRegionSize.x / 2, drawableRegionSize.y / 2);
		Game game(drawableRegionSize, &input, &fonts);
		#ifdef LINUX
		if (!XInitThreads()) {
			return EXIT_FAILURE;
		}
		#endif
		SmartThread logicThread([](Game * pGame, sf::RenderWindow * pWindow) {
			duration logicUpdateDelta;
			sf::Clock gameClock;
			try {
				while (pWindow->isOpen()) {
					time_point start = high_resolution_clock::now();
					sf::Time elapsedTime = gameClock.restart();
					// If the game went into extended sleep or froze for some reason, dt would be very high--reset clk
					if (util::isAsleep || elapsedTime.asMilliseconds() > 20) {
						elapsedTime = gameClock.restart();
						util::isAsleep = false;
					}
				    pGame->update(elapsedTime);
					time_point stop = high_resolution_clock::now();
					logicUpdateDelta = std::chrono::duration_cast<nanoseconds>(stop - start);
					static const microseconds logicUpdateLimit(2000);
					std::this_thread::sleep_for(logicUpdateLimit - logicUpdateDelta);
				}
			} catch (...) {
				global::pWorkerException = std::current_exception();
				return;
			}
		}, &game, &window);
		while (window.isOpen()) {
			input.update(window);
			window.clear();
			game.draw(window);
			window.display();
			if (global::pWorkerException) {
				window.close();
				std::rethrow_exception(global::pWorkerException);
			}
		}
	} catch (const std::exception & ex) {
		std::cerr << ex.what() << std::endl;
	}
	return EXIT_SUCCESS;
}


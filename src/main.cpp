//========================================================================//
// Copyright (C) 2016 Evan Bowman										  //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.			  //
//========================================================================//

// Start Date: 10/9/15
// End Date:

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include "framework/smartThread.hpp"
#include "backgroundHandler.hpp"
#include "inputController.hpp"
#include "resourceHandler.hpp"
#include "aspectScaling.hpp"
#include "ResourcePath.hpp"
#include "player.hpp"
#include "alias.hpp"
#include "game.hpp"
#include "util.hpp"
#include "rng.hpp"

namespace global {
	ResHandler * resHandlerPtr = nullptr;
	std::exception_ptr pWorkerException = nullptr;
}

int main() {
	rng::seed();
	ResHandler resourceHandler;
	sf::Vector2f drawableRegionSize = getDrawableRegionSize();
	try {
		resourceHandler.load();
		global::resHandlerPtr = &resourceHandler;
		sf::ContextSettings settings;
		settings.antialiasingLevel = 6;
		sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Blind Jump", sf::Style::Fullscreen, settings);
		window.setMouseCursorVisible(false);
		window.setVerticalSyncEnabled(true);
		window.setFramerateLimit(120);
		InputController input;
		sf::View hudView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
		sf::View worldView(drawableRegionSize / 2.f, drawableRegionSize);
		ui::Frontend uIFrontEnd(hudView, drawableRegionSize.x / 2, drawableRegionSize.y / 2);
		Game game(drawableRegionSize, &input, &uIFrontEnd);
		framework::SmartThread logicThread([& game, & window]() {
			duration logicUpdateDelta;
			sf::Clock gameClock;
			try {
				while (window.isOpen()) {
					time_point start = high_resolution_clock::now();
					sf::Time elapsedTime = gameClock.restart();
					// TODO: what if the game freezes? Elapsed time will be large...
					if (util::isAsleep) {
						elapsedTime = gameClock.restart();
						util::isAsleep = false;
					}
					game.update(elapsedTime);
					time_point stop = high_resolution_clock::now();
					logicUpdateDelta = std::chrono::duration_cast<nanoseconds>(stop - start);
					static const microseconds logicUpdateLimit(2000);
					std::this_thread::sleep_for(logicUpdateLimit - logicUpdateDelta);
				}
			} catch (...) {
				global::pWorkerException = std::current_exception();
				return;
			}
		});
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


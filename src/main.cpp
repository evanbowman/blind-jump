//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

// Start Date: 10/9/15
// End Date:

#include "alias.hpp"
#include "aspectScaling.hpp"
#include "backgroundHandler.hpp"
#include "config.h"
#include "framework/smartThread.hpp"
#include "game.hpp"
#include "inputController.hpp"
#include "introSequence.hpp"
#include "player.hpp"
#include "resourceHandler.hpp"
#include "rng.hpp"
#include "util.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <exception>
#include <iostream>
#include <stdexcept>

std::exception_ptr pWorkerException = nullptr;

int main() {
    rng::seed();
    ResHandler resourceHandler;
    sf::Vector2f drawableRegionSize = getDrawableRegionSize();
    try {
        resourceHandler.load();
        setgResHandlerPtr(&resourceHandler);
        sf::ContextSettings settings;
        settings.antialiasingLevel = 6;
        sf::RenderWindow window(sf::VideoMode::getDesktopMode(),
                                EXECUTABLE_NAME, sf::Style::Fullscreen,
                                settings);
        window.setMouseCursorVisible(false);
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(120);
        InputController input;
        dispIntroSequence(window, input);
        sf::View hudView(
            sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
        ui::Frontend uIFrontEnd(hudView, drawableRegionSize.x / 2,
                                drawableRegionSize.y / 2);
        Game game(drawableRegionSize, &input, &uIFrontEnd, &window);
        framework::SmartThread logicThread([&game, &window]() {
            duration logicUpdateDelta;
            sf::Clock gameClock;
            try {
                while (window.isOpen()) {
                    time_point start = high_resolution_clock::now();
                    sf::Time elapsedTime = gameClock.restart();
                    // TODO: what if the game freezes? Elapsed time will be
                    // large...
                    if (util::isAsleep) {
                        elapsedTime = gameClock.restart();
                        util::isAsleep = false;
                    }
                    game.update(elapsedTime);
                    time_point stop = high_resolution_clock::now();
                    logicUpdateDelta =
                        std::chrono::duration_cast<nanoseconds>(stop - start);
                    static const microseconds logicUpdateLimit(2000);
                    std::this_thread::sleep_for(logicUpdateLimit -
                                                logicUpdateDelta);
                }
            } catch (...) {
                ::pWorkerException = std::current_exception();
                return;
            }
        });
        game.getCamera().panDown();
        while (window.isOpen()) {
            input.update(window);
            window.clear();
            game.draw(window);
            window.display();
            if (::pWorkerException) {
                window.close();
                std::rethrow_exception(::pWorkerException);
            }
        }
    } catch (const std::exception & ex) {
        std::cerr << ex.what() << std::endl;
    }
    return EXIT_SUCCESS;
}

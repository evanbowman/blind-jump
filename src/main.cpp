// Start Date: 10/9/15

#include "alias.hpp"
#include "aspectScaling.hpp"
#include "backgroundHandler.hpp"
#include "config.h"
#include "framework/smartThread.hpp"
#include "Game.hpp"
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
#include <json.hpp>
#include <fstream>

std::exception_ptr pWorkerException = nullptr;
bool gameHasFocus = false;

int main() {
    rng::seed();
    ResHandler resourceHandler;
    try {
	nlohmann::json configJSON;
	{
	    std::fstream configRaw(resourcePath() + "config.json");
	    configRaw >> configJSON;
	}
        resourceHandler.load();
        setgResHandlerPtr(&resourceHandler);
        Game game({getDrawableArea(configJSON)});
        game.init();
	configJSON.clear();
        dispIntroSequence(game.getWindow(), game.getInputController());
        framework::SmartThread logicThread([&game]() {
            duration logicUpdateDelta;
            sf::Clock gameClock;
            try {
                while (game.getWindow().isOpen()) {
                    time_point start = high_resolution_clock::now();
                    sf::Time elapsedTime = gameClock.restart();
                    // TODO: what if the game freezes? Elapsed time will be
                    // large...
                    if (util::isAsleep) {
                        elapsedTime = gameClock.restart();
                        util::isAsleep = false;
                    }
                    game.updateLogic(elapsedTime);
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
        while (game.getWindow().isOpen()) {
            game.eventLoop();
            game.updateGraphics();
            if (::pWorkerException) {
                game.getWindow().close();
                std::rethrow_exception(::pWorkerException);
            }
        }
    } catch (const std::exception & ex) {
        std::cerr << ex.what() << std::endl;
    }
    return EXIT_SUCCESS;
}

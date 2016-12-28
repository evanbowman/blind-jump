// Start Date: 10/9/15
// End Date:

#include "alias.hpp"
#include "backgroundHandler.hpp"
#include "calc.hpp"
#include "config.h"
#include "framework/smartThread.hpp"
#include "game.hpp"
#include "inputController.hpp"
#include "json.hpp"
#include "resourceHandler.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>

std::exception_ptr pWorkerException = nullptr;

int main() {
    calc::rng::seed();
    try {
        LuaProvider luaProv;
        luaProv.runScriptFromFile(resourcePath() + "scripts/conf.lua");
        Game game(luaProv.applyHook(getConfig));
        json resourcesJSON;
        {
            std::fstream resourcesJSONRaw(resourcePath() + "resources.json");
            resourcesJSONRaw >> resourcesJSON;
            try {
                game.getResHandler().loadFromJSON(resourcesJSON);
            } catch (const std::exception & ex) {
                std::string err("Error: failed to parse resources file; ");
                std::cout << err + ex.what() << std::endl;
                return EXIT_FAILURE;
            }
        }
        game.init();
        // A global pointer to an instance of the Game class is required for the
        // engine's Lua API for scripting logic
        setgGamePtr(&game);
        json::iterator entryPt = resourcesJSON.find("main");
        if (entryPt == resourcesJSON.end()) {
            throw std::runtime_error(
                "Error: \"main\" field missing from manifest.json");
        }
        luaProv.runScriptFromFile(resourcePath() + entryPt->get<std::string>());
        framework::SmartThread logicThread([&game, &luaProv]() {
            duration logicUpdateDelta;
            sf::Clock gameClock;
            try {
                while (game.getWindow().isOpen()) {
                    time_point start = high_resolution_clock::now();
                    game.setElapsedTime(gameClock.restart());
                    if (game.hasSlept()) {
                        // IMPORTANT:
                        // This is necessary, otherwise calls to
                        // Game::setSleep would screw with delta
                        // timing for game logic.
                        game.setElapsedTime(gameClock.restart());
                        game.clearSleptFlag();
                    }
                    game.updateLogic(luaProv);
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

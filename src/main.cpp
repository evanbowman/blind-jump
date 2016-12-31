// Start Date: 10/9/15
// End Date:

#include "Engine.hpp"
#include "alias.hpp"
#include "calc.hpp"
#include "config.h"
#include "framework/smartThread.hpp"
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

std::exception_ptr pExceptionSignal = nullptr;

microseconds logicUpdateThrottle(0);

int main() {
    calc::rng::seed();
    try {
        LuaProvider luaProv;
        luaProv.runScriptFromFile(resourcePath() + "scripts/conf.lua");
        Engine engine(luaProv.applyHook(getConfig));
        {
            json resourcesJSON;
            std::fstream resourcesJSONRaw(resourcePath() + "resources.json");
            resourcesJSONRaw >> resourcesJSON;
            try {
                engine.getResHandler().loadFromJSON(resourcesJSON);
            } catch (const std::exception & ex) {
                std::string err("Error: failed to parse resources file; ");
                std::cout << err + ex.what() << std::endl;
                return EXIT_FAILURE;
            }
            engine.init();
            setgEnginePtr(&engine);
            json::iterator entryPt = resourcesJSON.find("main");
            if (entryPt == resourcesJSON.end()) {
                throw std::runtime_error(
                    "Error: \"main\" field missing from manifest.json");
            }
            luaProv.runScriptFromFile(resourcePath() +
                                      entryPt->get<std::string>());
        }
        SmartThread logicThread([&engine, &luaProv]() {
            duration logicUpdateDelta;
            sf::Clock logicClock;
            try {
                while (engine.getWindow().isOpen()) {
                    time_point start = high_resolution_clock::now();
                    engine.setElapsedTime(logicClock.restart());
                    if (engine.hasSlept()) {
                        // IMPORTANT:
                        // This is necessary, otherwise calls to
                        // Engine::setSleep would screw with delta
                        // timing for game logic.
                        engine.setElapsedTime(logicClock.restart());
                        engine.clearSleptFlag();
                    }
                    engine.updateLogic(luaProv);
                    time_point stop = high_resolution_clock::now();
                    logicUpdateDelta =
                        std::chrono::duration_cast<nanoseconds>(stop - start);
                    std::this_thread::sleep_for(logicUpdateThrottle -
                                                logicUpdateDelta);
                }
            } catch (...) {
                ::pExceptionSignal = std::current_exception();
                return;
            }
        });
        try {
            while (engine.getWindow().isOpen()) {
                engine.eventLoop(luaProv);
                engine.updateGraphics();
                if (::pExceptionSignal) {
                    std::rethrow_exception(::pExceptionSignal);
                }
            }
        } catch (const std::exception & ex) {
            engine.getWindow().close();
            logicThread.get().join();
            std::cerr << ex.what() << std::endl;
        }
    } catch (const std::exception & ex) {
        std::cerr << ex.what() << std::endl;
    }
    return EXIT_SUCCESS;
}

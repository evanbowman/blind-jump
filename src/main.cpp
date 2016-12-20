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
bool gameHasFocus = false;

int main() {
    rng::seed();
    ResHandler resourceHandler;
    try {
        resourceHandler.load();
        setgResHandlerPtr(&resourceHandler);
        LuaProvider luaProv;
        luaProv.runScriptFromFile(resourcePath() + "scripts/conf.lua");
        Game game(luaProv.applyHook(getConfig));
        setgGamePtr(&game);
        luaProv.runScriptFromFile(resourcePath() + "scripts/enemies.lua");
        framework::SmartThread logicThread([&game, &luaProv]() {
            duration logicUpdateDelta;
            sf::Clock gameClock;
            try {
                while (game.getWindow().isOpen()) {
                    time_point start = high_resolution_clock::now();
                    game.setElapsedTime(gameClock.restart());
                    // TODO: what if the game freezes? Elapsed time will be
                    // large...
                    if (util::isAsleep) {
                        game.setElapsedTime(gameClock.restart());
                        util::isAsleep = false;
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

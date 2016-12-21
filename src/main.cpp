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
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

std::exception_ptr pWorkerException = nullptr;

static void parseManifest(json & manifest, ResHandler & resources);

int main() {
    rng::seed();
    try {
	ResHandler resources;
        resources.load();
        setgResHandlerPtr(&resources);
        LuaProvider luaProv;
        luaProv.runScriptFromFile(resourcePath() + "scripts/conf.lua");
	json manifest;
	{
	    std::fstream manifestRaw(resourcePath() + "manifest.json");
	    manifestRaw >> manifest;
	    parseManifest(manifest, resources);
	}
        Game game(luaProv.applyHook(getConfig));
        setgGamePtr(&game);
	json::iterator entryPt = manifest.find("main");
	if (entryPt == manifest.end()) {
	    throw std::runtime_error("Error: \"main\" field missing from manifest.json");
	}
	luaProv.runScriptFromFile(resourcePath() + entryPt->get<std::string>());
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

static void parseManifest(json & manifest, ResHandler & resources) {
    auto it = manifest.find("textures");
    if (it != manifest.end()) {
	for (const auto & entry : *it) {
	    resources.loadTexture(entry);
	}
    }
    it = manifest.find("sounds");
    if (it != manifest.end()) {
	for (const auto & entry : *it) {
	    resources.loadSound(entry);
	}
    }
    it = manifest.find("spriteSheets");
    if (it != manifest.end()) {
	for (auto sheet = it->begin(); sheet != it->end(); ++sheet) {
	    auto textureTag = sheet->find("texture");
	    auto boxObj = sheet->find("box");
	    auto x = boxObj->find("x")->get<int>();
	    auto y = boxObj->find("y")->get<int>();
	    auto w = boxObj->find("w")->get<int>();
	    auto h = boxObj->find("h")->get<int>();
	    auto & texture = resources.getTexture(*textureTag);
	    resources.addSheet(sheet.key(), SpriteSheet(texture,
							sf::IntRect(x, y, w, h)));
	}
    }
}

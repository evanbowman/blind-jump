//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "RenderType.hpp"
#include "critter.hpp"
#include "dasher.hpp"
#include "effectsController.hpp"
#include "resourceHandler.hpp"
#include "scoot.hpp"
#include "util.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <thread>

class ScreenShakeController;
class detailController;
class tileController;
class Game;
class Camera;

class enemyController {
private:
    using drawableVec =
        std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>;
    std::vector<std::shared_ptr<Scoot>> scoots;
    std::vector<std::shared_ptr<Dasher>> dashers;
    std::vector<std::shared_ptr<Critter>> critters;
    float windowW;
    float windowH;

public:
    enemyController();
    void update(Game *, bool, const sf::Time &, std::vector<sf::Vector2f> &);
    void draw(drawableVec &, drawableVec &, Camera &);
    void clear();
    void addTurret(tileController *);
    void addScoot(tileController *);
    void addDasher(tileController *);
    void addCritter(tileController *);
    void setWindowSize(float, float);
    std::vector<std::shared_ptr<Critter>> & getCritters();
    std::vector<std::shared_ptr<Scoot>> & getScoots();
    std::vector<std::shared_ptr<Dasher>> & getDashers();
};

//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <thread>
#include <SFML/Graphics.hpp>
#include "resourceHandler.hpp"
#include "turret.hpp"
#include "effectsController.hpp"
#include "scoot.hpp"
#include "dasher.hpp"
#include "critter.hpp"
#include "RenderType.hpp"
#include "util.hpp"

class ScreenShakeController;
class detailController;
class tileController;
class Game;
class Camera;

class enemyController {
private:
	using drawableVec = std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>;
	std::vector<Turret> turrets;
	std::vector<Scoot> scoots;
	std::vector<Dasher> dashers;
	std::vector<Critter> critters;
	float windowW;
	float windowH;
	
public:
	enemyController();
	void update(Game *, float, float, bool, sf::Time &, std::vector<sf::Vector2f> &);
	void draw(drawableVec &, drawableVec &, Camera &);
	void clear();
	void addTurret(tileController *);
	void addScoot(tileController *);
	void addDasher(tileController *);
	void addCritter(tileController *);
	void setWindowSize(float, float);
	std::vector<Critter> & getCritters();
	std::vector<Scoot> & getScoots();
	std::vector<Dasher> & getDashers();
	std::vector<Turret> & getTurrets();
};

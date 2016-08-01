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

#pragma once

#include "resourceHandler.hpp"
#include "SFML/Graphics.hpp"
#include "turret.hpp"
#include "effectsController.hpp"
#include "scoot.hpp"
#include "dasher.hpp"
#include "critter.hpp"
#include "RenderType.hpp"

class ScreenShakeController;
class detailController;
class tileController;

class enemyController {
private:
	using drawableVec = std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>;
	sf::Sprite turretSprites[10];
	sf::Texture turretTextures[10];
	
	std::vector<Turret> turrets;
	std::vector<Scoot> scoots;
	std::vector<Dasher> dashers;
	std::vector<Critter> critters;
	
	float windowW;
	float windowH;
	
public:
	enemyController();
	void update(drawableVec &, drawableVec &, float, float, EffectGroup &, std::vector<wall>, bool, tileController*, ScreenShakeController*, FontController&, sf::Time &);
	void clear();
	sf::Sprite * getTurretSprites();
	sf::Sprite * getChaserSprites();
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

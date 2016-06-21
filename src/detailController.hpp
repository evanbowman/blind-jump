//
//  detailController.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/29/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef detailController_hpp
#define detailController_hpp

#include "SFML/Graphics.hpp"
#include "Teleporter.hpp"
#include "treasureChest.hpp"
#include "tileController.hpp"
#include "coordinate.hpp"
#include "generalDetail.hpp"
#include "lampLight.hpp"
#include "userInterface.hpp"
#include "damagedRobot.hpp"
#include "rock.hpp"
#include "IntroDoor.hpp"
#include <array>
#include "RenderType.hpp"
#include "resourceHandler.hpp"

class GameMap;

class detailController {
private:
	using drawableVec = std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>;
	std::vector<Teleporter> teleporters;
	std::vector<TreasureChest> chests;
	std::vector<LampLight> lamps;
	std::vector<Rock> rocks;
	std::vector<IntroDoor> doors;
	std::vector<DamagedRobot> damagedRobots;
	std::vector<GeneralDetail> misc32x26;
	ResourceHandler * pRH;
	float windowW, windowH;
	
public:
	detailController(float, float, ResourceHandler *);
	void addCrystals(float, float, float, float);
	void addDoor(float, float, int, int, float, float);
	void addPod(float, float, int, int);
	void addDamagedRobots(tileController&, float, float);
	void addLamplight(float, float, int, int, float, float);
	void addChest(tileController&, float, float, float, float, char);
	void addEnemyScrap(float, float, float, float);
	void addDamagedTurret(float, float, float, float);
	void addTeleporter(tileController&, float, float, float, float);
	void addRock(float, float, int, int);
	void update(GameMap *, sf::Time &);
	void addDasherScrap(float, float, int);
	void draw(drawableVec &, drawableVec &, sf::RenderTexture &);
	void clear();
	std::vector<TreasureChest> & getChests();
	Teleporter * getTeleporter();
	std::vector<LampLight> * getLamps();
	std::vector<Rock> * getRocks();
	void addWarpImpact(float, float);
	void killTeleporter();
	void setWindowSize(float, float);
};

#endif /* detailController_hpp */

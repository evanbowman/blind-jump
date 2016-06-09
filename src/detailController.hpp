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

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include "Teleporter.hpp"
#include "treasureChest.hpp"
#include "tileController.hpp"
#include "coordinate.h"
#include "generalDetail.hpp"
#include "lampLight.hpp"
#include "userInterface.hpp"
#include "damagedRobot.hpp"
#include "rock.hpp"
#include "IntroDoor.hpp"
#include <array>
#include "RenderType.hpp"
#include "Texturemanager.hpp"

class detailController {
private:
	std::vector<Teleporter> teleporters;
	std::vector<TreasureChest> chests;
	std::vector<LampLight> lamps;
	std::vector<Rock> rocks;
	std::vector<IntroDoor> doors;
	std::vector<DamagedRobot> damagedRobots;
	std::vector<GeneralDetail> misc32x26;
	TextureManager * pTM;
	
public:
	detailController();
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
	void update(float, float, effectsController& ef, char, std::vector<sf::Sprite*>*, std::vector<sf::Sprite*>*, userInterface&, FontController&, Player&, InputController*, ScreenShakeController * pscr, sf::Time&);
	void addDasherScrap(float, float, int);
	void draw(std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>&, std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>&, sf::RenderTexture&);
	void clear();
	std::vector<TreasureChest> getChests();
	Teleporter* getTeleporter();
	std::vector<LampLight>* getLamps();
	std::vector<Rock>* getRocks();
	void addWarpImpact(float, float);
	void killTeleporter();
	void setWindowSize(float, float);
	void setTextureManager(TextureManager *);
};

#endif /* detailController_hpp */

//
//  enemyController.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/18/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef enemyController_hpp
#define enemyController_hpp

#include "textureManager.hpp"
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
	sf::Sprite turretSprites[10];
	sf::Texture turretTextures[10];
	// A vector to hold turret objects
	std::vector<turret> turrets;
	sf::Sprite droneSprites[5];
	sf::Texture droneTextures[5];
	sf::Sprite chaserSprites[4];
	sf::Texture chaserTextures[4];

	TextureManager * pTM;
	std::vector<Scoot> scoots;
	std::vector<Dasher> dashers;
	std::vector<Critter> critters;
	float windowW;
	float windowH;
	
public:
	enemyController();
	void updateEnemies(std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>&, std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>&, float, float, effectsController&, std::vector<wall>, bool, detailController*, tileController*, ScreenShakeController*, FontController&, sf::Time &);
	void clear();
	sf::Sprite * getTurretSprites();
	sf::Sprite * getGuardianSprites();
	sf::Sprite * getChaserSprites();
	void linkTextures(TextureManager *);
	void addTurret(turret);
	void addScoot(tileController *);
	void addDasher(tileController *);
	void addCritter(Critter);
	void setWindowSize(float, float);
};
#endif /* enemyController_hpp */

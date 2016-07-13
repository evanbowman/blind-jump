//  Created by Evan Bowman on 10/18/15.

#pragma once
#ifndef enemyController_hpp
#define enemyController_hpp

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
	
	std::vector<turret> turrets;
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
	void addTurret(turret);
	void addScoot(tileController *);
	void addDasher(tileController *);
	void addCritter(tileController *);
	void setWindowSize(float, float);
};
#endif /* enemyController_hpp */

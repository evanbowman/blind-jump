//
//  effectsController.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef effectsController_hpp
#define effectsController_hpp

#include "SFML/Graphics.hpp"
#include "turretFlashEffect.hpp"
#include "bulletType1.hpp"
#include "shotPuff.hpp"
#include "turretShot.hpp"
#include "teleporterSmoke.hpp"
#include "enemyShot.hpp"
#include "dasherShot.hpp"
#include "fontController.hpp"
#include "dashSmoke.hpp"
#include "FireExplosion.hpp"
#include "smallExplosion.hpp"
#include "Powerup.hpp"
#include "ResourceHandler.hpp"
#include "RenderType.hpp"
#include "Framework/framework.hpp"

class ScreenShakeController;

using EffectGroup = Framework::Group<turretFlashEffect,
										  SmallExplosion,
										  FireExplosion,
										  TeleporterSmoke,
										  turretShot,
										  DasherShot,
										  Enemyshot,
										  bulletType1,
										  shotPuff,
										  Powerup,
										  Powerup>;

class effectsController {
private:
	ResourceHandler * pRH;
	std::vector<turretFlashEffect> turretFlashes;
	std::vector<SmallExplosion> smallExplosions;
	std::vector<FireExplosion> fireExplosions;
	std::vector<TeleporterSmoke> warpEffects;
	std::vector<turretShot> turretShots;
	std::vector<DasherShot> dasherShots;
	std::vector<sf::Sprite*> glowSprs2;
	std::vector<Enemyshot> enemyShots;
	std::vector<sf::Sprite*> glowSprs;
	std::vector<bulletType1> bullets;
	std::vector<shotPuff> puffs;
	std::vector<Powerup> hearts;
	std::vector<Powerup> coins;
	
public:
	effectsController(ResourceHandler *);
	void draw(sf::RenderTexture&, std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>&);
	void update(float, float, ScreenShakeController *, sf::Time &);

	void addOrbShot(unsigned char, float, float, float, float);
	void addScootShot(float, float, short, float, float);
	void addBullet(bool, char, float, float);
	void addTurretShot(float, float, short);
	void addDasherShot(float, float, short);
	void addEnemyShot(float, float, short);
	void addSmallExplosion(float, float);
	void addFireExplosion(float, float);
	void drawLower(sf::RenderTexture &);
	void addTurretFlash(float, float);
	void addWarpEffect(float, float);
	void addExplosion(float, float);
	void addMissile(float, float);
	void addHearts(float, float);
	void addCoins(float, float);
	void addPuff(float, float);
	void clear();
	std::vector<bulletType1> & getBulletLayer1();
   	std::vector<Enemyshot> & getEnemyShots();
	std::vector<Powerup> & getHearts();
	std::vector<Powerup> & getCoins();
	std::vector<turretShot> & getTurretShots();
	std::vector<DasherShot> & getDasherShots();
	std::vector<sf::Sprite*>* getGlowSprs();
	std::vector<sf::Sprite*>* getGlowSprs2();
	std::vector<FireExplosion> & getExplosions();
	void condClearGlowSpr(sf::Sprite*);
};

#endif /* effectsController_hpp */

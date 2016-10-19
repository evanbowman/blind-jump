//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <tuple>
#include "playerAnimationFunctions.hpp"
#include "playerCollisionFunctions.hpp"
#include "detailController.hpp"
#include "soundController.hpp"
#include "inputController.hpp"
#include "resourceHandler.hpp"
#include "tileController.hpp"
#include "spriteSheet.hpp"
#include "RenderType.hpp"
#include "util.hpp"
#include "wall.hpp"

class Game;

class Player {
public:
	using drawableVec = std::vector<std::tuple<framework::Sprite, float, Rendertype, float>>;
	using Health = int8_t;
	using HBox = framework::HitBox<8, 16, 12, 12>;
	enum class Sheet {
		stillDown,
		stillUp,
		stillLeft,
		stillRight,
		walkDown,
		walkUp,
		walkLeft,
		walkRight,
		deathSheet,
		dashSheet,
	};
	enum class State {
		deactivated,
		nominal,
		dashing,
		cooldown,
		dead,
		prepdash
	};
	struct Weapon {
		SpriteSheet<688, 106, 11, 10> gunSpr;
		int64_t timeout, bulletTimer;
	};
	Player(float, float);
	void activate();
	float getXpos() const; // The player's absolute position in the window
	float getYpos() const;
	void draw(drawableVec &, drawableVec &);
	void update(Game *, const sf::Time &, SoundController &);
	void setState(State);
	State getState() const;
	void setPosition(float, float);
	sf::Vector2f getPosition();
	sf::Vector2f getCameraTarget(const sf::View &);
	Health getHealth() const;
	bool visible = true;	
	void reset();
	void updateColor(const sf::Time &);
	void setHealth(Health);
	const HBox & getHitBox() const;
	const Weapon & getGun() const;
	const float getXVelocity() const;
	const float getYVeclocty() const;
	sf::Vector2f requestFuturePos(const uint32_t) const;
	
private:
	void init();
	HBox hitBox;
	void updateGun(const sf::Time &, const bool, EffectGroup &, SoundController &, ui::Backend &);
	Weapon gun;
	void checkEffectCollisions(EffectGroup &, ui::Frontend *);
	void checkEnemyCollisions(enemyController &, ui::Frontend *);
	std::vector<Dasher::Blur> blurs; // TODO: Move blur subclass out of Dasher, and into its own file...
	Health health;
	void updateAnimation(const sf::Time &, uint8_t, uint32_t);
	float xPos, yPos;
	uint8_t frameIndex;
	Sheet sheetIndex, cachedSheet;
	float lSpeed, rSpeed, uSpeed, dSpeed;
	framework::Sprite shadowSprite;
	SpriteSheet<400, 108, 32, 32> walkDown;
	SpriteSheet<208, 108, 32, 32> walkUp;
	SpriteSheet<208, 76, 32, 32> walkLeft;
	SpriteSheet<432, 76, 32, 32> walkRight;
	SpriteSheet<208, 38, 40, 38> deathSheet;
	SpriteSheet<208, 140, 32, 33> dashSheet;
	int64_t animationTimer, dashTimer;
	bool invulnerable;
	State state;
	float colorAmount;
	int32_t colorTimer;
	Rendertype renderType;
	bool upPrevious;
	bool downPrevious;
	bool leftPrevious;
	bool rightPrevious;
	bool actionPrevious;
	uint8_t dir = 0;
};

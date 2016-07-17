//
//  player.hpp
//  BlindJump
//
//  Created by Evan Bowman on 10/9/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef player_hpp
#define player_hpp

#include <SFML/Graphics.hpp>
#include "tileController.hpp"
#include "detailController.hpp"
#include "soundController.hpp"
#include "inputController.hpp"
#include "RenderType.hpp"
#include "resourceHandler.hpp"
#include "spriteSheet.hpp"

class Scene;

class Player {
public:
	using drawableVec = std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>;
	using Health = int8_t;
	using HBox = Framework::HitBox<8, 16, 12, 12>;
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
		int32_t timeout, bulletTimer;
	};
	Player(float, float);
	float getWorldOffsetX() const; // The distance the player has moved
	float getWorldOffsetY() const;
	void setWorldOffsetX(float);
	void setWorldOffsetY(float);
	float getXpos() const; // The player's absolute position in the window
	float getYpos() const;
	void draw(drawableVec &, drawableVec &, const sf::Time &);
	void update(Scene *, const sf::Time &);
	void setState(State);
	State getState() const;
	void setPosition(float, float);
	bool scrShakeState;
	Health getHealth() const;
	bool visible = true;	
	void reset();
	void updateColor(const sf::Time &);
	void setHealth(Health);
	const HBox & getHitBox() const;

private:
	HBox hitBox;
	void updateGun(const sf::Time &, const bool, EffectGroup &, float, float);
	Weapon gun;
	void checkEffectCollisions(EffectGroup &, FontController *);
	std::vector<Dasher::Blur> blurs; // I could have designed this better...
	Health health;
	void updateAnimation(const sf::Time &, uint8_t, uint8_t);
	float xPos, yPos, worldOffsetX, worldOffsetY;
	uint8_t frameIndex;
	Sheet sheetIndex, cachedSheet;
	float lSpeed, rSpeed, uSpeed, dSpeed;
	sf::Sprite shadowSprite;
	SpriteSheet<400, 108, 32, 32> walkDown;
	SpriteSheet<208, 108, 32, 32> walkUp;
	SpriteSheet<208, 76, 32, 32> walkLeft;
	SpriteSheet<432, 76, 32, 32> walkRight;
	SpriteSheet<208, 38, 40, 38> deathSheet;
	SpriteSheet<208, 140, 32, 33> dashSheet;
	int32_t animationTimer, dashTimer, invulnerableCounter;
	bool invulnerable;
	State state;
	float colorAmount;
	int32_t colorTimer;
	Rendertype renderType;
	bool upPrevious;
	bool downPrevious;
	bool leftPrevious;
	bool rightPrevious;
	bool zPrevious;
};

#endif

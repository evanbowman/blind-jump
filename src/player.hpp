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
#include "gun.hpp"
#include "tileController.hpp"
#include "detailController.hpp"
#include "soundController.hpp"
#include "inputController.hpp"
#include "RenderType.hpp"
#include "resourceHandler.hpp"
#include "spriteSheet.hpp"

class GameMap;

class Player {
	using drawableVec = std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>;
	public:
	enum class Sheet {
		walkDown,
		walkUp,
		walkLeft,
		walkRight,
		deathSheet,
		dashSheet,
		stillDown,
		stillUp,
		stillLeft,
		stillRight
	};
	enum class State {
		deactivated,
		nominal,
		dashing,
		cooldown,
		dead,
		prepdash
	};
	Player(ResourceHandler *, float, float);
	float getWorldOffsetX() const;
	float getWorldOffsetY() const;
	void setWorldOffsetX(float);
	void setWorldOffsetY(float);
	float getXpos() const;
	float getYpos() const;
	
	void draw(drawableVec &, drawableVec &, const sf::Time &);
	void update(GameMap *, const sf::Time &);
	
	void setState(State);
	State getState() const;
	
	void setPosition(float, float);
	
	bool scrShakeState;
	char getHealth() const;
	char getSprIndex() const;
	
	bool visible = true;
	
	void reset();
	
	void fillHealth(char);

private:
	std::vector<Dasher::Blur> blurs; // I could have designed this better...
	uint8_t health;
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
    gun weapon;
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

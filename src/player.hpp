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

#include <SFML/Graphics.hpp>
#include "tileController.hpp"
#include "detailController.hpp"
#include "soundController.hpp"
#include "inputController.hpp"
#include "RenderType.hpp"
#include "resourceHandler.hpp"
#include "spriteSheet.hpp"
#include "feedback.hpp"

class Game;

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
	bool scrShakeState;
	Health getHealth() const;
	bool visible = true;	
	void reset();
	void updateColor(const sf::Time &);
	void setHealth(Health);
	const HBox & getHitBox() const;
	const Weapon & getGun() const;
	
private:
	HBox hitBox;
	void updateGun(const sf::Time &, const bool, EffectGroup &, SoundController &);
	Weapon gun;
	void checkEffectCollisions(EffectGroup &, FontController *);
	std::vector<Dasher::Blur> blurs; // I could have designed this better...
	Health health;
	void updateAnimation(const sf::Time &, uint8_t, uint32_t);
	float xPos, yPos;
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
	int64_t animationTimer, dashTimer, invulnerableCounter;
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

//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "turret.hpp"
#include "effectsController.hpp"
#include "resourceHandler.hpp"
#include "framework/framework.hpp"
#include "spriteSheet.hpp"

class Player;

class Turret {
private:
	enum class State {
		closed, opening, shoot1, shoot2, shoot3, rest, closing
    };
	State state;	
	using HBox = framework::HitBox<16, 32>;
	HBox hitBox;
	float xPos, yPos;
	int8_t frameIndex;
	SpriteSheet<0, 0, 16, 32> turretSheet;
	SpriteSheet<0, 32, 16, 26> shadowSheet;
	bool active;
	int64_t timer;
	float hp;
	bool killFlag;
	char colorTimer;
	bool isColored;
	float colorAmount;
	
public:
	Turret(const sf::Texture &, float, float);
	const HBox & getHitBox() const;
	void setPosition(float, float);
	const framework::Sprite & getShadow();
	const framework::Sprite & getSprite();
	sf::Vector2f target;
	void update(const sf::Time &, const Player *, EffectGroup &);
	bool getKillFlag();
	float getXpos();
	float getYpos();
	bool colored();
	float getColorAmount();
};

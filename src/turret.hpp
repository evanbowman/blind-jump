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
#include "Framework/framework.hpp"
#include "spriteSheet.hpp"

class Turret {
private:
	enum class State {
		closed, opening, shoot1, shoot2, shoot3, rest, closing
    };
	State state;	
	using HBox = Framework::HitBox<16, 32>;
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
	const sf::Sprite & getShadow();
	const sf::Sprite & getSprite();
	void update(const sf::Time &, float, float, EffectGroup &);
	bool getKillFlag();
	float getXpos();
	float getYpos();
	bool colored();
	float getColorAmount();
};

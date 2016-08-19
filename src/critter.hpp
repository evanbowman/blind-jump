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

#include "enemy.hpp"
#include "effectsController.hpp"
#include "aStar.hpp"
#include "spriteSheet.hpp"

class tileController;

class Critter : public Enemy {
public:
	using HBox = Framework::HitBox<12, 12, 4, -3>;
	Critter(const sf::Texture &, uint8_t map[61][61], float, float);
	void update(float, float, const std::vector<wall> &, EffectGroup & ef, const sf::Time &);
	void critterUpdate(float, float, EffectGroup & ef, const sf::Time &, tileController * pTiles);
	const sf::Sprite & getSprite() const;
	const sf::Sprite & getShadow() const;
	void activate();
	void deActivate();
	bool isActive();
	void updatePlayerDead();
	const HBox & getHitBox() const;
	
private:
	float xInit, yInit;
	void onDeath(EffectGroup &);
    float currentDir;
	float jumpTargetx, jumpTargety;
	void newPath(tileController *);
	mutable SpriteSheet<0, 57, 18, 18> spriteSheet;
	std::vector<aStrCoordinate> path;
	aStrCoordinate previous;
	sf::Sprite shadow;
	HBox hitBox;
	bool awake;
	bool active;
	int recalc;
	uint8_t (*map)[61]; //*** I know this is a nasty solution, perhaps there's a better way to not store it locally...
};

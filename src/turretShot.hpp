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

#include <cmath>
#include "spritesheet.hpp"
#include "Effect.hpp"
#include "rng.hpp"

class TurretShot : public Effect {
public:
	using HBox = Framework::HitBox<10, 10, -5, -5>;
	const HBox & getHitBox() const;
	TurretShot(const sf::Texture &, const sf::Texture &, float, float, float);
	sf::Sprite * getGlow();
	const sf::Sprite & getSprite();
	void update(float, float, sf::Time&);
	void speedFactor(float);
	int32_t animationTimer;
	
private:
	SpriteSheet<26, 75, 9, 16> spriteSheet;
	HBox hitBox;
	sf::Sprite glowSprite;
	float direction;
	float scale;	
};

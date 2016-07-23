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
#include <cmath>
#include "spriteSheet.hpp"
#include "Effect.hpp"

class Powerup : public Effect {
public:
	enum class Type { Heart, Coin };
	using HBox = Framework::HitBox<13, 13, -8, -8>;
	Powerup(const sf::Texture &, const sf::Texture &, float, float, Type);
	const sf::Sprite & getSprite();
	const HBox & getHitBox() const;
	sf::Sprite * getGlow();
	void update(float, float, sf::Time &);
	
protected:
	HBox hitBox;
	Sprite glow;
	SpriteSheet<0, 75, 13, 13> powerupSheet;
};

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
#include "spriteSheet.hpp"
#include "Effect.hpp"

class PlayerShot : public Effect {
public:
	using HBox = Framework::HitBox<12, 12, 2, 2>;
	PlayerShot(const sf::Texture &, const sf::Texture &, char, float, float);
	const sf::Sprite & getSprite();
	const sf::Sprite & getGlow();
	void update(const sf::Time &);
	char getDirection();
	bool checkCanPoof();
	void poof();
	void disablePuff();
	const HBox & getHitBox() const;

private:
	float xInit, yInit;
	HBox hitBox;
	SpriteSheet<44, 75, 16, 16> spriteSheet; // This could easily be a plain sprite, but the memory usage would be the same
	SpriteSheet<88, 145, 16, 16> puffSheet;
	sf::Sprite glow;
	char direction;
	bool canPoof;
	enum class State { travelling, poof };
	State state;
};

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

#include "SFML/Graphics.hpp"
#include <cmath>
#include "spriteSheet.hpp"
#include "Effect.hpp"
#include "rng.hpp"

class DasherShot : public Effect {
public:
	using HBox = Framework::HitBox<12, 12, -6, -6>;
	DasherShot(const sf::Texture &, const sf::Texture &, float, float, float);
	SpriteSheet<0, 88, 12, 12> spriteSheet;
	const sf::Sprite & getSprite();
	void update(float, float, sf::Time &);
	float direction;
	void speedFactor(float);
	bool driftSel;
	const sf::Sprite & getGlow() const;
	const HBox & getHitBox() const;
	
private:
	int32_t timeout;
	float scale;
	HBox hitBox;
	sf::Sprite glowSprite;
};

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

#include "detailParent.hpp"
#include "inputController.hpp"
#include "spriteSheet.hpp"
#include "rng.hpp"

class TreasureChest : public Detail {
public:
	enum class State {
		closed, opening, ready, complete
	};
	TreasureChest(float, float, const sf::Texture &, char);
	const sf::Sprite & getShadow() const;
	const sf::Sprite & getSprite() const;
	void update(float, float, const sf::Time &);
	State getState() const;
	void setState(const State);
	char getItem() const;
	
private:
	State state;
	char item;
	int32_t animationTimer;
	uint8_t frameIndex;
	mutable SpriteSheet<656, 76, 16, 30> chestSheet;
	mutable sf::Sprite chestShadow;
};

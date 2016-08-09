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

#include "wall.hpp"
#include "effectsController.hpp"
#include "enemy.hpp"
#include "resourceHandler.hpp"
#include "RenderType.hpp"

class Scoot : public Enemy {
public:
	using HBox = Framework::HitBox<12, 12, -6, -6>;
	Scoot(const sf::Texture &, const sf::Texture &, float, float);
	void update(float, float, const std::vector<wall> &, EffectGroup & ef, const sf::Time &);
	const sf::Sprite & getSprite() const override;
	const sf::Sprite & getShadow() const override;
	const HBox & getHitBox() const;
	
private:
	enum class State {
		drift1, drift2, shoot, recoil
	};
	mutable SpriteSheet<88, 161, 12, 12> spriteSheet;
	sf::Sprite shadow;
	float speedScale, hSpeed, vSpeed;
	State state;
	int32_t timer;
	void changeDir(float);
	void onDeath(EffectGroup &) override;
	HBox hitBox;
};

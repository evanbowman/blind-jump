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

#include "effectsController.hpp"
#include "enemy.hpp"
#include "resourceHandler.hpp"

class Dasher : public Enemy {
public:
	using HBox = Framework::HitBox<20, 32, -6, -4>;
	struct Blur {
		Blur(sf::Sprite *, float, float);
		sf::Sprite * getSprite();
		void update(const sf::Time &, float, float);
		bool getKillFlag();
		int32_t timer;
		float xInit;
		float yInit;
		sf::Sprite spr;
		bool killflag;
	};
	enum class State {
		idle, shooting, dashBegin, dashing, dashEnd, dying, dead, shootBegin, pause
	};
	Dasher(const sf::Texture &, float, float, float, float);
	const sf::Sprite & getSprite() const override;
	const sf::Sprite & getShadow() const override;
    void update(float, float, const std::vector<wall> &, EffectGroup & ef, const sf::Time &) override;
	std::vector<Dasher::Blur> * getBlurEffects();
	State getState() const;
	const sf::Vector2f & getScale() const;
	const HBox & getHitBox() const;
	
private:
	HBox hitBox;
	uint8_t shotCount;
	State state;
	mutable SpriteSheet<648, 38, 29, 38> dasherSheet;
	mutable SpriteSheet<80, 0, 47, 38> deathSheet;
	sf::Sprite shadow;
	float hSpeed, vSpeed;
	int32_t timer;
	std::vector<Dasher::Blur> blurEffects;
	void onDeath(EffectGroup &) override;
	void facePlayer();
};

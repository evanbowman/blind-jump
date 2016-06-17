//
//  scoot.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/21/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef scoot_hpp
#define scoot_hpp

#include "wall.hpp"
#include "effectsController.hpp"
#include "enemy.hpp"

class Scoot : public Enemy {
private:
	enum class State {
		drift1, drift2, shoot, recoil
	};
	mutable SpriteSheet<12, 12> spriteSheet;
	sf::Sprite shadow;
	float speedScale, hSpeed, vSpeed;
	State state;
	int32_t timer;
	void changeDir(float);
	void onDeath(effectsController &) override;

public:
	Scoot(const sf::Texture &, const sf::Texture &, float, float, float, float);
	void update(float, float, const std::vector<wall> &, effectsController & ef, const sf::Time &) override;
	const sf::Sprite & getSprite() const override;
	const sf::Sprite & getShadow() const override;
};

#endif /* scoot_hpp */

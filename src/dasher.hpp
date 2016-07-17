//
//  dasher.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/11/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef dasher_hpp
#define dasher_hpp

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

#endif /* dasher_hpp */

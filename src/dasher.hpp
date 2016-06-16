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

struct DasherBlur {
	DasherBlur(sf::Sprite *, float, float);
	sf::Sprite * getSprite();
	bool getKillFlag();
	float xInit;
	float yInit;
	sf::Sprite spr;
	bool killflag;
};

class Dasher : public Enemy {
public:
	Dasher(sf::Texture *, sf::Texture *, sf::Texture *, float, float, float, float);
	const sf::Sprite & getSprite() const override;
	const sf::Sprite & getShadow() const override;
    void update(float, float, const std::vector<wall> &, effectsController & ef, const sf::Time &) override;
	std::vector<DasherBlur> * getBlurEffects();
	enum class State {
		idle, shooting, dashBegin, dashing, dashEnd, dying, dead, shootBegin, pause
	};
	State getState() const;
	
private:
	State state;
	mutable SpriteSheet<29, 38> dasherSheet;
	mutable SpriteSheet<47, 38> deathSheet;
	sf::Sprite shadow;
	float hSpeed, vSpeed;
	int32_t timer;
	std::vector<DasherBlur> blurEffects;
	void onDeath(effectsController &) override;
	void facePlayer();
};

#endif /* dasher_hpp */

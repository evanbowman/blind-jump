
//  Pillar.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/15/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef IntroDoor_hpp
#define IntroDoor_hpp

#include "detailParent.hpp"
#include "effectsController.hpp"
#include "spriteSheet.hpp"

class ScreenShakeController;

class IntroDoor : public Detail {
private:
	enum class State { dormant, opening, opened };
	mutable SpriteSheet<200, 95> doorSheet;
	uint8_t frameIndex;
	int32_t timer;
	State state;
	
public:
	void _update(float, float, ScreenShakeController * pscr, effectsController & ef, const sf::Time & elapsedTime);
	void update(float, float, const sf::Time &) override;
	IntroDoor(float, float, const sf::Texture &);
	const sf::Sprite & getSprite() const override;
};

#endif

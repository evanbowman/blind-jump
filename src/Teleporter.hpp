//
//  mapTower.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 11/7/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef Teleporter_hpp
#define Teleporter_hpp

#include "detailParent.hpp"
#include "effectsController.hpp"

class Teleporter : public Detail {
public:
	Teleporter(float, float, sf::Sprite *, sf::Sprite *);
	const sf::Sprite & getShadow() const;
	const sf::Sprite & getSprite() const override;
	bool smokeReady();
	void update(float, float, const sf::Time &) override;
	sf::Sprite * getGlow();
	float getXpos();
	
private:
	mutable sf::Sprite glowSprite;
	int32_t smokeTimer;
	mutable sf::Sprite TeleporterSprites[2];
	float xPos;
};

#endif /* mapTower_hpp */

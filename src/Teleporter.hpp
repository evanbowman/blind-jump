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
	Teleporter(float, float, const sf::Texture &, const sf::Texture &);
	const sf::Sprite & getShadow() const;
	const sf::Sprite & getSprite() const;
	bool smokeReady();
	void update(float, float, const sf::Time &);
	sf::Sprite * getGlow();
	
private:
	mutable sf::Sprite glowSprite;
	mutable sf::Sprite TeleporterSprites[2];
	int32_t smokeTimer;
};

#endif /* mapTower_hpp */

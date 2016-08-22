//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "detailParent.hpp"
#include "effectsController.hpp"

class Teleporter : public Detail {
public:
	Teleporter(float, float, const sf::Texture &, const sf::Texture &);
	const sf::Sprite & getShadow() const;
	const sf::Sprite & getSprite() const;
	bool smokeReady();
	void update(const sf::Time &);
	const sf::Sprite & getGlow() const;
	
private:
	mutable sf::Sprite glowSprite;
	mutable sf::Sprite TeleporterSprites[2];
	int32_t smokeTimer;
};

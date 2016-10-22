//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "detailParent.hpp"
#include <SFML/Graphics.hpp>
#include "spriteSheet.hpp"
#include "rng.hpp"

class Rock : public Detail {
private:
	mutable SpriteSheet<80, 38, 32, 64> rockSheet;
	
public:
	void update(const sf::Time &);
	Rock(float, float, const sf::Texture &);
	const framework::Sprite & getSprite() const;
};

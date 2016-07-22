//
//  rock.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/5/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef rock_hpp
#define rock_hpp

#include "detailParent.hpp"
#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"
#include "rng.hpp"

class Rock : public Detail {
private:
	mutable SpriteSheet<80, 38, 32, 64> rockSheet;
	
public:
	void update(float, float, const sf::Time &);
	Rock(float, float, const sf::Texture &);
	const sf::Sprite & getSprite() const;
};

#endif /* rock_hpp */

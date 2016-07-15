//
//  lampLight.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/16/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef lampLight_hpp
#define lampLight_hpp

#include "detailParent.hpp"

class LampLight : public Detail {
public:
	LampLight(float, float, const sf::Texture &, const sf::Texture &);
	const sf::Sprite & getSprite() const;
	sf::Sprite * getGlow();
	void update(float, float, const sf::Time &);
	
private:
	sf::Sprite lampSprite;
	sf::Sprite glowSprite;
};

#endif /* lampLight_hpp */

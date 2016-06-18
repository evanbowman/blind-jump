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
	LampLight(float, float, sf::Sprite &, sf::Sprite &);
	const sf::Sprite & getSprite() const override;
	sf::Sprite * getGlow();
	void update(float, float, const sf::Time &) override;
	bool getKillFlag();
	void setKillFlag(bool);
	float getXpos();
	
private:
	sf::Sprite lampSprite;
	sf::Sprite glowSprite;
	bool killflag;
	float xPos;
	
};

#endif /* lampLight_hpp */

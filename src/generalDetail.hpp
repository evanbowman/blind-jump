//
//  generalDetail.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/11/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef generalDetail_hpp
#define generalDetail_hpp

#include "detailParent.hpp"

class GeneralDetail : public Detail {
public:
	GeneralDetail(float, float, sf::Sprite &);
	const sf::Sprite & getSprite() const;
	void update(float, float, const sf::Time & elapsedTime);
	
private:
	sf::Sprite spr;
};

#endif /* generalDetail_hpp */

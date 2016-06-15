//
//  teleporterSmoke.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/1/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef teleporterSmoke_hpp
#define teleporterSmoke_hpp

#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"
#include "Effect.hpp"

class TeleporterSmoke : public Effect {
private:
	mutable SpriteSheet<16, 16> spriteSheet;
   	char drawOrder;
	
public:
   	TeleporterSmoke(sf::Texture *, float, float);
	void update(float, float, const sf::Time &) override;
	const sf::Sprite & getSprite() const override;
	char getDrawOrder();
	void updateAnim(const sf::Time &);
};
#endif /* teleporterSmoke_hpp */

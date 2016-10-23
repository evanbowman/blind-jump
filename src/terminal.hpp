#pragma once

#include "detailParent.hpp"
#include "spriteSheet.hpp"
#include "rng.hpp"

class Terminal : public Detail {
public:
	Terminal(const float, const float, const sf::Texture &, const sf::Texture &);
	const sf::Sprite & getSprite() const;
	const sf::Sprite & getShadow() const;
	const sf::Sprite & getScreen() const;
	const sf::Sprite & getGlow() const;
	void update(const sf::Time &);
	
private:
	int64_t animationTimer;
	uint8_t frameIndex;
	mutable SpriteSheet<21, 132, 19, 11> screenSheet;
	sf::Sprite mainSprite;
	sf::Sprite shadow;
	sf::Sprite glow;
};

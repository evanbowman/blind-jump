#pragma once

#include "detailParent.hpp"
#include "spriteSheet.hpp"
#include "math.hpp"
#include "rng.hpp"

class Terminal : public Detail {
public:
	enum class State {
		dormant, wakeup, awake, poweroff
	};
	Terminal(const float, const float, const sf::Texture &);
	const sf::Sprite & getSprite() const;
	const sf::Sprite & getShadow() const;
	const sf::Sprite & getScreen() const;
	const sf::Sprite & getGlow() const;
	void update(const sf::Time &);
	void setState(const State);
	const State getState() const;
	
private:
	int64_t animationTimer;
	int64_t stateTimer;
	uint8_t frameIndex;
	State state;
	mutable SpriteSheet<21, 132, 19, 11> screenSheet;
	sf::Sprite mainSprite;
	sf::Sprite shadow;
};

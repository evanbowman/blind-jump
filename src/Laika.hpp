#pragma once

#include "Drawable.hpp"
#include "framework/framework.hpp"
#include "spriteSheet.hpp"

template <typename DrawPolicy>
class _Laika : public Drawable<_Laika<DrawPolicy>, DrawPolicy>,
	       public framework::Object,
	       public std::enable_shared_from_this<_Laika<DrawPolicy>> {
public:
    enum class State {
	idle, running
    };
    using HBox = framework::HitBox<32, 32, 0, 0>;
    _Laika(const float _xInit, const float _yInit, const sf::Texture & texture)
	: Object(_xInit, _yInit), state(State::idle), idleSheet(texture) {
	// ... TODO ...
    }
    static const int drawOffset = 0;
    const sf::Sprite & getSprite() const {
	switch (state) {
	case State::idle:
	    return idleSheet[frameIndex];

	case State::running:
	    return idleSheet[frameIndex];
	}
    }
    const sf::Sprite & getShadow() const { return shadow; }
    template <typename Game>
    void update(const sf::Time & elapsedTime, Game * pGame) {
	// ... TODO ...
    }
    
private:
    State state;
    HBox hitBox;
    mutable SpriteSheet<423, 224, 32, 32> idleSheet;
    sf::Sprite shadow;
    uint8_t frameIndex;
    int64_t animationTimer;
};


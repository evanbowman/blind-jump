#pragma once

#include "Drawable.hpp"
#include "spriteSheet.hpp"

template <typename DrawPolicy>
class _DasherCorpse : public Drawable<_DasherCorpse<DrawPolicy>, DrawPolicy>,
		      public Object {
    mutable SpriteSheet<80, 0, 47,38> deathSheet;
    int frameIndex;
    int32_t animationTimer;
    enum class State {
	falling,
	fallen
    };
    State state;
public:
    static const size_t drawOffset = 0;
    _DasherCorpse(const sf::Vector2f & _position,
		  const sf::Texture & texture, float scale)
	: Object(_position.x + 4 , _position.y),
	  frameIndex(0), animationTimer(0),
	  state(State::falling) {
	deathSheet.setTexture(texture);
	deathSheet.setOrigin(14, 8);
	deathSheet.setScale(scale, 1.f);
	deathSheet.setPosition(position);
    }
    const sf::Sprite & getSprite() const { return deathSheet[frameIndex]; }
    template <typename Game>
    void update(const sf::Time & elapsedTime, Game *) {
	switch (state) {
	case State::falling:
	    animationTimer += elapsedTime.asMicroseconds();
	    if (animationTimer > 53000) {
		animationTimer -= 53000;
		++frameIndex;
		if (frameIndex > 14) {
		    frameIndex = 14;
		    state = State::fallen;
		}
	    }
	    break;

	case State::fallen:
	    break;
	}
    }
};

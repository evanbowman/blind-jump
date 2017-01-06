#pragma once

#include "Drawable.hpp"

template <typename DrawPolicy>
class _StaticDrawable
    : public Drawable<_StaticDrawable<DrawPolicy>, DrawPolicy>,
      public framework::Object {
public:
    static const int drawOffset = 0;
    _StaticDrawable(float xInit, float yInit, sf::Sprite & _spr)
        : Object(xInit, yInit) {
        spr = _spr;
        spr.setPosition(position);
    }
    const sf::Sprite & getSprite() const { return spr; }
    template <typename Game>
    void update(const sf::Time & elapsedTime, Game *) {}

private:
    sf::Sprite spr;
};

#pragma once

#include "Drawable.hpp"

namespace detail {
template <typename DrawPolicy>
class StaticDrawable : public Drawable<StaticDrawable<DrawPolicy>, DrawPolicy>,
                       public framework::Object {
public:
    static const int drawOffset = 0;
    StaticDrawable(float xInit, float yInit, sf::Sprite & _spr)
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
}

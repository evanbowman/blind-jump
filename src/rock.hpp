#pragma once

#include "Drawable.hpp"
#include "GfxContext.hpp"
#include "rng.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>

template <typename DrawPolicy>
class _Rock : public Drawable<_Rock<DrawPolicy>, DrawPolicy>,
             public framework::Object {
public:
    static const int drawOffset = 24;
    _Rock(float _xPos, float _yPos, const sf::Texture & inpTxtr)
        : Object(_xPos, _yPos) {
        rockSheet.setTexture(inpTxtr);
        if (rng::random<2>()) {
            rockSheet.setScale(-1, 1);
            position.x += 32;
        }
        rockSheet[rng::random<4>()];
        rockSheet.setPosition(position.x, position.y);
    }
    template <typename Game> void update(const sf::Time &, Game *) {}
    const sf::Sprite & getSprite() const { return rockSheet.getSprite(); }

private:
    mutable SpriteSheet<80, 38, 32, 64> rockSheet;
};

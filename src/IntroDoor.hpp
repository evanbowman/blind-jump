#pragma once

#include "Drawable.hpp"
#include "effectsController.hpp"
#include "spriteSheet.hpp"

namespace detail {
template <typename DrawPolicy>
class IntroDoor : public Drawable<IntroDoor<DrawPolicy>, DrawPolicy>,
                  public framework::Object {
public:
    static const int drawOffset = 60;
    template <typename Game> void update(const sf::Time &, Game *) {}
    IntroDoor(float _xInit, float _yInit, const sf::Texture & inpTxtr)
        : Object{_xInit, _yInit}, doorSheet{inpTxtr}, frameIndex{3} {
        doorSheet.setPosition(position.x, position.y);
    }
    const sf::Sprite & getSprite() const { return doorSheet[frameIndex]; }

private:
    enum class State { dormant, opening, opened };
    mutable SpriteSheet<0, 0, 200, 95> doorSheet;
    uint8_t frameIndex;
};
}

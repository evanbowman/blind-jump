//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Drawable.hpp"
#include "Effect.hpp"
#include "GfxContext.hpp"
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

namespace effect {
template <typename DrawPolicy>
class Item : public Drawable<Item<DrawPolicy>, DrawPolicy>, public Effect {
    constexpr static float PI{3.1415926535};

public:
    static const int drawOffset = -16;
    enum class Type { Heart, Coin };
    using HBox = framework::HitBox<13, 13, -8, -8>;
    Item(const sf::Texture & bodyTxtr, const sf::Texture & glowTxtr,
         float xInit, float yInit, Type id)
        : Effect(xInit, yInit) {
        glow.setTexture(glowTxtr);
        glow.setOrigin(22.5, 22.5);
        glow.setPosition(position.x, position.y + 10);
        powerupSheet.setTexture(bodyTxtr);
        // Square brace overloads provide access, but in doing so also set the
        // working frame
        powerupSheet[static_cast<int>(id)];
        powerupSheet.setOrigin(7, 7);
        timer = 0;
        killFlag = false;
        hitBox.setPosition(position);
    }
    const sf::Sprite & getSprite() const { return powerupSheet.getSprite(); }
    const sf::Sprite & getGlow() const { return glow; }
    const Item::HBox & getHitBox() const { return hitBox; }
    void update(const sf::Time & elapsedTime) {
        timer += elapsedTime.asMilliseconds();
        const float offset = (3 * sinf(2 * PI * 0.001 * timer + 180));
        // Make the sprite float up and down
        powerupSheet.setPosition(position.x, position.y + offset);
    }

protected:
    HBox hitBox;
    sf::Sprite glow;
    SpriteSheet<0, 75, 13, 13> powerupSheet;
};
}

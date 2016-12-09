//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Drawable.hpp"

namespace detail {
    template <typename DrawPolicy>
    class Lamp : public Drawable<Lamp<DrawPolicy>, DrawPolicy>, public framework::Object {
    public:
        static const int drawOffset = 0;
        Lamp(float _xInit, float _yInit, const sf::Texture & txtr,
                  const sf::Texture & glwTxtr)
            : Object(_xInit, _yInit) {
            glowSprite.setTexture(glwTxtr);
            lampSprite.setTexture(txtr);
            lampSprite.setTextureRect(sf::IntRect(40, 91, 10, 9));
            lampSprite.setPosition(_xInit, _yInit + 8);
            glowSprite.setPosition(_xInit - 250 + 16, _yInit - 250 + 16);
        }
        const sf::Sprite & getSprite() const { return lampSprite; }
        const sf::Sprite & getGlow() const { return glowSprite; }
        template <typename Game>
        void update(const sf::Time &, Game *) {}

    private:
        sf::Sprite lampSprite;
        sf::Sprite glowSprite;
    };
}

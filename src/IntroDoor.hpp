//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "Drawable.hpp"
#include "effectsController.hpp"
#include "spriteSheet.hpp"

namespace detail {
    template <typename DrawPolicy>
    class IntroDoor : private DrawPolicy, public framework::Object {
    private:
        enum class State { dormant, opening, opened };
        mutable SpriteSheet<0, 0, 200, 95> doorSheet;
        uint8_t frameIndex;

    public:
        static const int drawOffset = 60;
        void draw(GfxContext & gfxContext, const sf::View & view) {
            DrawPolicy::draw(*this, gfxContext, view);
        }
        template <typename Game>
        void update(const sf::Time &, Game *) {}
        IntroDoor(float _xInit, float _yInit, const sf::Texture & inpTxtr)
            : Object{_xInit, _yInit}, doorSheet{inpTxtr}, frameIndex{3} {
            doorSheet.setPosition(position.x, position.y);
        }
        const sf::Sprite & getSprite() const {
            return doorSheet[frameIndex];
        }
    };
}

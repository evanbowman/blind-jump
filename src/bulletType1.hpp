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

namespace effect {
template <typename DrawPolicy>
class PlayerShot : public Drawable<PlayerShot<DrawPolicy>, DrawPolicy>,
                   public Effect {
public:
    static const int drawOffset = 0;
    using HBox = framework::HitBox<12, 12, 2, 2>;
    PlayerShot(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr,
               char dir, float x, float y)
        : Effect{x, y}, xInit{x}, yInit{y}, direction{dir}, canPoof{true},
          state{State::travelling} {
        spriteSheet.setTexture(mainTxtr);
        puffSheet.setTexture(mainTxtr);
        glow.setTexture(glowTxtr);
        canPoof = true;
        if (dir == 0 || dir == 1 || dir == 4 || dir == 5) {
            spriteSheet[1];
        } else {
            spriteSheet[0];
        }
    }
    const sf::Sprite & getGlow() const { return glow; }
    const sf::Sprite & getSprite() const {
        switch (state) {
        case State::poof:
            return puffSheet[frameIndex];
            break;

        default:
            return spriteSheet.getSprite();
            break;
        }
    }
    void poof() {
        if (canPoof) {
            canPoof = false;
            state = State::poof;
            timer = 0;
            puffSheet.setPosition(position.x, position.y);
        }
    }
    void update(const sf::Time & elapsedTime) {
        const static float movementRate = 0.00038;
        timer += elapsedTime.asMilliseconds();
        hitBox.setPosition(position);
        switch (state) {
        case State::travelling:
            if (direction == 0 || direction == 4) {
                yInit += movementRate * elapsedTime.asMicroseconds();
                setPosition(xInit + 6, yInit + 12);
            } else if (direction == 1 || direction == 5) {
                yInit -= movementRate * elapsedTime.asMicroseconds();
                setPosition(xInit + 6, yInit);
            } else if (direction == 2 || direction == 6) {
                xInit -= movementRate * elapsedTime.asMicroseconds();
                setPosition(xInit - 5, yInit + 8);
            } else if (direction == 3 || direction == 7) {
                xInit += movementRate * elapsedTime.asMicroseconds();
                setPosition(xInit + 22, yInit + 8);
            }
            spriteSheet.setPosition(position.x, position.y);
            glow.setPosition(position.x - 16, position.y - 11);
            if (timer > 200) {
                if (canPoof) {
                    canPoof = false;
                    state = State::poof;
                    timer = 0;
                    puffSheet.setPosition(position.x, position.y);
                } else {
                    setKillFlag();
                }
            }
            break;

        case State::poof:
            if (direction == 0 || direction == 4) {
                setPosition(xInit + 6, yInit + 12);
            } else if (direction == 1 || direction == 5) {
                setPosition(xInit + 6, yInit);
            } else if (direction == 2 || direction == 6) {
                setPosition(xInit - 5, yInit + 8);
            } else if (direction == 3 || direction == 7) {
                setPosition(xInit + 22, yInit + 8);
            }
            if (timer > 50) {
                timer -= 50;
                ++frameIndex;
                sf::Color color = glow.getColor();
                color.r -= 50;
                color.g -= 50;
                color.b -= 50;
                glow.setColor(color);
                if (frameIndex == 4) {
                    frameIndex = 3;
                    setKillFlag();
                }
            }
            puffSheet.setPosition(position.x, position.y);
            break;
        }
    }
    char getDirection() { return direction; }
    bool checkCanPoof() { return canPoof; }
    void disablePuff() { canPoof = false; }
    const HBox & getHitBox() const { return hitBox; }

private:
    float xInit, yInit;
    HBox hitBox;
    mutable SpriteSheet<44, 75, 16, 16> spriteSheet;
    mutable SpriteSheet<88, 145, 16, 16> puffSheet;
    sf::Sprite glow;
    char direction;
    bool canPoof;
    enum class State { travelling, poof };
    State state;
};
}

//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "bulletType1.hpp"

PlayerShot::PlayerShot(const sf::Texture & mainTxtr,
                       const sf::Texture & glowTxtr, char dir, float x, float y)
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

const sf::Sprite & PlayerShot::getSprite() {
    switch (state) {
    case State::poof:
        return puffSheet[frameIndex];
        break;

    default:
        return spriteSheet.getSprite();
        break;
    }
}

const sf::Sprite & PlayerShot::getGlow() { return glow; }

void PlayerShot::poof() {
    if (canPoof) {
        canPoof = false;
        state = State::poof;
        timer = 0;
        puffSheet.setPosition(position.x, position.y);
    }
}

void PlayerShot::update(const sf::Time & elapsedTime) {
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

char PlayerShot::getDirection() { return direction; }

bool PlayerShot::checkCanPoof() { return canPoof; }

void PlayerShot::disablePuff() { canPoof = false; }

const PlayerShot::HBox & PlayerShot::getHitBox() const { return hitBox; }

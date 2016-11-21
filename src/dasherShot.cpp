//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "dasherShot.hpp"

DasherShot::DasherShot(const sf::Texture & mainTxtr,
                       const sf::Texture & glowTxtr, float x, float y,
                       float dir)
    : Effect(x, y) {
    spriteSheet.setTexture(mainTxtr);
    spriteSheet.setOrigin(6, 6);
    glowSprite.setTexture(glowTxtr);
    glowSprite.setOrigin(22.5, 22.5);
    int diff = pow(-1, rng::random<2>() + rng::random<6, -3>());
    direction = (dir + diff) * (3.14 / 180); // I added 270 previously to get
                                             // the sprite to face in the right
                                             // direction, so subract it
    initialVelocity = 5.8f + (0.8f * rng::random<3>());
    timeout = 0;
    driftSel = rng::random<2>();
}

void DasherShot::update(const sf::Time & elapsedTime) {
    float scale = initialVelocity *
                  Easing::easeOut<2>(timeout, static_cast<int64_t>(830000));
    position.x +=
        scale * (elapsedTime.asMicroseconds() * 0.00005f) * (cos(direction));
    position.y +=
        scale * (elapsedTime.asMicroseconds() * 0.00005f) * (sin(direction));
    hitBox.setPosition(position);
    glowSprite.setPosition(position.x, position.y + 18);
    timer += elapsedTime.asMilliseconds();
    timeout += elapsedTime.asMicroseconds();
    // Alternate between frames
    if (timer > 70) {
        frameIndex ^= 0x01;
        timer -= 70;
    }
    if (driftSel) {
        direction += 0.004f * elapsedTime.asMicroseconds() * 0.00005f;
    } else {
        direction -= 0.004f * elapsedTime.asMicroseconds() * 0.00005f;
    }
    if (timeout > 750000) {
        setKillFlag();
    }
    spriteSheet.setPosition(position.x, position.y);
}

const sf::Sprite & DasherShot::getSprite() { return spriteSheet[frameIndex]; }

const sf::Sprite & DasherShot::getGlow() const { return glowSprite; }

const DasherShot::HBox & DasherShot::getHitBox() const { return hitBox; }

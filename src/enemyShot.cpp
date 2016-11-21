//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "enemyShot.hpp"

EnemyShot::EnemyShot(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr,
                     float x, float y, float dir)
    : Effect(x, y), frameTimer(0) {
    glowSprite.setTexture(glowTxtr);
    glowSprite.setOrigin(22.5, 22.5);
    spriteSheet.setTexture(mainTxtr);
    direction = dir * (3.14 / 180);
}

void EnemyShot::update(const sf::Time & elapsedTime) {
    position.x +=
        4.4 * (elapsedTime.asMicroseconds() * 0.00005f) * (cos(direction));
    position.y +=
        4.4 * (elapsedTime.asMicroseconds() * 0.00005f) * (sin(direction));
    hitBox.setPosition(position);
    glowSprite.setPosition(position.x, position.y + 18);
    timer += elapsedTime.asMilliseconds();
    frameTimer += elapsedTime.asMilliseconds();
    if (frameTimer > 211) {
        frameTimer -= 211;
        if (frameIndex == 0) {
            frameIndex = 1;
        } else {
            frameIndex = 0;
        }
    }
    if (timer > lifetime) {
        setKillFlag();
    }
    float offset = rng::random<20>();
    glowSprite.setColor(
        sf::Color(230 + offset, 230 + offset, 230 + offset, 255));
    spriteSheet.setPosition(position.x, position.y);
}

const sf::Sprite & EnemyShot::getGlow() const { return glowSprite; }

const EnemyShot::HBox & EnemyShot::getHitBox() const { return hitBox; }

const sf::Sprite & EnemyShot::getSprite() { return spriteSheet[frameIndex]; }

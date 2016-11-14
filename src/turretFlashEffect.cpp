//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "turretFlashEffect.hpp"

TurretFlashEffect::TurretFlashEffect(const sf::Texture & txtr, float x, float y)
    : Effect(x, y) {
    spriteSheet.setTexture(txtr);
    bool select = rng::random<2>();
    if (select) {
        spriteSheet.setScale(-1.f, 1.f);
        position.x += 17;
    }
    spriteSheet.setPosition(position.x, position.y);
}

void TurretFlashEffect::update(const sf::Time & elapsedTime) {
    timer += elapsedTime.asMilliseconds();
    if (timer > 40) {
        timer -= 40;
        frameIndex += 1;
        if (frameIndex > 4) {
            setKillFlag();
            frameIndex = 4;
        };
    }
}

const framework::Sprite & TurretFlashEffect::getSprite() const {
    return spriteSheet[frameIndex];
}

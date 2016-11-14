//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "shotPuff.hpp"

ShotPuff::ShotPuff(const sf::Texture & txtr, float x, float y) : Effect(x, y) {
    spriteSheet.setTexture(txtr);
    spriteSheet.setPosition(position.x, position.y);
}

void ShotPuff::update(const sf::Time & elapsedTime) {
    timer += elapsedTime.asMilliseconds();
    if (timer > 50) {
        timer -= 50;
        frameIndex += 1;
        if (frameIndex == 4) {
            frameIndex = 3;
            killFlag = true;
        }
    }
}

const sf::Sprite & ShotPuff::getSprite() const {
    return spriteSheet[frameIndex];
}

//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "FireExplosion.hpp"

FireExplosion::FireExplosion(const sf::Texture & mainTxtr,
                             const sf::Texture & glowTxtr, float x, float y)
    : Effect(x, y), glowFadeTimer(0) {
    spriteSheet.setTexture(mainTxtr);
    spriteSheet.setOrigin(29, 25);
    glow.setTexture(glowTxtr);
    glow.setColor(sf::Color(240, 240, 240));
    spriteSheet.setPosition(position.x, position.y);
    glow.setPosition(position.x - 225, position.y - 225);
}

void FireExplosion::update(const sf::Time & elapsedTime) {
    timer += elapsedTime.asMicroseconds();
    glowFadeTimer += elapsedTime.asMicroseconds();
    static const int frameTransitionTime = 70000;
    if (timer > frameTransitionTime) {
        timer -= frameTransitionTime;
        frameIndex++;
        static const int maxFrame = 8;
        if (frameIndex > maxFrame) {
            frameIndex = maxFrame;
            killFlag = true;
        }
    }
    uint8_t color =
        Easing::easeOut<1>(glowFadeTimer, static_cast<int64_t>(560000)) * 230;
    glow.setColor(sf::Color(color, color, color, 255));
}

const sf::Sprite & FireExplosion::getGlow() const { return glow; }

const sf::Sprite & FireExplosion::getSprite() const {
    return spriteSheet[frameIndex];
}

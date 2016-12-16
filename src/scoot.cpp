//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "scoot.hpp"
#include "angleFunction.hpp"
#include "game.hpp"
#include "player.hpp"
#include <cmath>

Scoot::Scoot(const sf::Texture & mainTxtr, const sf::Texture & shadowTxtr,
             float _xPos, float _yPos)
    : Enemy(_xPos, _yPos), spriteSheet(mainTxtr), speedScale(0.5f),
      state(State::drift1), timer(rng::random<1800>()) {
    spriteSheet.setOrigin(6, 6);
    hitBox.setPosition(position.x, position.y);
    shadow.setTexture(shadowTxtr);
    float dir = rng::random<359>();
    hSpeed = cos(dir) * 0.5;
    vSpeed = sin(dir) * 0.5;
    health = 2;
}

const Scoot::HBox & Scoot::getHitBox() const { return hitBox; }

void Scoot::changeDir(float dir) {
    hSpeed = std::cos(dir);
    vSpeed = std::sin(dir);
}

void Scoot::update(Game * pGame, const std::vector<wall> & w,
                   const sf::Time & elapsedTime) {
    EffectGroup & effects = pGame->getEffects();
    for (auto & element : effects.get<9>()) {
        if (hitBox.overlapping(element->getHitBox()) &&
            element->checkCanPoof()) {
            if (health == 1) {
                element->disablePuff();
                element->setKillFlag();
            }
            element->poof();
            health -= 1;
            colored = true;
            colorAmount = 1.f;
        }
    }
    if (health == 0) {
        int select = rng::random<5>();
        if (select == 0) {
            effects.add<EffectRef::Heart>(
                getgResHandlerPtr()->getTexture(
                    ResHandler::Texture::gameObjects),
                getgResHandlerPtr()->getTexture(ResHandler::Texture::redglow),
                position.x, position.y + 4, Item::Type::Heart);
        } else {
            effects.add<EffectRef::Coin>(
                getgResHandlerPtr()->getTexture(
                    ResHandler::Texture::gameObjects),
                getgResHandlerPtr()->getTexture(ResHandler::Texture::blueglow),
                position.x, position.y + 4, Item::Type::Coin);
        }
        effects.add<EffectRef::FireExplosion>(
            getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
            getgResHandlerPtr()->getTexture(
                ResHandler::Texture::fireExplosionGlow),
            position.x, position.y - 2);
        killFlag = true;
    }
    Enemy::updateColor(elapsedTime);
    hitBox.setPosition(position.x, position.y);
    spriteSheet.setPosition(position.x, position.y);
    shadow.setPosition(position.x - 6, position.y + 2);
    Player & player = pGame->getPlayer();
    if (position.x > player.getXpos()) {
        spriteSheet.setScale(1, 1);
    } else {
        spriteSheet.setScale(-1, 1);
    }
    switch (state) {
    case State::drift1:
        timer += elapsedTime.asMilliseconds();
        if (timer > 1800) {
            timer -= 1800;
            ;
            state = State::drift2;
            if (rng::random<2>()) {
                changeDir(atan((position.y - player.getYpos()) /
                               (position.x - player.getXpos())));
            } else {
                changeDir(static_cast<float>(rng::random<359>()));
            }
        }
        break;

    case State::drift2:
        timer += elapsedTime.asMilliseconds();
        if (timer > 1800) {
            timer -= 1800;
            state = State::shoot;
        }
        break;

    case State::shoot: {
        const sf::Vector2f playerPos = player.getPosition();
        effects.add<EffectRef::TurretFlashEffect>(
            getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
            position.x - 8, position.y - 12);
        effects.add<EffectRef::TurretShot>(
            position.x - 8, position.y - 12,
            angleFunction(playerPos.x + 16, playerPos.y + 8, position.x - 8,
                          position.y - 8));
        pGame->getSounds().play(ResHandler::Sound::laser,
                                this->shared_from_this(), 320.f, 30.f);
        state = State::recoil;
        changeDir(atan((position.y - player.getYpos()) /
                       (position.x - player.getXpos())));
        hSpeed *= -1;
        vSpeed *= -1;
        // Correct for negative values in arctan calculation
        if (position.x > player.getXpos()) {
            hSpeed *= -1;
            vSpeed *= -1;
        }
        speedScale = 2.f;
    } break;

    case State::recoil:
        timer += elapsedTime.asMilliseconds();
        speedScale *= 0.99;
        if (timer > 400) {
            timer -= 400;
            state = State::drift1;
            speedScale = 0.5f;
            if (rng::random<2>()) {
                changeDir(atan((position.y - player.getYpos()) /
                               (position.x - player.getXpos())));
            } else {
                changeDir(rng::random<359>());
            }
        }
        break;
    }
    uint_fast8_t collisionMask =
        Enemy::checkWallCollision(w, position.x - 8, position.y - 8);
    if (collisionMask) {
        hSpeed = 0;
        vSpeed = 0;
        if (collisionMask & 0x01) {
            hSpeed += 1;
        }
        if (collisionMask & 0x02) {
            hSpeed -= 1;
        }
        if (collisionMask & 0x04) {
            vSpeed += 1;
        }
        if (collisionMask & 0x08) {
            vSpeed -= 1;
        }
    }
    position.x +=
        (elapsedTime.asMicroseconds() * 0.00006f) * hSpeed * speedScale;
    position.y +=
        (elapsedTime.asMicroseconds() * 0.00006f) * vSpeed * speedScale;
    frameTimer += elapsedTime.asMilliseconds();
    if (frameTimer > 87) {
        frameTimer -= 87;
        frameIndex ^= 0x01;
    }
}

const sf::Sprite & Scoot::getSprite() const { return spriteSheet[frameIndex]; }

const sf::Sprite & Scoot::getShadow() const { return shadow; }

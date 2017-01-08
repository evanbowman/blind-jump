#include "turret.hpp"
#include "angleFunction.hpp"
#include "player.hpp"
#include <cmath>
#include "Game.hpp"

Turret::Turret(const sf::Texture & gameObjects, float _xPos, float _yPos)
    : Enemy(_xPos, _yPos), state(State::closed), frameIndex(0), timer(0), hp(6),
      colorTimer(0), isColored(0), colorAmount(0) {
    turretSheet.setTexture(gameObjects);
    shadowSheet.setTexture(gameObjects);
    hitBox.setPosition(position.x, position.y);
    turretSheet.setPosition(position.x, position.y);
    shadowSheet.setPosition(position.x, position.y + 18);
    hitBox.setPosition(position.x, position.y);
}

const sf::Sprite & Turret::getSprite() { return turretSheet[frameIndex]; }

void Turret::update(const sf::Time & elapsedTime, Game * pGame) {
    EffectGroup & effects = pGame->getEffects();
    Player & player = pGame->getPlayer();
    if (isColored) {
        colorTimer += elapsedTime.asMilliseconds();
        if (colorTimer > 20.f) {
            colorTimer -= 20.f;
            colorAmount -= 0.1f;
        }
        if (colorAmount <= 0.f) {
            isColored = false;
        }
    }
    for (auto & element : effects.get<EffectRef::PlayerShot>()) {
        if (hitBox.overlapping(element->getHitBox()) &&
            element->checkCanPoof()) {
            if (hp == 1) {
                element->disablePuff();
                element->setKillFlag();
            }
            element->poof();
            hp -= 1;
            isColored = true;
            colorAmount = 1.f;
        }
    }
    for (auto & helper : pGame->getHelperGroup().get<HelperRef::Laika>()) {
	if (hitBox.overlapping(helper->getHitBox())) {
	    health = 0;
	}
    }
    if (hp == 0) {
        killFlag = true;
        if (rng::random<4>() == 0) {
            effects.add<EffectRef::Heart>(
                getgResHandlerPtr()->getTexture(
                    ResHandler::Texture::gameObjects),
                getgResHandlerPtr()->getTexture(ResHandler::Texture::redglow),
                position.x + 8, position.y + 10, Item::Type::Heart);
        } else {
            effects.add<EffectRef::Coin>(
                getgResHandlerPtr()->getTexture(
                    ResHandler::Texture::gameObjects),
                getgResHandlerPtr()->getTexture(ResHandler::Texture::blueglow),
                position.x + 8, position.y + 10, Item::Type::Coin);
        }
        effects.add<EffectRef::FireExplosion>(
            getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
            getgResHandlerPtr()->getTexture(
                ResHandler::Texture::fireExplosionGlow),
            position.x + 12, position.y + 12);
    }
    switch (state) {
    case State::closed:
        if (std::sqrt(std::pow((position.x - player.getXpos() + 8), 2) +
                      std::pow((position.y - player.getYpos() + 16), 2)) <
            174) {
            state = State::opening;
            timer = 0;
            frameIndex = 0;
        }
        break;

    case State::opening:
        timer += elapsedTime.asMicroseconds();
        if (timer > 50000) {
            timer = 0;
            frameIndex += 1;
            if (frameIndex > 4) {
                frameIndex = 4;
                state = State::shoot1;
            }
        }
        break;

    case State::shoot1:
        target = player.getPosition();
        timer += elapsedTime.asMicroseconds();
        if (timer > 200000) {
            effects.add<EffectRef::TurretFlashEffect>(
                getgResHandlerPtr()->getTexture(
                    ResHandler::Texture::gameObjects),
                position.x, position.y + 8);
            effects.add<EffectRef::EnemyShot>(
                getgResHandlerPtr()->getTexture(
                    ResHandler::Texture::gameObjects),
                getgResHandlerPtr()->getTexture(ResHandler::Texture::redglow),
                position.x, position.y + 6,
                angleFunction(target.x + 16, target.y + 8, position.x + 18,
                              position.y + 8));
            timer = 0;
            state = State::shoot2;
        }
        break;

    case State::shoot2:
        timer += elapsedTime.asMicroseconds();
        if (timer > 200000) {
            effects.add<EffectRef::TurretFlashEffect>(
                getgResHandlerPtr()->getTexture(
                    ResHandler::Texture::gameObjects),
                position.x, position.y + 8);
            effects.add<EffectRef::EnemyShot>(
                getgResHandlerPtr()->getTexture(
                    ResHandler::Texture::gameObjects),
                getgResHandlerPtr()->getTexture(ResHandler::Texture::redglow),
                position.x, position.y + 8,
                angleFunction(target.x + 16, target.y + 8, position.x + 18,
                              position.y + 6));
            timer = 0;
            state = State::shoot3;
        }
        break;

    case State::shoot3:
        timer += elapsedTime.asMicroseconds();
        if (timer > 200000) {
            effects.add<EffectRef::TurretFlashEffect>(
                getgResHandlerPtr()->getTexture(
                    ResHandler::Texture::gameObjects),
                position.x, position.y + 8);
            effects.add<EffectRef::EnemyShot>(
                getgResHandlerPtr()->getTexture(
                    ResHandler::Texture::gameObjects),
                getgResHandlerPtr()->getTexture(ResHandler::Texture::redglow),
                position.x, position.y + 8,
                angleFunction(target.x + 16, target.y + 8, position.x + 18,
                              position.y + 6));
            timer = 0;
            state = State::rest;
        }
        break;

    case State::rest:
        timer += elapsedTime.asMicroseconds();
        if (timer > 1200000) {
            if (std::sqrt(std::pow((position.x - player.getXpos() + 8), 2) +
                          std::pow((position.y - player.getYpos() + 16), 2)) <
                174) {
                state = State::shoot1;
            } else {
                state = State::closing;
            }
            timer = 0;
        }
        break;

    case State::closing:
        timer += elapsedTime.asMicroseconds();
        if (timer > 50000) {
            timer = 0;
            frameIndex -= 1;
            if (frameIndex < 0) {
                frameIndex = 0;
                state = State::closed;
            }
        }
        break;
    }
}

const Turret::HBox & Turret::getHitBox() const { return hitBox; }

const sf::Sprite & Turret::getShadow() { return shadowSheet[frameIndex]; }

bool Turret::colored() { return isColored; }

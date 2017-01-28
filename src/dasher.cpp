#include "dasher.hpp"
#include "Game.hpp"
#include "angleFunction.hpp"
#include <cmath>

Dasher::Blur::Blur(sf::Sprite * spr, float xInit, float yInit) {
    this->spr = *spr;
    this->xInit = xInit;
    this->yInit = yInit;
    killflag = false;
    timer = 0;
    sf::Color c = this->spr.getColor();
    c.a -= 120;
    c.r -= 30;
    c.g -= 30;
    c.b -= 10;
    this->spr.setColor(c);
    this->spr.setPosition(xInit, yInit);
}

sf::Sprite * Dasher::Blur::getSprite() { return &spr; }

void Dasher::Blur::update(const sf::Time & elapsedTime) {
    timer += elapsedTime.asMilliseconds();
    if (timer > 18) {
        timer = 0;
        sf::Color c = spr.getColor();
        if (c.a > 30) {
            c.a -= 30;
            spr.setColor(c);
        } else {
            killflag = true;
        }
    }
}

bool Dasher::Blur::getKillFlag() { return killflag; }

const Dasher::HBox & Dasher::getHitBox() const { return hitBox; }

Dasher::Dasher(const sf::Texture & mainTxtr, float _xPos, float _yPos)
    : Enemy(_xPos, _yPos), shotCount(0), state(State::idle),
      dasherSheet(mainTxtr), hSpeed(0.f), vSpeed(0.f),
      timer(0) {
    dasherSheet.setOrigin(14, 8);
    shadow.setTexture(mainTxtr);
    shadow.setTextureRect(sf::IntRect(0, 100, 18, 16));
    health = 5;
    hitBox.setPosition(position.x, position.y);
}

const sf::Sprite & Dasher::getSprite() const {
    return dasherSheet[frameIndex];
}

const sf::Sprite & Dasher::getShadow() const { return shadow; }

void Dasher::update(Game * pGame, const std::vector<wall> & walls,
                    const sf::Time & elapsedTime) {
    auto & effects = pGame->getEffects();
    auto & details = pGame->getDetails();
    auto & player = pGame->getPlayer();
    if (health > 0) {
        for (auto & element : effects.get<EffectRef::PlayerShot>()) {
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
        for (auto & helper : pGame->getHelperGroup().get<HelperRef::Laika>()) {
            if (hitBox.overlapping(helper->getHitBox())) {
                health = 0;
            }
        }
        if (health == 0) {
	    hSpeed = 0;
	    vSpeed = 0;
	    frameIndex = 0;
	    killFlag = true;
	    details.add<DetailRef::DasherCorpse>(this->getPosition(),
						 getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
						 dasherSheet.getScale().x);
	    unsigned long int temp = rng::random<4>();
	    if (temp < 1) {
		effects.add<EffectRef::Heart>(
					      getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
					      getgResHandlerPtr()->getTexture(ResHandler::Texture::redglow),
					      position.x, position.y + 4, Item::Type::Heart);
	    } else if (temp < 3) {
		effects.add<EffectRef::GoldHeart>(
						  getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
						  getgResHandlerPtr()->getTexture(ResHandler::Texture::yellowGlow),
						  position.x, position.y + 4, Item::Type::GoldHeart);
	    } else {
		effects.add<EffectRef::Coin>(
					     getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
					     getgResHandlerPtr()->getTexture(ResHandler::Texture::blueglow),
					     position.x, position.y + 4, Item::Type::Coin);
	    }
	    effects.add<EffectRef::SmallExplosion>(
						   getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
						   getgResHandlerPtr()->getTexture(ResHandler::Texture::fireExplosionGlow),
						   position.x, position.y - 2);
	    blurEffects.clear();
        }
    }
    SoundController & sounds = pGame->getSounds();
    Enemy::updateColor(elapsedTime);
    dasherSheet.setPosition(position.x + 4, position.y);
    shadow.setPosition(position.x - 4, position.y + 22);
    hitBox.setPosition(position.x, position.y);
    timer += elapsedTime.asMilliseconds();
    auto facePlayer = [this, player]() {
        if (this->position.x > player.getXpos()) {
            this->dasherSheet.setScale(1, 1);
        } else {
            this->dasherSheet.setScale(-1, 1);
        }
    };
    switch (state) {
    case State::idle:
        if (timer >= 200) {
            timer -= 200;
            const int select = rng::random<2>();
            if (select) {
                state = State::dashBegin;
                frameIndex = 1;
            } else {
                state = State::shootBegin;
                frameIndex = 3;
            }
        }
        break;

    case State::pause:
        if (timer >= 200) {
            timer -= 200;
            state = State::dashBegin;
            frameIndex = 1;
        }
        break;

    case State::shooting:
        facePlayer();
        frameTimer += elapsedTime.asMilliseconds();
        if (frameTimer > 80 && shotCount < 3) {
            frameTimer -= 80;
            shotCount++;
            if (position.x > player.getXpos()) {
                effects.add<EffectRef::TurretFlashEffect>(
                    getgResHandlerPtr()->getTexture(
                        ResHandler::Texture::gameObjects),
                    position.x - 14, position.y + 2);
                effects.add<EffectRef::DasherShot>(
                    position.x - 12, position.y,
                    angleFunction(target.x + 8, target.y + 8, position.x,
                                  position.y));
                pGame->getSounds().play(ResHandler::Sound::silenced,
                                        this->shared_from_this(), 220.f, 5.f);
            } else {
                effects.add<EffectRef::TurretFlashEffect>(
                    getgResHandlerPtr()->getTexture(
                        ResHandler::Texture::gameObjects),
                    position.x + 6, position.y + 2);
                effects.add<EffectRef::DasherShot>(
                    position.x + 4, position.y,
                    angleFunction(target.x, target.y + 8, position.x,
                                  position.y));
                pGame->getSounds().play(ResHandler::Sound::silenced,
                                        this->shared_from_this(), 220.f, 5.f);
            }
        }
        if (timer > 300) {
            timer -= 300;
            shotCount = 0;
            state = State::pause;
        }
        break;

    case State::shootBegin:
        facePlayer();
        if (timer > 80) {
            timer -= 80;
            frameTimer = 0;
            target = player.getPosition();
            state = State::shooting;
            frameIndex = 4;
        }
        break;

    case State::dashBegin:
    begin:
        facePlayer();
        if (timer > 352) {
            timer -= 352;
            state = State::dashing;
            sounds.play(ResHandler::Sound::wooshMono, this->shared_from_this(),
                        220.f, 5.f);
            frameIndex = 2;
            uint8_t tries{0};
            float dir{static_cast<float>(rng::random<359>())};
            do {
                tries++;
                if (tries > 254) {
                    state = State::shootBegin;
                    frameIndex = 3;
                    goto begin;
                }
                dir += 12;
            } while (wallInPath(walls, dir, position.x, position.y));
            hSpeed = 5 * cos(dir);
            vSpeed = 5 * sin(dir);
            if (hSpeed > 0) {
                dasherSheet.setScale(-1, 1);
            } else {
                dasherSheet.setScale(1, 1);
                dasherSheet.setScale(1, 1);
            }
        }
        break;

    case State::dashing:
        frameTimer += elapsedTime.asMilliseconds();
        if (frameTimer > 40) {
            frameTimer = 0;
            blurEffects.emplace_back(dasherSheet.getSpritePtr(), position.x,
                                     position.y);
        }
        if (timer > 250) {
            timer -= 250;
            state = State::dashEnd;
            frameIndex = 1;
            hSpeed = 0.f;
            vSpeed = 0.f;
        }

        if (Enemy::checkWallCollision(walls, position.x, position.y)) {
            hSpeed *= -1.f;
            vSpeed *= -1.f;
        }
        break;

    case State::dashEnd:
        if (timer > 150) {
            blurEffects.clear();
            timer -= 150;
            state = State::idle;
            frameIndex = 0;
        }
        break;
    }

    if (!blurEffects.empty()) {
        for (auto it = blurEffects.begin(); it != blurEffects.end();) {
            if (it->getKillFlag())
                it = blurEffects.erase(it);
            else {
                it->update(elapsedTime);
                ++it;
            }
        }
    }

    position.x += hSpeed * (elapsedTime.asMicroseconds() * 0.00005f);
    position.y += vSpeed * (elapsedTime.asMicroseconds() * 0.00005f);
}

Dasher::State Dasher::getState() const { return state; }

std::vector<Dasher::Blur> * Dasher::getBlurEffects() { return &blurEffects; }

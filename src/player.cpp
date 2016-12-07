//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "player.hpp"
#include "game.hpp"

static const float MOVEMENT_RATE_CONSTANT = 0.000054f;

Player::Player(float _xPos, float _yPos)
    : gun{}, health(4), xPos(_xPos - 17), // Magic number that puts the player
                                          // in the direct center of the screen.
                                          // Hmmm why does it work...
      yPos(_yPos), frameIndex(5), sheetIndex(Sheet::stillDown),
      cachedSheet(Sheet::stillDown), lSpeed(0.f), rSpeed(0.f), uSpeed(0.f),
      dSpeed(0.f), animationTimer(0), dashTimer(0), invulnerable(false),
      state(Player::State::nominal), colorAmount(0.f), colorTimer(0),
      renderType(Rendertype::shadeDefault), upPrevious(false),
      downPrevious(false), leftPrevious(false), rightPrevious(false) {
    init();
}

void Player::init() {
    deathSheet.setTexture(
        getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects));
    walkDown.setTexture(
        getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects));
    walkUp.setTexture(
        getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects));
    walkLeft.setTexture(
        getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects));
    walkRight.setTexture(
        getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects));
    walkDown.setPosition(xPos, yPos);
    walkUp.setPosition(xPos, yPos);
    walkLeft.setPosition(xPos, yPos);
    walkRight.setPosition(xPos, yPos);
    shadowSprite.setPosition(xPos + 7, yPos + 24);
    dashSheet.setPosition(xPos, yPos);
    deathSheet.setPosition(xPos - 13, yPos - 1);
    dashSheet.setTexture(
        getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects));
    dashSheet.setOrigin(0, 1);
    shadowSprite.setTexture(
        getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects));
    shadowSprite.setTextureRect(sf::IntRect(0, 100, 18, 16));
    gun.gunSpr.setPosition(xPos, yPos);
    gun.gunSpr.setTexture(
        getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects));
}

sf::Vector2f Player::getPosition() { return sf::Vector2f(xPos + 16, yPos); }

void Player::setPosition(float _xPos, float _yPos) {
    xPos = _xPos;
    yPos = _yPos;
    hitBox.setPosition({xPos, yPos});
    walkDown.setPosition(xPos, yPos);
    walkUp.setPosition(xPos, yPos);
    walkLeft.setPosition(xPos, yPos);
    walkRight.setPosition(xPos, yPos);
    deathSheet.setPosition(xPos - 13, yPos - 1);
    dashSheet.setPosition(xPos, yPos);
    shadowSprite.setPosition(xPos + 7, yPos + 24);
}

float Player::getXpos() const { return xPos; }

float Player::getYpos() const { return yPos; }

template <Player::Sheet S>
void regKeyResponse(bool key1, bool key2, bool key3, bool key4,
                    Player::Sheet & sheetIndex, float & speed, bool collision) {
    if (key1) {
        if (!key2 && !key3 && !key4 && sheetIndex != S) {
            sheetIndex = S;
        }
        if (!collision) {
            if (key3 || key4) {
                speed = 1.70f;
            } else {
                speed = 2.20f;
            }
        } else {
            speed = 0.f;
        }
    } else {
        speed = 0.f;
    }
}

template <Player::Sheet S>
void altKeyResponse(bool key1, bool key2, bool key3, Player::Sheet & sheetIndex,
                    bool collision, float & speed) {
    if (key1) {
        sheetIndex = S;
        if (!collision) {
            if (key2 || key3) {
                speed = 1.40f;
            } else {
                speed = 1.80f;
            }
        } else {
            speed = 0.f;
        }
    } else {
        speed = 0.f;
    }
}

template <Player::Sheet S, uint8_t maxIndx>
void onKeyReleased(bool key1, bool key2, bool key3, bool key4, bool keyprev,
                   bool x, Player::Sheet & sheetIndex, uint8_t & frmIndex) {
    if (!key1 && keyprev) {
        if (!key2 && !key3 && !key4) {
            if (!x) {
                sheetIndex = S;
                frmIndex = maxIndx;
            } else {
                switch (sheetIndex) {
                case Player::Sheet::walkDown:
                    sheetIndex = Player::Sheet::stillDown;
                    break;

                case Player::Sheet::walkUp:
                    sheetIndex = Player::Sheet::stillUp;
                    break;

                case Player::Sheet::walkLeft:
                    sheetIndex = Player::Sheet::stillLeft;
                    break;

                case Player::Sheet::walkRight:
                    sheetIndex = Player::Sheet::stillRight;
                    break;

                default:
                    break;
                }
            }
        }
    }
}

template <int spd>
void setSpeed(bool key1, bool key2, bool key3, bool collision, float & speed) {
    if (key1 && !collision) {
        if (key2 || key3) {
            speed = spd * 0.8;
        } else {
            speed = spd;
        }
    } else {
        speed = 0;
    }
}

void Player::update(Game * pGM, const sf::Time & elapsedTime,
                    SoundController & sounds) {
    InputController * pInput(pGM->getPInput());
    tileController & tiles(pGM->getTileController());
    DetailGroup & details(pGM->getDetails());
    EffectGroup & effects(pGM->getEffects());
    ui::Frontend * pUiFrontend(pGM->getPUIFrontend());
    bool shoot(pInput->shootPressed());
    bool action(pInput->actionPressed());
    bool up(pInput->upPressed());
    bool down(pInput->downPressed());
    bool left(pInput->leftPressed());
    bool right(pInput->rightPressed());
    bool collisionUp(false);
    bool collisionDown(false);
    bool collisionLeft(false);
    bool collisionRight(false);
    uint_fast8_t collisionMask = checkCollisionWall(tiles.walls, yPos, xPos);
    collisionMask |= checkCollisionChest(details.get<1>(), yPos, xPos);
    if (collisionMask & 0x01) {
        collisionLeft = true;
    }
    if (collisionMask & 0x02) {
        collisionRight = true;
    }
    if (collisionMask & 0x04) {
        collisionUp = true;
    }
    if (collisionMask & 0x08) {
        collisionDown = true;
    }
    switch (state) {
    case State::deactivated:
        sheetIndex = Sheet::stillDown;
        frameIndex = 5;
        lSpeed = 0.f;
        rSpeed = 0.f;
        uSpeed = 0.f;
        dSpeed = 0.f;
        gun.timeout = 0;
        upPrevious = false;
        downPrevious = false;
        leftPrevious = false;
        rightPrevious = false;
        break;

    case State::nominal:
        updateGun(elapsedTime, shoot, effects, sounds, pGM->getUI());
        if (!shoot) {
            regKeyResponse<Sheet::walkUp>(up, down, left, right, sheetIndex,
                                          uSpeed, collisionUp);
            regKeyResponse<Sheet::walkDown>(down, up, left, right, sheetIndex,
                                            dSpeed, collisionDown);
            regKeyResponse<Sheet::walkLeft>(left, right, down, up, sheetIndex,
                                            lSpeed, collisionLeft);
            regKeyResponse<Sheet::walkRight>(right, left, down, up, sheetIndex,
                                             rSpeed, collisionRight);
        } else {
            if (sheetIndex == Sheet::walkUp || sheetIndex == Sheet::stillUp) {
                altKeyResponse<Sheet::walkUp>(up, left, right, sheetIndex,
                                              collisionUp, uSpeed);
                altKeyResponse<Sheet::walkUp>(down, left, right, sheetIndex,
                                              collisionDown, dSpeed);
                altKeyResponse<Sheet::walkUp>(left, up, down, sheetIndex,
                                              collisionLeft, lSpeed);
                altKeyResponse<Sheet::walkUp>(right, up, down, sheetIndex,
                                              collisionRight, rSpeed);
            }
            if (sheetIndex == Sheet::walkDown ||
                sheetIndex == Sheet::stillDown) {
                altKeyResponse<Sheet::walkDown>(up, left, right, sheetIndex,
                                                collisionUp, uSpeed);
                altKeyResponse<Sheet::walkDown>(down, left, right, sheetIndex,
                                                collisionDown, dSpeed);
                altKeyResponse<Sheet::walkDown>(left, up, down, sheetIndex,
                                                collisionLeft, lSpeed);
                altKeyResponse<Sheet::walkDown>(right, up, down, sheetIndex,
                                                collisionRight, rSpeed);
            }
            if (sheetIndex == Sheet::walkRight ||
                sheetIndex == Sheet::stillRight) {
                altKeyResponse<Sheet::walkRight>(up, left, right, sheetIndex,
                                                 collisionUp, uSpeed);
                altKeyResponse<Sheet::walkRight>(down, left, right, sheetIndex,
                                                 collisionDown, dSpeed);
                altKeyResponse<Sheet::walkRight>(left, up, down, sheetIndex,
                                                 collisionLeft, lSpeed);
                altKeyResponse<Sheet::walkRight>(right, up, down, sheetIndex,
                                                 collisionRight, rSpeed);
            }
            if (sheetIndex == Sheet::walkLeft ||
                sheetIndex == Sheet::stillLeft) {
                altKeyResponse<Sheet::walkLeft>(up, left, right, sheetIndex,
                                                collisionUp, uSpeed);
                altKeyResponse<Sheet::walkLeft>(down, left, right, sheetIndex,
                                                collisionDown, dSpeed);
                altKeyResponse<Sheet::walkLeft>(left, up, down, sheetIndex,
                                                collisionLeft, lSpeed);
                altKeyResponse<Sheet::walkLeft>(right, up, down, sheetIndex,
                                                collisionRight, rSpeed);
            }
        }
        onKeyReleased<Player::Sheet::stillLeft, 5>(
            left, right, up, down, leftPrevious, shoot, sheetIndex, frameIndex);
        onKeyReleased<Player::Sheet::stillRight, 5>(right, left, up, down,
                                                    rightPrevious, shoot,
                                                    sheetIndex, frameIndex);
        onKeyReleased<Player::Sheet::stillUp, 4>(
            up, left, right, down, upPrevious, shoot, sheetIndex, frameIndex);
        onKeyReleased<Player::Sheet::stillDown, 4>(
            down, left, right, up, downPrevious, shoot, sheetIndex, frameIndex);

        if (action && !actionPrevious && (left || right || up || down)) {
            state = State::prepdash;
            if (sheetIndex == Sheet::stillDown ||
                sheetIndex == Sheet::walkDown) {
                frameIndex = 6;
            } else if (sheetIndex == Sheet::stillUp ||
                       sheetIndex == Sheet::walkUp) {
                frameIndex = 8;
            } else if (sheetIndex == Sheet::stillLeft ||
                       sheetIndex == Sheet::walkLeft) {
                frameIndex = 0;
            } else if (sheetIndex == Sheet::stillRight ||
                       sheetIndex == Sheet::walkRight) {
                frameIndex = 2;
            }
            cachedSheet =
                sheetIndex; // So we know what to go back to after dash
            sheetIndex = Sheet::dashSheet;
        }
        actionPrevious = action;
        upPrevious = up;
        downPrevious = down;
        leftPrevious = left;
        rightPrevious = right;
        // If the action button is pressed, open nearby chests
        if (state == State::nominal) {
            std::vector<TreasureChest> & chests = details.get<1>();
            for (auto & chest : chests) {
                if (std::abs(xPos - chest.getPosition().x) < 32 &&
                    std::abs(yPos - chest.getPosition().y) < 26 &&
                    chest.getState() == TreasureChest::State::closed &&
                    action) {
                    util::sleep(milliseconds(40));
                    chest.setState(TreasureChest::State::opening);
                    pGM->getUI().setPowerup(chest.getPowerup());
                }
            }
        }
        for (auto & term : details.get<7>()) {
            const sf::Vector2f termPos = term.getPosition();
            const Terminal::State termState = term.getState();
            if (std::sqrt(std::pow(xPos - termPos.x, 2) +
                          std::pow(yPos - termPos.y, 2)) < 48.f) {
                if (termState == Terminal::State::dormant) {
                    term.setState(Terminal::State::wakeup);
                }
            } else {
                if (termState == Terminal::State::awake) {
                    term.setState(Terminal::State::poweroff);
                }
            }
        }
        break;

    case State::prepdash:
        if (gun.timeout != 0) {
            gun.timeout = 40000;
        }
        setSpeed<1>(left, up, down, collisionLeft, lSpeed);
        setSpeed<1>(right, up, down, collisionRight, rSpeed);
        setSpeed<1>(up, left, right, collisionUp, uSpeed);
        setSpeed<1>(down, left, right, collisionDown, dSpeed);
        dashTimer += elapsedTime.asMicroseconds();
        if (dashTimer > 80000) {
            dashTimer = 0;
            state = State::dashing;
            switch (frameIndex) {
            case 6:
                if (uSpeed > 0.f ||
                    (uSpeed == 0.f && dSpeed == 0.f)) { // Sidestep
                    if (lSpeed > 0.f) {
                        frameIndex = 5;
                    } else if (rSpeed > 0.f) {
                        frameIndex = 4;
                    } else {
                        frameIndex = 7;
                    }
                } else { // Forward dash
                    frameIndex = 14;
                }
                break;

            case 8:
                if (dSpeed > 0.f || (uSpeed == 0.f && dSpeed == 0.f)) {
                    if (lSpeed > 0.f) {
                        frameIndex = 10;
                    } else if (rSpeed > 0.f) {
                        frameIndex = 11;
                    } else {
                        frameIndex = 9;
                    }
                } else {
                    frameIndex = 15;
                }
                break;

            case 0:
                if (rSpeed > 0.f) {
                    frameIndex = 1;
                } else if (lSpeed == 0.f) {
                    frameIndex = 1;
                } else {
                    frameIndex = 12;
                }
                break;

            case 2:
                if (lSpeed > 0.f) {
                    frameIndex = 3;
                } else if (rSpeed == 0.f) {
                    frameIndex = 3;
                } else {
                    frameIndex = 13;
                }
                break;

            default:
                break;
            }
        }
        break;

    case State::dashing:
        setSpeed<7>(leftPrevious, upPrevious, downPrevious, collisionLeft,
                    lSpeed);
        setSpeed<7>(rightPrevious, upPrevious, downPrevious, collisionRight,
                    rSpeed);
        setSpeed<7>(upPrevious, leftPrevious, rightPrevious, collisionUp,
                    uSpeed);
        setSpeed<7>(downPrevious, leftPrevious, rightPrevious, collisionDown,
                    dSpeed);
        dashTimer += elapsedTime.asMicroseconds();
        if (dashTimer > 115000) {
            dashTimer = 0;
            state = State::cooldown;
        }
        break;

    case State::cooldown:
        setSpeed<1>(leftPrevious, upPrevious, downPrevious, collisionLeft,
                    lSpeed);
        setSpeed<1>(rightPrevious, upPrevious, downPrevious, collisionRight,
                    rSpeed);
        setSpeed<1>(upPrevious, leftPrevious, rightPrevious, collisionUp,
                    uSpeed);
        setSpeed<1>(downPrevious, leftPrevious, rightPrevious, collisionDown,
                    dSpeed);
        dashTimer += elapsedTime.asMicroseconds();
        if (dashTimer > 250000) {
            dashTimer = 0;
            state = State::nominal;
            sheetIndex = cachedSheet;
        }
        break;

    case State::dead:
        lSpeed = 0.f;
        rSpeed = 0.f;
        uSpeed = 0.f;
        dSpeed = 0.f;
        break;
    }
    updateColor(elapsedTime);
    if (health > 0 && state != Player::State::deactivated) {
        checkEffectCollisions(effects, pUiFrontend);
        enemyController & enemies = pGM->getEnemyController();
        checkEnemyCollisions(enemies, pUiFrontend);
    }
    if (health <= 0 && state != Player::State::dead) {
        state = Player::State::dead;
        sheetIndex = Player::Sheet::deathSheet;
        frameIndex = 0;
    }
    xPos -= (lSpeed + -rSpeed) *
            (elapsedTime.asMicroseconds() * MOVEMENT_RATE_CONSTANT);
    yPos -= (uSpeed + -dSpeed) *
            (elapsedTime.asMicroseconds() * MOVEMENT_RATE_CONSTANT);
    setPosition(xPos, yPos);
    if (!blurs.empty()) {
        for (auto it = blurs.begin(); it != blurs.end();) {
            if (it->getKillFlag())
                it = blurs.erase(it);
            else {
                it->update(elapsedTime);
                ++it;
            }
        }
    }
    switch (sheetIndex) {
    case Sheet::stillDown:
        if (gun.timeout > 0) {
            gun.gunSpr.setPosition(xPos + 12, yPos + 15);
        }
        break;

    case Sheet::stillUp:
        break;

    case Sheet::stillLeft:
        if (gun.timeout > 0) {
            gun.gunSpr.setPosition(xPos + 2, yPos + 13);
        }
        break;

    case Sheet::stillRight:
        if (gun.timeout > 0) {
            gun.gunSpr.setPosition(xPos + 19, yPos + 13);
        }
        break;

    case Sheet::walkDown:
        if (gun.timeout > 0) {
            gun.gunSpr.setPosition(xPos + 12, yPos + 15);
        }
        updateAnimation(elapsedTime, 9, 100000);
        break;

    case Sheet::walkUp:
        updateAnimation(elapsedTime, 9, 100000);
        break;

    case Sheet::walkLeft:
        if (gun.timeout > 0) {
            gun.gunSpr.setPosition(xPos + 2, yPos + 13);
        }
        updateAnimation(elapsedTime, 5, 100000);
        break;

    case Sheet::walkRight:
        if (gun.timeout > 0) {
            gun.gunSpr.setPosition(xPos + 19, yPos + 13);
        }
        updateAnimation(elapsedTime, 5, 100000);
        break;

    case Sheet::deathSheet:
        if (frameIndex < 10) {
            animationTimer += elapsedTime.asMicroseconds();
            if (animationTimer > 80000) {
                animationTimer = 0;
                ++frameIndex;
            }
        }
        break;

    case Sheet::dashSheet:
        animationTimer += elapsedTime.asMicroseconds();
        break;
    }
}

void Player::draw(drawableVec & gameObjects, drawableVec & gameShadows) {
    if (visible) {
        auto gunIndexOffset = [](int64_t timeout) {
            if (timeout < 1707000 && timeout > 44000) {
                return 1;
            } else {
                return 0;
            }
        };
        switch (sheetIndex) {
        case Sheet::stillDown:
            if (gun.timeout > 0) {
                gameObjects.emplace_back(
                    gun.gunSpr[4 + gunIndexOffset(gun.timeout)],
                    gun.gunSpr.getYpos() - 14, renderType, colorAmount);
            }
            gameObjects.emplace_back(walkDown[5], yPos, renderType,
                                     colorAmount);
            gameShadows.emplace_back(shadowSprite, 0.f,
                                     Rendertype::shadeDefault, 0.f);
            break;

        case Sheet::stillUp:
            gameObjects.emplace_back(walkUp[5], yPos, renderType, colorAmount);
            gameShadows.emplace_back(shadowSprite, 0.f,
                                     Rendertype::shadeDefault, 0.f);
            break;

        case Sheet::stillLeft:
            if (gun.timeout > 0) {
                gameObjects.emplace_back(
                    gun.gunSpr[2 + gunIndexOffset(gun.timeout)],
                    gun.gunSpr.getYpos() - 14, renderType, colorAmount);
            }
            gameObjects.emplace_back(walkLeft[6], yPos, renderType,
                                     colorAmount);
            gameShadows.emplace_back(shadowSprite, 0.f,
                                     Rendertype::shadeDefault, 0.f);
            break;

        case Sheet::stillRight:
            if (gun.timeout > 0) {
                gameObjects.emplace_back(
                    gun.gunSpr[gunIndexOffset(gun.timeout)],
                    gun.gunSpr.getYpos() - 14, renderType, colorAmount);
            }
            gameObjects.emplace_back(walkRight[6], yPos, renderType,
                                     colorAmount);
            gameShadows.emplace_back(shadowSprite, 0.f,
                                     Rendertype::shadeDefault, 0.f);
            break;

        case Sheet::walkDown:
            if (gun.timeout > 0) {
                gameObjects.emplace_back(
                    gun.gunSpr[4 + gunIndexOffset(gun.timeout)],
                    gun.gunSpr.getYpos() - 14, renderType, colorAmount);
            }
            gameObjects.emplace_back(
                walkDown[verticalAnimationDecoder(frameIndex)], yPos,
                renderType, colorAmount);
            gameShadows.emplace_back(shadowSprite, 0.f,
                                     Rendertype::shadeDefault, 0.f);
            break;

        case Sheet::walkUp:
            gameObjects.emplace_back(
                walkUp[verticalAnimationDecoder(frameIndex)], yPos, renderType,
                colorAmount);
            gameShadows.emplace_back(shadowSprite, 0.f,
                                     Rendertype::shadeDefault, 0.f);
            break;

        case Sheet::walkLeft:
            if (gun.timeout > 0) {
                gameObjects.emplace_back(
                    gun.gunSpr[2 + gunIndexOffset(gun.timeout)],
                    gun.gunSpr.getYpos() - 14, renderType, colorAmount);
            }
            gameObjects.emplace_back(walkLeft[frameIndex], yPos, renderType,
                                     colorAmount);
            gameShadows.emplace_back(shadowSprite, 0.f,
                                     Rendertype::shadeDefault, 0.f);
            break;

        case Sheet::walkRight:
            if (gun.timeout > 0) {
                gameObjects.emplace_back(
                    gun.gunSpr[gunIndexOffset(gun.timeout)],
                    gun.gunSpr.getYpos() - 14, renderType, colorAmount);
            }
            gameObjects.emplace_back(walkRight[frameIndex], yPos, renderType,
                                     colorAmount);
            gameShadows.emplace_back(shadowSprite, 0.f,
                                     Rendertype::shadeDefault, 0.f);
            break;

        case Sheet::deathSheet:
            gameObjects.emplace_back(deathSheet[frameIndex], yPos, renderType,
                                     colorAmount);
            break;

        case Sheet::dashSheet:
            gameObjects.emplace_back(dashSheet[frameIndex], yPos, renderType,
                                     colorAmount);
            gameShadows.emplace_back(shadowSprite, 0.f,
                                     Rendertype::shadeDefault, 0.f);
            if (state == Player::State::dashing) {
                if (animationTimer > 20000) {
                    animationTimer = 0;
                    blurs.emplace_back(&std::get<0>(gameObjects.back()), xPos,
                                       yPos);
                }
            }
            break;
        }
    }
    for (auto & element : blurs) {
        gameObjects.emplace_back(*element.getSprite(), element.yInit,
                                 Rendertype::shadeDefault, 0.f);
    }
}

void Player::updateAnimation(const sf::Time & elapsedTime, uint8_t maxIndex,
                             uint32_t count) {
    animationTimer += elapsedTime.asMicroseconds();
    if (animationTimer > count) {
        frameIndex++;
        animationTimer -= count;
    }
    if (frameIndex > maxIndex) {
        frameIndex = 0;
    }
}

void Player::setState(State _state) { state = _state; }

Player::State Player::getState() const { return state; }

Player::Health Player::getHealth() const { return health; }

void Player::activate() {
    state = State::nominal;
    sheetIndex = Sheet::stillDown;
}

void Player::reset() {
    state = State::nominal;
    invulnerable = false;
    health = 4;
    sheetIndex = Sheet::stillDown;
    frameIndex = 5;
    upPrevious = false;
    downPrevious = false;
    leftPrevious = false;
    rightPrevious = false;
}

void Player::setHealth(Health value) { health = value; }

void Player::updateGun(const sf::Time & elapsedTime, const bool shootKey,
                       EffectGroup & effects, SoundController & sounds,
                       ui::Backend & UI) {
    gun.timeout -= elapsedTime.asMicroseconds();
    if (gun.bulletTimer != 0) {
        gun.bulletTimer -= elapsedTime.asMicroseconds();
        if (gun.bulletTimer < 0) {
            gun.bulletTimer = 0;
        }
    }
    if (gun.timeout <= 0) {
        gun.timeout = 0;
    }
    if (shootKey) {
        if (gun.timeout == 0) {
            gun.timeout = 1760000;
        } else if (gun.timeout < 1671000) {
            gun.timeout = 1671000;
            if (gun.bulletTimer == 0) {
                effects.add<9>(getgResHandlerPtr()->getTexture(
                                   ResHandler::Texture::gameObjects),
                               getgResHandlerPtr()->getTexture(
                                   ResHandler::Texture::whiteGlow),
                               static_cast<int>(sheetIndex), xPos, yPos);
                if (UI.getCurrentPowerup() == Powerup::rapidFire) {
                    gun.bulletTimer = 220000;
                } else {
                    sounds.play(ResHandler::Sound::gunShot);
                    gun.bulletTimer = 440000;
                }
            }
        }
    }
}

template <size_t indx, typename F>
void checkEffectCollision(EffectGroup & effects, Player * pPlayer,
                          const F & policy) {
    for (auto & element : effects.get<indx>()) {
        if (pPlayer->getHitBox().overlapping(element.getHitBox())) {
            element.setKillFlag();
            policy();
        }
    }
}

void Player::checkEffectCollisions(EffectGroup & effects,
                                   ui::Frontend * pUiFrontend) {
    auto hitPolicy = [&]() {
        if (colorAmount == 0.f) {
            health -= 1;
            pUiFrontend->updateHealth(health);
            renderType = Rendertype::shadeGldnGt;
            colorAmount = 1.f;
            colorTimer = 0;
            util::sleep(milliseconds(40));
        }
    };
    checkEffectCollision<8>(effects, this, hitPolicy);
    checkEffectCollision<7>(effects, this, hitPolicy);
    checkEffectCollision<6>(effects, this, hitPolicy);
    checkEffectCollision<4>(effects, this, [&]() {
        health = fmin(pUiFrontend->getMaxHealth(), health + 1);
        pUiFrontend->updateHealth(health);
        renderType = Rendertype::shadeRuby;
        colorAmount = 1.f;
        colorTimer = 0;
        util::sleep(milliseconds(40));
    });
    checkEffectCollision<5>(effects, this, [&]() {
        pUiFrontend->updateScore(1);
        renderType = Rendertype::shadeElectric;
        colorAmount = 1.f;
        colorTimer = 0;
        util::sleep(milliseconds(40));
    });
}

template <typename F, typename T>
void checkEnemyCollision(const std::vector<T> & enemyGroup, Player * pPlayer,
                         const F & policy) {
    for (auto & enemy : enemyGroup) {
        if (pPlayer->getHitBox().overlapping(enemy.getHitBox())) {
            policy();
        }
    }
}

template <typename F>
void checkEnemyCollision(const std::vector<Dasher> & dashers, Player * pPlayer,
                         const F & policy) {
    for (auto & enemy : dashers) {
        if (pPlayer->getHitBox().overlapping(enemy.getHitBox()) &&
            enemy.getState() != Dasher::State::dead &&
            enemy.getState() != Dasher::State::dying) {
            policy();
        }
    }
}

void Player::checkEnemyCollisions(enemyController & enemies,
                                  ui::Frontend * pUiFrontend) {
    auto collisionPolicy = [&]() {
        if (colorAmount == 0.f) {
            health -= 1;
            pUiFrontend->updateHealth(health);
            renderType = Rendertype::shadeGldnGt;
            colorAmount = 1.f;
            colorTimer = 0;
            util::sleep(milliseconds(40));
        }
    };
    checkEnemyCollision(enemies.getCritters(), this, collisionPolicy);
    checkEnemyCollision(enemies.getDashers(), this, collisionPolicy);
    // TODO: why is this buggy? checkEnemyCollision(enemies.getTurrets(), this,
    // collisionPolicy);
    checkEnemyCollision(enemies.getScoots(), this, collisionPolicy);
}

const Player::HBox & Player::getHitBox() const { return hitBox; }

void Player::updateColor(const sf::Time & elapsedTime) {
    if (colorAmount > 0.f) {
        colorTimer += elapsedTime.asMilliseconds();
        if (colorTimer > 40) {
            colorTimer -= 40;
            colorAmount -= 0.1f;
        }
    } else {
        colorAmount = 0.f;
        renderType = Rendertype::shadeDefault;
    }
}

const Player::Weapon & Player::getGun() const { return gun; }

sf::Vector2f Player::requestFuturePos(const uint32_t uTime) const {
    sf::Vector2f futurePos;
    futurePos.x = uTime * (-lSpeed + rSpeed) * MOVEMENT_RATE_CONSTANT + xPos;
    futurePos.y = uTime * (-uSpeed + dSpeed) * MOVEMENT_RATE_CONSTANT + yPos;
    return futurePos;
}

sf::Vector2f Player::getPosition() const { return sf::Vector2f(xPos, yPos); }

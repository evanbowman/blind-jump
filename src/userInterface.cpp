#include "userInterface.hpp"
#include "Game.hpp"
#include "player.hpp"
#include <cmath>

ui::Backend::Backend()
    : state(State::closed), powerupBubbleState(PowerupBubbleState::dormant),
      menuItemSelected(0), menuItemTarget(0), timer(0), timerAlt(0),
      powerupTimer(0), powerupBubbleTimer(0), dispPowerupBar(false),
      blurAmount(0.f), desaturateAmount(0.f) {}

bool ui::Backend::isOpen() const { return state != State::closed; }

ui::Backend::State ui::Backend::getState() const { return state; }

static const char MENU_ITEM_DESEL_INTEN = 180;

void ui::Backend::draw(sf::RenderWindow & window, ui::Frontend & uIFrontEnd) {
    switch (state) {
    case State::deathScreenEntry: {
        uint8_t textAlpha = desaturateAmount * 255 + 38.25f;
        uIFrontEnd.drawDeathText(static_cast<unsigned char>(textAlpha), window);
    } break;

    case State::menuScreenEntry:
        uIFrontEnd.setTextAlpha(255 * blurAmount,
                                ui::Frontend::Text::resumeText);
        uIFrontEnd.setTextAlpha(140 * blurAmount, ui::Frontend::Text::quitText);
        uIFrontEnd.setTextOffset(0, -0.01 * blurAmount,
                                 ui::Frontend::Text::resumeText);
        uIFrontEnd.setTextOffset(0, -0.01 * blurAmount,
                                 ui::Frontend::Text::quitText);
        break;

    case State::menuScreenExit:
        uIFrontEnd.setTextAlpha(255 * blurAmount,
                                ui::Frontend::Text::resumeText);
        uIFrontEnd.setTextAlpha(140 * blurAmount, ui::Frontend::Text::quitText);
        uIFrontEnd.setTextOffset(0, -0.01 * blurAmount,
                                 ui::Frontend::Text::resumeText);
        uIFrontEnd.setTextOffset(0, -0.01 * blurAmount,
                                 ui::Frontend::Text::quitText);
        break;

    case State::deathScreen:
        uIFrontEnd.drawDeathText(255, window);
        break;

    case State::deathScreenExit: {
        uint8_t textAlpha = Easing::easeOut<3>(timer, 300) * 255;
        if (textAlpha > 0) {
            uIFrontEnd.drawDeathText(textAlpha, window);
        }
    } break;

    default:
        break;
    }
    switch (powerupBubbleState) {
    case PowerupBubbleState::opening: {
        static const int transitionTime = 500000;
        const float deg =
            math::smoothstep(0, transitionTime, powerupBubbleTimer);
        uIFrontEnd.setBubbleAlpha(deg * 255);
        uIFrontEnd.setBubbleRadius(deg * 0.06f);
        uIFrontEnd.setTextAlpha(deg * 255, ui::Frontend::Text::powerupText);
        uIFrontEnd.setTextOffset(0, -0.001f * deg,
                                 ui::Frontend::Text::powerupText);
    } break;

    case PowerupBubbleState::closing: {
        static const int transitionTime = 300000;
        const float deg =
            math::smootherstep(0, transitionTime, powerupBubbleTimer);
        uIFrontEnd.setBubbleAlpha(255 - deg * 255);
        uIFrontEnd.setBubbleRadius(0.06f - deg * 0.06f);
        uIFrontEnd.setTextAlpha(255 - deg * 255,
                                ui::Frontend::Text::powerupText);
    } break;

    default:
        break;
    }
}

void ui::Backend::setPowerup(Powerup _powerup) {
    powerup = _powerup;
    powerupBubbleState = PowerupBubbleState::triggered;
}

Powerup ui::Backend::getCurrentPowerup() const { return powerup; }

ui::Backend::PowerupBubbleState ui::Backend::getPowerupBubbleState() const {
    return powerupBubbleState;
}

void ui::Backend::update(Game * pGame, const sf::Time & elapsedTime) {
    InputController & input = pGame->getInputController();
    Frontend & uIFrontEnd = pGame->getUIFrontend();
    Player & player = pGame->getPlayer();
    bool action = input.actionPressed();
    bool up = input.upPressed();
    bool down = input.downPressed();
    bool pause = input.pausePressed();
    SoundController & sounds = pGame->getSounds();
    switch (state) {
    case State::closed:
        if (dispPowerupBar) {
            static const int64_t powerupTimerCeil = 10000000;
            powerupTimer += elapsedTime.asMicroseconds();
            float barWidth = Easing::easeOut<1>(powerupTimer, powerupTimerCeil);
            uIFrontEnd.setBarWidth(barWidth);
            if (powerupTimer > powerupTimerCeil) {
                dispPowerupBar = false;
                pGame->getHelperGroup().clear();
                powerup = Powerup::nil;
            }
        }
        if (pause) {
            state = State::menuScreenEntry;
            player.setState(Player::State::deactivated);
            uIFrontEnd.setTextAlpha(0, ui::Frontend::Text::waypointText);
            uIFrontEnd.setTextAlpha(0, ui::Frontend::Text::healthNumText);
            uIFrontEnd.setTextAlpha(0, ui::Frontend::Text::scoreText);
            uIFrontEnd.setTextAlpha(0, ui::Frontend::Text::heart);
            uIFrontEnd.setTextAlpha(0, ui::Frontend::Text::coin);
        }
        break;

    case State::menuScreenEntry:
        timer += elapsedTime.asMilliseconds();
        blurAmount = math::smootherstep(0.f, 280, timer);
        if (blurAmount == 1.f) {
            state = State::menuScreen;
            sounds.pause(SoundController::Sound);
            uIFrontEnd.setTextAlpha(255, ui::Frontend::Text::resumeText);
            uIFrontEnd.setTextAlpha(140, ui::Frontend::Text::quitText);
        }
        break;

    case State::menuScreen:
        if (pause) {
            timer = 0;
            menuItemSelected = 0;
            sounds.unpause(SoundController::Sound);
            state = State::menuScreenExit;
        } else if (up) {
            if (menuItemSelected == 1) {
                menuItemTarget = 0;
                state = State::menuSelectionTransition;
                timer = 0;
            }
        } else if (down) {
            if (menuItemSelected == 0) {
                menuItemTarget = 1;
                state = State::menuSelectionTransition;
                timer = 0;
            }
        } else if (action) {
            switch (menuItemSelected) {
            case 0:
                menuItemSelected = 0;
                sounds.unpause(SoundController::Sound);
                state = State::menuScreenExit;
                timer = 0;
                break;

            case 1:
                throw ShutdownSignal();
                break;
            }
        }
        break;

    case State::menuSelectionTransition:
        if ((timer += elapsedTime.asMilliseconds()) < 200) {
            const float transition = math::smoothstep(0, 200, timer);
            if (menuItemTarget == 0) {
                uIFrontEnd.setTextAlpha(140 + transition * 115,
                                        ui::Frontend::Text::resumeText);
                uIFrontEnd.setTextAlpha(255 - transition * 115,
                                        ui::Frontend::Text::quitText);
            } else {
                uIFrontEnd.setTextAlpha(255 - transition * 115,
                                        ui::Frontend::Text::resumeText);
                uIFrontEnd.setTextAlpha(140 + transition * 115,
                                        ui::Frontend::Text::quitText);
            }
        } else {
            menuItemSelected = menuItemTarget;
            state = State::menuScreen;
        }
        break;

    case State::menuScreenExit:
        timer += elapsedTime.asMilliseconds();
        blurAmount = 1 - math::smoothstep(0, 280, timer);
        if (blurAmount == 0.f) {
            state = State::closed;
            timer = 0;
            player.activate();
            uIFrontEnd.setTextAlpha(0, ui::Frontend::Text::resumeText);
            uIFrontEnd.setTextAlpha(0, ui::Frontend::Text::quitText);
        }
        break;

    case State::deathScreenEntry:
        timer += elapsedTime.asMilliseconds();
        if (timer > 20) {
            timer -= 20;
            desaturateAmount += 0.01f;
        }
        if (desaturateAmount > 0.85f) {
            desaturateAmount = 0.85f;
            state = State::deathScreen;
            timerAlt = 0;
        }
        break;

    case State::deathScreen:
        timer += elapsedTime.asMilliseconds();
        timerAlt += elapsedTime.asMilliseconds();
        if (timer > 20) {
            timer -= 20;
            if (timerAlt < 1500) {
                // TODO: This previously zoomed the window... re-implement?
            } else {
                timer = 0;
                state = State::deathScreenExit;
            }
        }
        break;

    case State::deathScreenExit:
        timer += elapsedTime.asMilliseconds();
        blurAmount = Easing::easeIn<3>(timer, 300);
        if (timer >= 300) {
            timer = 0;
            blurAmount = 1.f;
            state = State::statsScreen;
        }
        break;

    case State::statsScreen:
        if (action) {
            state = State::complete;
        }
        break;

    case State::complete:
        break;
    }
    switch (powerupBubbleState) {
    case PowerupBubbleState::triggered:
        dispPowerupBar = false;
        powerupTimer = 0;
        pGame->getHelperGroup().clear();
        uIFrontEnd.addPowerup(powerup);
        powerupBubbleState = PowerupBubbleState::opening;
        break;

    case PowerupBubbleState::opening:
        powerupBubbleTimer += elapsedTime.asMicroseconds();
        {
            static const int transitionTime = 500000;
            if (powerupBubbleTimer > transitionTime) {
                powerupBubbleTimer = 0;
                uIFrontEnd.setBubbleAlpha(255);
                powerupBubbleState = PowerupBubbleState::open;
            }
        }
        break;

    case PowerupBubbleState::open:
        powerupBubbleTimer += elapsedTime.asMicroseconds();
        {
            static const int transitionTime = 1200000;
            if (powerupBubbleTimer > transitionTime) {
                powerupBubbleTimer = 0;
                powerupBubbleState = PowerupBubbleState::closing;
            }
        }
        break;

    case PowerupBubbleState::closing:
        powerupBubbleTimer += elapsedTime.asMicroseconds();
        {
            static const int transitionTime = 300000;
            if (powerupBubbleTimer > transitionTime) {
                powerupBubbleTimer = 0;
                powerupBubbleState = PowerupBubbleState::closed;
            }
        }
        break;

    case PowerupBubbleState::closed:
        uIFrontEnd.setBubbleAlpha(0);
        switch (powerup) {
        case Powerup::nil:
            break;

        case Powerup::goldHeart:
            uIFrontEnd.updateMaxHealth(uIFrontEnd.getMaxHealth() + 1);
            uIFrontEnd.updateHealth(uIFrontEnd.getHealth() + 1);
            dispPowerupBar = false;
            powerupTimer = 0;
            break;

        case Powerup::rapidFire:
            dispPowerupBar = true;
            powerupTimer = 0;
            break;

        case Powerup::laika: {
            dispPowerupBar = true;
            powerupTimer = 0;
            HelperGroup & hg = pGame->getHelperGroup();
            const sf::Vector2f playerPos = pGame->getPlayer().getPosition();
            hg.add<HelperRef::Laika>(playerPos.x, playerPos.y + 32,
                                     getgResHandlerPtr()->getTexture(
                                         ResHandler::Texture::gameObjects),
                                     pGame->getTileController().mapArray);
        } break;
        }
        powerupBubbleState = PowerupBubbleState::dormant;
        break;

    case PowerupBubbleState::dormant:
        break;
    }
}

void ui::Backend::dispDeathSeq() {
    if (state == ui::Backend::State::closed) {
        timer = 0;
        state = ui::Backend::State::deathScreenEntry;
    }
}

bool ui::Backend::isComplete() { return state == State::complete; }

float ui::Backend::getBlurAmount() { return blurAmount; }

void ui::Backend::reset() {
    state = State::closed;
    desaturateAmount = 0.f;
    blurAmount = 0.f;
    timer = 0;
    powerup = Powerup::nil;
    dispPowerupBar = false;
    powerupTimer = 0;
}

float ui::Backend::getDesaturateAmount() { return desaturateAmount; }

bool ui::Backend::blurEnabled() { return blurAmount != 0.f; }

bool ui::Backend::desaturateEnabled() { return desaturateAmount > 0.f; }

void ui::PowerupBubble::init(float scale) {
    bubble.setOutlineThickness(0.0065f * scale);
    bubble.setFillColor(sf::Color(40, 48, 81, 170));
    bubble.setOutlineColor(sf::Color::White);
    bubble.setPointCount(60);
    powerupSheet.setTexture(
        getgResHandlerPtr()->getTexture(ResHandler::Texture::powerupSheet));
}

void ui::PowerupBubble::setFrame(size_t idx) { powerupSheet[idx]; }

void ui::PowerupBubble::setAlpha(uint8_t alpha) {
    bubble.setFillColor(sf::Color(40, 48, 81, alpha * 0.7));
    bubble.setOutlineColor(sf::Color(255, 255, 255, alpha));
    powerupSheet.setColor(sf::Color(255, 255, 255, alpha));
}

const Sprite & ui::PowerupBubble::getSprite() {
    return powerupSheet.getSprite();
}

void ui::PowerupBubble::setRadius(float rad, float scale) {
    bubble.setRadius(rad * scale);
    const float offset = bubble.getRadius();
    bubble.setOrigin(offset, offset);
    const float sprScale = rad * scale * 0.035f;
    powerupSheet.setScale(sprScale, sprScale);
    const sf::FloatRect size = powerupSheet.getSize();
    powerupSheet.setOrigin(size.width / 2.f, size.height / 2.f);
}

void ui::PowerupBubble::setPosition(float xpos, float ypos) {
    bubble.setPosition(xpos, ypos);
    powerupSheet.setPosition(xpos, ypos);
}

sf::Vector2f ui::PowerupBubble::getPosition() { return bubble.getPosition(); }

float ui::PowerupBubble::getRadius() { return bubble.getRadius(); }

const sf::CircleShape & ui::PowerupBubble::getShape() const { return bubble; }

#define HEALTH_TEXT_FADE_SECONDS 3
#define SCORE_TEXT_FADE_SECONDS 3
#define WAYPOINT_TEXT_FADE_SECONDS 3

ui::Frontend::Frontend(sf::View fontView, float x, float y)
    : healthModified(true), scoreModified(true), powerupAdded(Powerup::nil),
      barWidth(0.f) {
    // Store the view to use when drawing fonts
    this->fontView = fontView;
    windowCenterX = x;
    windowCenterY = y;
    maxHealth = 4;
    health = 4;
    score = 0;
    const sf::Vector2f viewSize = fontView.getSize();
    if (viewSize.y < viewSize.x) {
        scale = viewSize.y;
    } else {
        scale = viewSize.x;
    }
    powerupBubble.init(scale);
    powerupBubble.setRadius(0.065f, scale);
    powerupBubble.setPosition(viewSize.x / 2.f, viewSize.y / 4.5f);
    powerupBubble.setAlpha(0);
    heart.setPointCount(20);
    heart.setPoint(0, sf::Vector2f(38, 72));
    heart.setPoint(1, sf::Vector2f(8, 44));
    heart.setPoint(2, sf::Vector2f(4, 38));
    heart.setPoint(3, sf::Vector2f(0, 30));
    heart.setPoint(4, sf::Vector2f(0, 20));
    heart.setPoint(5, sf::Vector2f(2, 8));
    heart.setPoint(6, sf::Vector2f(8, 2));
    heart.setPoint(7, sf::Vector2f(18, 0));
    heart.setPoint(8, sf::Vector2f(24, 0));
    heart.setPoint(9, sf::Vector2f(32, 4));
    heart.setPoint(10, sf::Vector2f(38, 10));
    heart.setPoint(11, sf::Vector2f(44, 4));
    heart.setPoint(12, sf::Vector2f(52, 0));
    heart.setPoint(13, sf::Vector2f(58, 0));
    heart.setPoint(14, sf::Vector2f(68, 2));
    heart.setPoint(15, sf::Vector2f(74, 8));
    heart.setPoint(16, sf::Vector2f(76, 20));
    heart.setPoint(17, sf::Vector2f(76, 30));
    heart.setPoint(18, sf::Vector2f(72, 38));
    heart.setPoint(19, sf::Vector2f(68, 44));
    heart.setScale(0.0005f * scale, 0.0005f * scale);
    heart.setOrigin(heart.getLocalBounds().width / 2,
                    heart.getLocalBounds().height / 2);
    coin.setFillColor(sf::Color::White);
    coin.setPointCount(20);
    coin.setRadius(0.018f * scale);
    coin.setOrigin(coin.getLocalBounds().width / 2,
                   coin.getLocalBounds().height / 2);
    const sf::Font & cornerstone =
        getgResHandlerPtr()->getFont(ResHandler::Font::cornerstone);

    auto initText = [&cornerstone](sf::Text & text, const std::string string,
                                   float size) {
        text.setFont(cornerstone);
        text.setCharacterSize(size);
        text.setString(string);
    };
    initText(waypointText, std::string("CRASH SITE"), 0.055f * scale);
    waypointText.setPosition(16, 0);
    waypointText.setFillColor(sf::Color(255, 255, 255, 60));

    initText(scoreText, std::string("0: "), 0.032f * scale);

    healthNumText.setString(std::to_string(4) + " / " +
                            std::to_string(static_cast<int>(maxHealth)) + ": ");
    healthNumText.setCharacterSize(0.032 * scale);
    healthNumText.setFont(cornerstone);

    initText(resumeText, std::string("RESUME"), 0.085f * scale);
    resumeText.setFillColor(sf::Color(255, 255, 255, 0));

    powerupText.setFillColor(sf::Color(255, 255, 255, 0));
    powerupText.setFont(cornerstone);
    powerupText.setCharacterSize(0.065 * scale);

    initText(quitText, std::string("QUIT"), 0.085 * scale);
    quitText.setFillColor(sf::Color(255, 255, 255, 0));

    initText(titleText, std::string("BLIND JUMP"), 0.115f * scale);
    titleText.setPosition(viewSize.x / 2 - titleText.getLocalBounds().width / 2,
                          viewSize.y / 8 -
                              titleText.getLocalBounds().height / 2);
    titleText.setFillColor(sf::Color(255, 255, 255, 0));

    initText(deathText, std::string("YOU DIED"), 0.115 * scale);
    deathText.setFillColor(sf::Color(231, 26, 83));
    deathText.setPosition(viewSize.x / 2 - deathText.getLocalBounds().width / 2,
                          viewSize.y / 12 -
                              deathText.getLocalBounds().height / 2);

    const sf::Vector2f barPosition(0.f, viewSize.y - viewSize.y * 0.008f);
    powerupBarFront.setPosition(barPosition);
    powerupBarBack.setPosition(barPosition);
    powerupBarBack.setSize(sf::Vector2f(viewSize.x, viewSize.y * 0.008f));
    powerupBarBack.setFillColor(sf::Color(160, 160, 160, 255));
    powerupBarFront.setFillColor(sf::Color::White);
}

void ui::Frontend::setBubbleAlpha(uint8_t alpha) {
    powerupBubble.setAlpha(alpha);
}

void ui::Frontend::setBubbleRadius(float rad) {
    powerupBubble.setRadius(rad, scale);
}

void ui::Frontend::setTextOffset(float xOffset, float yOffset,
                                 ui::Frontend::Text text) {
    float scale;
    const sf::Vector2f viewSize = fontView.getSize();
    if (viewSize.y < viewSize.x) {
        scale = viewSize.y;
    } else {
        scale = viewSize.x;
    }
    switch (text) {
    case Text::resumeText:
        resumeText.setPosition(xOffset * scale + viewSize.x / 2 -
                                   resumeText.getLocalBounds().width / 2,
                               viewSize.y / 2.8f -
                                   resumeText.getLocalBounds().height / 2 +
                                   yOffset * scale);
        break;

    case Text::quitText:
        quitText.setPosition(xOffset * scale + viewSize.x / 2 -
                                 quitText.getLocalBounds().width / 2,
                             resumeText.getPosition().y +
                                 quitText.getLocalBounds().height * 2 +
                                 yOffset * scale);
        break;

    case Text::powerupText:
        powerupText.setPosition(xOffset * scale + viewSize.x / 2 -
                                    powerupText.getLocalBounds().width / 2,
                                yOffset * scale +
                                    powerupBubble.getPosition().y -
                                    powerupBubble.getRadius() -
                                    powerupText.getLocalBounds().height * 1.8f);
        break;

    default:
        // TODO: handle other cases...
        break;
    }
}

void ui::Frontend::setTextAlpha(uint8_t alpha, ui::Frontend::Text text) {
    switch (text) {
    case Text::resumeText:
        resumeText.setFillColor(sf::Color(255, 255, 255, alpha));
        break;

    case Text::quitText:
        quitText.setFillColor(sf::Color(255, 255, 255, alpha));
        break;

    case Text::healthNumText:
        healthNumText.setFillColor(sf::Color(255, 255, 255, alpha));
        break;

    case Text::scoreText:
        scoreText.setFillColor(sf::Color(255, 255, 255, alpha));
        break;

    case Text::waypointText:
        waypointText.setFillColor(sf::Color(255, 255, 255, alpha));
        break;

    case Text::heart:
        heart.setFillColor(sf::Color(255, 255, 255, alpha));
        break;

    case Text::coin:
        coin.setFillColor(sf::Color(255, 255, 255, alpha));
        break;

    case Text::powerupText:
        powerupText.setFillColor(sf::Color(255, 255, 255, alpha));
        break;
    }
}

void ui::Frontend::reset() {
    score = 0;
    barWidth = 0;
}

void ui::Frontend::addPowerup(Powerup powerup) { powerupAdded = powerup; }

void ui::Frontend::setWaypointText(const int level) {
    heart.setPosition(fontView.getSize().x - heart.getLocalBounds().width / 2,
                      heart.getLocalBounds().height / 1.8);
    coin.setPosition(heart.getPosition().x,
                     heart.getPosition().y +
                         coin.getLocalBounds().height * 1.25);
    coin.setFillColor(sf::Color(255, 255, 255, 60));
    if (health != 1) {
        healthNumText.setFillColor(sf::Color(255, 255, 255, 60));
        heart.setFillColor(sf::Color(255, 255, 255, 60));
    }
    if (level != 0) {
        std::string str = "WAYPOINT-";
        str += std::to_string(level);
        waypointText.setString(str);
    } else {
        static const std::string str = "CRASH SITE";
        waypointText.setString(str);
    }
    scoreText.setFillColor(sf::Color(255, 255, 255, 60));
    waypointText.setFillColor(sf::Color::White);
    wpTextDisplayTimer.restart();
    if (level != 0) {
        if (health != 1) {
            healthDisplayTimer.restart();
        }
        scoreDisplayTimer.restart();
    }
}

int ui::Frontend::getScore() { return score; }

void ui::Frontend::draw(sf::RenderWindow & window) {
    // Set the correct view, so not to blur the fonts
    window.setView(fontView);
    if (barWidth > 0) {
        powerupBarFront.setSize(sf::Vector2f(fontView.getSize().x * barWidth,
                                             fontView.getSize().y * 0.01f));
        window.draw(powerupBarBack, sf::BlendMultiply);
        window.draw(powerupBarFront);
    }
    if (healthModified) {
        healthModified = false;
        healthNumText.setString(
            std::to_string(static_cast<int>(health)) + " / " +
            std::to_string(static_cast<int>(maxHealth)) + " :");
        healthNumText.setPosition(
            fontView.getSize().x - healthNumText.getLocalBounds().width -
                fontView.getSize().x * 0.015 - heart.getLocalBounds().width,
            healthNumText.getLocalBounds().height);
    }
    if (scoreModified) {
        scoreModified = false;
        scoreText.setString(std::to_string(score) + " :");
        scoreText.setPosition(
            fontView.getSize().x - scoreText.getLocalBounds().width -
                fontView.getSize().x * 0.015 - heart.getLocalBounds().width,
            scoreText.getLocalBounds().height * 3);
    }
    switch (powerupAdded) {
    case Powerup::nil:
        break;

    case Powerup::goldHeart:
        powerupBubble.setFrame(static_cast<int>(powerupAdded) - 1);
        powerupAdded = Powerup::nil;
        powerupText.setString(std::string("HEALTH UP"));
        break;

    case Powerup::rapidFire:
        powerupBubble.setFrame(static_cast<int>(powerupAdded) - 1);
        powerupAdded = Powerup::nil;
        powerupText.setString(std::string("SUPERCHARGER"));
        break;

    case Powerup::laika:
        powerupBubble.setFrame(static_cast<int>(powerupAdded) - 1);
        powerupAdded = Powerup::nil;
        powerupText.setString(std::string("LAIKA"));
        break;
    }
    // Slowly fade out the  waypoint text
    sf::Color c = waypointText.getFillColor();
    if (c.a > 68) {
        if (wpTextDisplayTimer.getElapsedTime().asSeconds() >
            WAYPOINT_TEXT_FADE_SECONDS) {
            c.a -= 4;
            waypointText.setFillColor(c);
        }
    }
    window.draw(waypointText);
    if (health != 1) {
        c = healthNumText.getFillColor();
        if (c.a > 68) {
            if (healthDisplayTimer.getElapsedTime().asSeconds() >
                HEALTH_TEXT_FADE_SECONDS) {
                c.a -= 4;
                healthNumText.setFillColor(c);
                heart.setFillColor(c);
                heart.setOutlineColor(c);
            }
        }
    }
    window.draw(healthNumText);
    window.draw(heart);
    c = scoreText.getFillColor();
    if (c.a > 68) {
        if (scoreDisplayTimer.getElapsedTime().asSeconds() >
            SCORE_TEXT_FADE_SECONDS) {
            c.a -= 4;
            scoreText.setFillColor(c);
            coin.setFillColor(c);
        }
    }
    window.draw(scoreText);
    window.draw(coin);
    c = resumeText.getFillColor();
    if (c.a > 0) {
        window.draw(resumeText);
    }
    c = quitText.getFillColor();
    if (c.a > 0) {
        window.draw(quitText);
    }
    c = powerupBubble.getShape().getOutlineColor();
    if (c.a > 0) {
        window.draw(powerupBubble.getShape());
        window.draw(powerupBubble.getSprite());
    }
    c = powerupText.getFillColor();
    if (c.a > 0) {
        window.draw(powerupText);
    }
}

void ui::Frontend::resetWPText() {
    waypointText.setFillColor(sf::Color::White);
    wpTextDisplayTimer.restart();
}

void ui::Frontend::resetSCText() {
    scoreText.setFillColor(sf::Color::White);
    coin.setFillColor(sf::Color::White);
    scoreDisplayTimer.restart();
}

void ui::Frontend::updateScore(int offset) {
    score += offset;
    resetSCText();
    scoreModified = true;
}

void ui::Frontend::resetHPText() {
    healthNumText.setFillColor(sf::Color::White);
    heart.setFillColor(sf::Color::White);
    heart.setOutlineColor(sf::Color::White);
    healthDisplayTimer.restart();
}

void ui::Frontend::drawTitle(unsigned char alpha, sf::RenderWindow & window) {
    titleText.setFillColor(sf::Color(255, 255, 255, alpha));
    window.setView(fontView);
    window.draw(titleText);
}

void ui::Frontend::drawDeathText(unsigned char alpha,
                                 sf::RenderWindow & window) {
    deathText.setFillColor(sf::Color(colors::Ruby::r * 255,
                                     colors::Ruby::g * 255,
                                     colors::Ruby::b * 255, alpha));
    window.setView(fontView);
    window.draw(deathText);
}

sf::Text * ui::Frontend::getTitle() { return &titleText; }

void ui::Frontend::updateHealth(char _health) {
    health = _health;
    // Can't update the actual text from here, since it needs to happen on the
    // main thread.
    // Instead mark it as modifed and handle it later
    healthModified = true;
    resetHPText();
}

void ui::Frontend::updateMaxHealth(char _maxHealth) {
    maxHealth = _maxHealth;
    healthModified = true;
    resetHPText();
}

char ui::Frontend::getMaxHealth() const { return maxHealth; }

char ui::Frontend::getHealth() const { return health; }

sf::Text * ui::Frontend::getDeathText() { return &deathText; }

void ui::Frontend::setBarWidth(float _barWidth) { barWidth = _barWidth; }

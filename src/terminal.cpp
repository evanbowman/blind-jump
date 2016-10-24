#include "terminal.hpp"

Terminal::Terminal(const float _xInit, const float _yInit, const sf::Texture & mainTxtr, const uint8_t tile)
    : Detail(_xInit + rng::random<4, -2>(), _yInit - rng::random<2, 1>()),
      animationTimer(0),
      stateTimer(0),
      frameIndex(0),
      state(State::dormant),
      screenSheet(mainTxtr),
      mainSprite(mainTxtr),
      shadow(mainTxtr)
{
    shadow.setTextureRect(sf::IntRect(0, 159, 21, 12));
    if (tile == 3 || tile == 4) {
        mainSprite.setTextureRect(sf::IntRect(0, 132, 21, 27));
    } else {
        mainSprite.setTextureRect(sf::IntRect(21, 143, 21, 27));
    }
    mainSprite.setPosition(position);
    screenSheet.setPosition(position.x + 1, position.y + 2);
    screenSheet.setColor(sf::Color::Transparent);
    shadow.setPosition(position.x, position.y + 20);
}

const sf::Sprite & Terminal::getSprite() const {
    return mainSprite;
}

const sf::Sprite & Terminal::getShadow() const {
    return shadow;
}

const sf::Sprite & Terminal::getScreen() const {
    return screenSheet[frameIndex];
}

void Terminal::setState(const Terminal::State _state) {
    state = _state;
}

const Terminal::State Terminal::getState() const {
    return state;
}

void Terminal::update(const sf::Time & elapsedTime) {
    animationTimer += elapsedTime.asMicroseconds();
    if (state != State::dormant) {
        static const int FLICKER_FREQUENCY = 30000;
        if (animationTimer > FLICKER_FREQUENCY) {
            animationTimer -= FLICKER_FREQUENCY;
            frameIndex ^= 1;
        }
    }
    switch (state) {
    case State::dormant:
        break;
        
    case State::wakeup:
        {
            static const int WAKEUP_USECS = 150000;
            stateTimer += elapsedTime.asMicroseconds();
            const uint8_t alpha = math::smootherstep(0.f, WAKEUP_USECS, stateTimer) * 255;
            screenSheet.setColor(sf::Color(255, 255, 255, alpha));
            if (stateTimer > WAKEUP_USECS) {
                state = State::awake;
                stateTimer = 0;
            }
        }
        break;
        
    case State::awake:
        break;
        
    case State::poweroff:
        {
            static const int POWEROFF_USECS = 400000;
            stateTimer += elapsedTime.asMicroseconds();
            const uint8_t alpha = (1 - math::smoothstep(0.f, POWEROFF_USECS, stateTimer)) * 255;
            screenSheet.setColor(sf::Color(255, 255, 255, alpha));
            if (stateTimer > POWEROFF_USECS) {
                state = State::dormant;
                stateTimer = 0;
            }
        }
        break;
    }
}

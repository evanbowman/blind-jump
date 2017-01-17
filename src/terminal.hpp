#pragma once

#include "Drawable.hpp"
#include "math.hpp"
#include "rng.hpp"
#include "spriteSheet.hpp"

struct DrawScreen {
    using value_type = int;
    template <typename CallerType> void run(CallerType & ct, GfxContext & gfx) {
        gfx.faces.emplace_back(ct.getScreen(),
                               ct.getPosition().y - CallerType::drawOffset + 1,
                               Rendertype::shadeNone, 0.f);
    }
};

template <typename DrawPolicy>
class _Terminal : public Drawable<_Terminal<DrawPolicy>, DrawPolicy>,
                  public Object {
public:
    static const int drawOffset = -10;
    enum class State { dormant, wakeup, awake, poweroff };
    _Terminal(const float _xInit, const float _yInit,
              const sf::Texture & mainTxtr, const uint8_t tile)
        : Object(_xInit + rng::random<4, -2>(), _yInit - rng::random<2, 1>()),
          animationTimer(0), stateTimer(0), frameIndex(0),
          state(State::dormant), screenSheet(mainTxtr), mainSprite(mainTxtr),
          shadow(mainTxtr) {
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
    const sf::Sprite & getSprite() const { return mainSprite; }
    const sf::Sprite & getShadow() const { return shadow; }
    const sf::Sprite & getScreen() const { return screenSheet[frameIndex]; }
    template <typename Game>
    void update(const sf::Time & elapsedTime, Game * pGame) {
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

        case State::wakeup: {
            static const int WAKEUP_USECS = 150000;
            stateTimer += elapsedTime.asMicroseconds();
            const uint8_t alpha =
                math::smootherstep(0.f, WAKEUP_USECS, stateTimer) * 255;
            screenSheet.setColor(sf::Color(255, 255, 255, alpha));
            if (stateTimer > WAKEUP_USECS) {
                state = State::awake;
                stateTimer = 0;
            }
        } break;

        case State::awake:
            break;

        case State::poweroff: {
            static const int POWEROFF_USECS = 400000;
            stateTimer += elapsedTime.asMicroseconds();
            const uint8_t alpha =
                (1 - math::smoothstep(0.f, POWEROFF_USECS, stateTimer)) * 255;
            screenSheet.setColor(sf::Color(255, 255, 255, alpha));
            if (stateTimer > POWEROFF_USECS) {
                state = State::dormant;
                stateTimer = 0;
            }
        } break;
        }
    }
    void setState(const _Terminal::State _state) { state = _state; }
    const State getState() const { return state; }

private:
    int64_t animationTimer;
    int64_t stateTimer;
    uint8_t frameIndex;
    State state;
    mutable SpriteSheet<21, 132, 19, 11> screenSheet;
    sf::Sprite mainSprite;
    sf::Sprite shadow;
};

#pragma once

#include "inputController.hpp"
#include "math.hpp"
#include "util.hpp"
#include <SFML/Graphics.hpp>

inline void dispIntroSequence(sf::RenderWindow & window,
                              InputController & input) {
    const sf::Font & cornerstone =
        getgResHandlerPtr()->getFont(ResHandler::Font::cornerstone);
    sf::Text introText("A Game by Evan Bowman", cornerstone);
    const sf::Vector2u windowSize = window.getSize();
    int scale;
    if (windowSize.y < windowSize.x) {
        scale = windowSize.y;
    } else {
        scale = windowSize.x;
    }
    introText.setCharacterSize(0.048f * scale);
    introText.setPosition(
        windowSize.x / 2.f - introText.getLocalBounds().width / 2.f,
        windowSize.y / 2.f - introText.getLocalBounds().height / 2.f);
    introText.setFillColor(sf::Color::Transparent);
    sf::Clock introSeqClock;
    uint32_t elapsedTime = 0;
    enum class State { dormant, textIn, pause1, textOut, pause2 };
    State state = State::dormant;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                throw ShutdownSignal();
                break;

            default:
                input.recordEvent(event);
                break;
            }
        }
        uint32_t timeDelta = introSeqClock.restart().asMicroseconds();
        if (util::isAsleep) {
            timeDelta = introSeqClock.restart().asMicroseconds();
            util::isAsleep = false;
        }
        elapsedTime += timeDelta;
        if (!window.hasFocus()) {
            util::sleep(milliseconds(200));
        }
        switch (state) {
        case State::dormant:
            if (elapsedTime > 300000) {
                elapsedTime = 0;
                state = State::textIn;
            }
            break;

        case State::textIn:
            if (elapsedTime > 300000) {
                elapsedTime = 0;
                state = State::pause1;
            } else {
                const uint8_t alpha =
                    math::smoothstep(0, 300000, elapsedTime) * 255;
                introText.setFillColor(sf::Color(255, 255, 255, alpha));
            }
            break;

        case State::pause1:
            if (elapsedTime > 2100000) {
                elapsedTime = 0;
                state = State::textOut;
            }
            break;

        case State::textOut:
            if (elapsedTime > 500000) {
                elapsedTime = 0;
                state = State::pause2;
            } else {
                const uint8_t alpha =
                    (1 - math::smoothstep(0, 400000, elapsedTime)) * 255;
                introText.setFillColor(sf::Color(255, 255, 255, alpha));
            }
            break;

        case State::pause2:
            if (elapsedTime > 200000) {
                return;
            }
        }
        window.clear(sf::Color::Black);
        window.draw(introText);
        window.display();
    }
}

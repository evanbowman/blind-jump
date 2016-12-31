#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <bitset>
#include "shutdownSignal.hpp"

struct Cursor {
    float x, y;
};

class InputController {
public:
    InputController();
    void recordEvent(const sf::Event &);
    void clear();
    int getKeyState(const int) const;
    const sf::Vector2f & getCursorPosition();

private:
    Cursor m_cursor;
    std::array<int, sf::Keyboard::Key::KeyCount> m_keyStates;
};

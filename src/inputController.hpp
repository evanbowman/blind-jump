#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <bitset>

#include "shutdownSignal.hpp"

class InputController {
public:
    InputController();
    void recordEvent(const sf::Event &);
    void clear();
    int getKeyState(const int) const;

private:
    std::array<int, sf::Keyboard::Key::KeyCount> m_keyStates;
};

#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <array>
#include <bitset>
#include <json.hpp>
#include "shutdownSignal.hpp"

struct JoystickInfo {
    int vendorId;
    int productId;
    uint8_t shoot;
    uint8_t action;
    uint8_t pause;
};

class InputController {
public:
    InputController(nlohmann::json &);
    bool pausePressed() const;
    bool leftPressed() const;
    bool rightPressed() const;
    bool upPressed() const;
    bool downPressed() const;
    bool shootPressed() const;
    bool actionPressed() const;
    void recordEvent(const sf::Event &);
    void mapKeyboardKey(const sf::Keyboard::Key, const uint8_t);
    void mapJoystickButton(const uint32_t, const uint8_t);

private:
    enum {
        indexShoot,
        indexAction,
        indexPause,
        indexLeft,
        indexRight,
        indexUp,
        indexDown,
        indexCount
    };
    void remapJoystick();
    std::bitset<indexCount> keyMask;
    std::bitset<indexCount> joystickMask;
    std::array<uint32_t, 3> joystickMappings;
    std::array<sf::Keyboard::Key, 7> keyboardMappings;
    std::vector<JoystickInfo> joysticks;
};

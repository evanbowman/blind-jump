#pragma once
#include "alias.hpp"
#include <SFML/System.hpp>
#include <chrono>
#include <thread>

class Player;

namespace util {
extern bool isAsleep;
inline void sleep(const milliseconds & time) {
    isAsleep = true;
    std::this_thread::sleep_for(time);
}
}

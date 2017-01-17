#pragma once

#include "framework/framework.hpp"
#include <SFML/Graphics.hpp>

class Effect : public Object {
protected:
    int64_t timer;
    uint8_t frameIndex;

public:
    Effect(float _xInit, float _yInit)
        : Object(_xInit, _yInit), timer(0), frameIndex(0) {}
};

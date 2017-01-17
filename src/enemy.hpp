#pragma once

#include "effectsController.hpp"
#include "framework/framework.hpp"
#include "wall.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

class Enemy : public Object {
protected:
    bool colored;
    float colorAmount;
    uint8_t frameIndex, health;
    uint32_t colorTimer, frameTimer;
    uint_fast8_t checkWallCollision(const std::vector<wall> &, float, float);
    bool wallInPath(const std::vector<wall> &, float, float, float);
    void updateColor(const sf::Time &);
    void facePlayer();
    ~Enemy(){};

public:
    Enemy(float, float);
    bool isColored() const;
    float getColorAmount() const;
};

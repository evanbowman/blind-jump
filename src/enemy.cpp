#include "enemy.hpp"

Enemy::Enemy(float _xPos, float _yPos)
    : Object(_xPos, _yPos), colored(false), colorAmount(0.f), frameIndex(0),
      colorTimer(0), frameTimer(0) {}

float Enemy::getColorAmount() const { return colorAmount; }

bool Enemy::isColored() const { return colored; }

uint_fast8_t Enemy::checkWallCollision(const std::vector<wall> & w, float xPos,
                                       float yPos) {
    uint_fast8_t collisionMask = 0;
    for (auto & element : w) {
        if ((xPos + 6 < (element.getPosX() + element.getWidth()) &&
             (xPos + 6 > (element.getPosX()))) &&
            (fabs((yPos + 16) - element.getPosY()) <= 13)) {
            collisionMask |= 0x01;
        }

        if ((xPos + 24 > (element.getPosX()) &&
             (xPos + 24 < (element.getPosX() + element.getWidth()))) &&
            (fabs((yPos + 16) - element.getPosY()) <= 13)) {
            collisionMask |= 0x02;
        }

        if (((yPos + 22 < (element.getPosY() + element.getHeight())) &&
             (yPos + 22 > (element.getPosY()))) &&
            (fabs((xPos)-element.getPosX()) <= 16)) {
            collisionMask |= 0x04;
        }

        if (((yPos + 36 > element.getPosY()) &&
             (yPos + 36 < element.getPosY() + element.getHeight())) &&
            (fabs((xPos)-element.getPosX()) <= 16)) {
            collisionMask |= 0x08;
        }
    }
    return collisionMask;
}

bool Enemy::wallInPath(const std::vector<wall> & w, float dir, float xPos,
                       float yPos) {
    for (int i{10}; i < 100; i += 16) {
        if (checkWallCollision(w, xPos + cos(dir) * i, yPos + sin(dir) * i)) {
            return true;
        }
    }
    return false;
}

void Enemy::updateColor(const sf::Time & elapsedTime) {
    if (colored) {
        colorTimer += elapsedTime.asMilliseconds();
        if (colorTimer > 20.f) {
            colorTimer -= 20.f;
            colorAmount -= 0.1f;
        }
    }

    if (colorAmount <= 0.f) {
        colored = false;
    }
}

#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

namespace calc {
inline float clamp(float x, float floor, float ceil) {
    if (x < floor) {
        return floor;
    } else if (x > ceil) {
        return ceil;
    } else {
        return x;
    }
}
template <typename T> T lerp(const T & A, const T & B, const float t) {
    return A * t + (1 - t) * B;
}
inline float lerp(const float A, const float B, const float t) {
    return A * t + (1 - t) * B;
}
inline float smoothstep(const float edge0, const float edge1, float x) {
    x = clamp((x - edge0) / (edge1 - edge0), 0.f, 1.f);
    return x * x * (3 - 2 * x);
}
inline float smootherstep(const float edge0, const float edge1, float x) {
    x = clamp((x - edge0) / (edge1 - edge0), 0.f, 1.f);
    return x * x * x * (x * (x * 6 - 15) + 10);
}
namespace rng {
extern std::mt19937 RNG;

template <size_t upper, int lower = 0> int random() {
    return std::abs(static_cast<int>(RNG())) % upper + lower;
}

inline int random(size_t upper, int lower = 0) {
    return std::abs(static_cast<int>(RNG())) % upper + lower;
}

inline void seed() {
    std::random_device rd;
    RNG.seed(rd() ^ time(nullptr));
}
}
}

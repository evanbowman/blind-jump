//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

namespace math {
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
}

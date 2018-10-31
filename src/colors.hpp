#pragma once
#include <SFML/Graphics.hpp>

#define DEF_COLOR(NAME, R, G, B)                                               \
    struct NAME {                                                              \
        constexpr static float r = R;                                          \
        constexpr static float g = G;                                          \
        constexpr static float b = B;                                          \
    }

namespace colors {
DEF_COLOR(Ruby, 0.93f, 0.09f, 0.36f);
DEF_COLOR(GldnGt, 0.98f, 0.22f, 0.03f);
DEF_COLOR(White, 1.00f, 1.00f, 1.00f);
DEF_COLOR(Electric, 0.29f, 0.99f, 0.99f);
DEF_COLOR(Koamaru, 0.16f, 0.26f, 0.43f);
DEF_COLOR(Yellow, 1.00f, 0.84f, 0.08f);
} // namespace colors

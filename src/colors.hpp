//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once
#include <SFML/Graphics.hpp>

#define DEF_GLSL_COLOR(color, name)\
    static const sf::Glsl::Vec3 name(color::R, color::G, color::B)

namespace colors {
    namespace Ruby { 
        constexpr float R = 0.93f;
        constexpr float G = 0.09f;
        constexpr float B = 0.36f;
    }
    namespace GldnGt {
        constexpr float R = 0.98f;
        constexpr float G = 0.22f;
        constexpr float B = 0.03f;
    }
    namespace White {
        constexpr float R = 1.00f;
        constexpr float G = 1.00f;
        constexpr float B = 1.00f;
    }
    namespace Electric {
        constexpr float R = 0.29f;
        constexpr float G = 0.99f;
        constexpr float B = 0.99f;
    }
    namespace Koamaru {
        constexpr float R = 0.16f;
        constexpr float G = 0.26f;
        constexpr float B = 0.43f;
    }
}

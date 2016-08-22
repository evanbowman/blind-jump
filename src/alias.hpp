//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <chrono>
#include <tuple>
#include <SFML/Graphics.hpp>
#include "RenderType.hpp"

using high_resolution_clock = std::chrono::high_resolution_clock;
using nanoseconds = std::chrono::nanoseconds;
using microseconds = std::chrono::microseconds;
using milliseconds = std::chrono::milliseconds;
using time_point = std::chrono::high_resolution_clock::time_point;
using duration = std::chrono::duration<double>;
using drawableMetadata = std::tuple<sf::Sprite, float, Rendertype, float>;

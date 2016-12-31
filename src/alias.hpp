#pragma once

#include "Entity.hpp"
#include "RenderType.hpp"
#include "framework/framework.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <tuple>

using high_resolution_clock = std::chrono::high_resolution_clock;
using nanoseconds = std::chrono::nanoseconds;
using microseconds = std::chrono::microseconds;
using milliseconds = std::chrono::milliseconds;
using time_point = std::chrono::high_resolution_clock::time_point;
using duration = std::chrono::duration<double>;

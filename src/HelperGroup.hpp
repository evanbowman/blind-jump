#pragma once

#include "Laika.hpp"
#include "framework/framework.hpp"

using Laika = _Laika<RenderPolicy<DrawMain, DrawShadow>>;

struct HelperRef {
    enum { Laika };
};

using HelperGroup = Group<Laika>;

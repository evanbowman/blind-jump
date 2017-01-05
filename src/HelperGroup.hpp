#pragma once

#include "framework/framework.hpp"
#include "Laika.hpp"

using Laika = _Laika<RenderPolicy<DrawMain, DrawShadow>>;

struct HelperRef {
    enum {
	Laika
    };
};

using HelperGroup = framework::Group<Laika>;

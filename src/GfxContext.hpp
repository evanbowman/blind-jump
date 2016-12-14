#pragma once

#include <SFML/Graphics.hpp>
#include <tuple>

#include "RenderType.hpp"

using drawContext = std::tuple<sf::Sprite, float, Rendertype, float>;

struct GfxContext {
    std::vector<drawContext> faces, shadows;
    std::vector<sf::Sprite> glowSprs1, glowSprs2;
    sf::RenderTexture * targetRef;
};

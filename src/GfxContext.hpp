#pragma once

#include "alias.hpp"
#include <SFML/Graphics.hpp>
#include <tuple>

struct GfxContext {
    std::vector<EntityRef> entities;
    std::vector<sf::Sprite> glowSprs;
    sf::RenderTexture * targetRef;
};

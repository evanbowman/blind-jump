#pragma once
#include "spriteSheet.hpp"

struct Layer {
    SpriteSheet * sheet;
    float absorptivity;
    float paralax;
    enum class Type { full, tiled, stretched };
    Type type;
};

class BackgroundController {
private:
    std::vector<Layer> m_layers;

public:
};

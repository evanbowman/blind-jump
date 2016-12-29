#pragma once
#include "spriteSheet.hpp"
#include <functional>
#include <mutex>
#include <utility>

struct SpriteLayer {
    SpriteSheet * sheet;
    float paralax;
    enum class Fill { full, tiled, stretched };
    Fill fill;
    float x, y;
};

struct ColorLayer {
    struct Color {
        uint8_t r, g, b, a;
    };
    Color color;
};

struct Layer {
    union Data {
        SpriteLayer spriteLayer;
        ColorLayer colorLayer;
    };
    Data data;
    enum class Source { sprite, color };
    Source source;
    float absorptivity;
    std::unique_ptr<sf::RenderTexture> canvas;
    sf::BlendMode blending;
};

using LockedLayersMapPtr =
    std::pair<std::map<int, Layer> *, std::unique_lock<std::mutex>>;

class BackgroundController {
public:
    void addBkgLayer(const int, Layer &&);
    void addFgLayer(const int, Layer &&);
    LockedLayersMapPtr getBkgLayers();
    LockedLayersMapPtr getFgLayers();

private:
    std::mutex m_layersMutex;
    std::map<int, Layer> m_bkgLayers;
    std::map<int, Layer> m_fgLayers;
};

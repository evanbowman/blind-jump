#pragma once
#include "spriteSheet.hpp"
#include "utility.hpp"

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

using LayerMap = std::map<int, Layer>;

class BackgroundController {
public:
    void addBkgLayer(const int, Layer &&);
    void addFgLayer(const int, Layer &&);
    LockedRef<LayerMap> getBkgLayers();
    LockedRef<LayerMap> getFgLayers();

private:
    std::mutex m_fgLayersMutex;
    std::mutex m_bgLayersMutex;
    std::map<int, Layer> m_bkgLayers;
    std::map<int, Layer> m_fgLayers;
};

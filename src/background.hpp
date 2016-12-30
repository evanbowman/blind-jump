#pragma once
#include "spriteSheet.hpp"
#include "utility.hpp"

struct Layer {
    SpriteSheet * sheet;
    float x, y;
    bool fixed;
    float xScale, yScale;
    float lightingFactor;
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

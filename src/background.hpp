#pragma once
#include "spriteSheet.hpp"


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
    enum class Source {
	sprite, color
    };
    Source source;
    float absorptivity;
    std::unique_ptr<sf::RenderTexture> canvas;
    sf::BlendMode blending;
};

class BackgroundController {
public:
    void addBkgLayer(const int, Layer &&);
    void addFgLayer(const int, Layer &&);
    std::map<int, Layer> & getBkgLayers();
    std::map<int, Layer> & getFgLayers();
    
private:
    std::map<int, Layer> m_bkgLayers;
    std::map<int, Layer> m_fgLayers;
};

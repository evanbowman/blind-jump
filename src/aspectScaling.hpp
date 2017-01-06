#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <exception>
#include <json.hpp>

inline sf::Vector2f getDrawableArea(const nlohmann::json & configJSON) {
    sf::Vector2f drawableAreaSize = {};
    auto screenSize = sf::VideoMode::getDesktopMode();
    const float aspectRatio =
        (float)screenSize.width / (float)screenSize.height;
    try {
        for (auto it = configJSON["aspect-ratios"].begin();
             it != configJSON["aspect-ratios"].end(); ++it) {
            static const char delimiter = ':';
            const size_t splitPos = it.key().find(delimiter);
            const float wFactor =
                std::atoi(it.key().substr(0, splitPos).c_str());
            const float hFactor = std::atoi(
                it.key().substr(splitPos + 1, it.key().length()).c_str());
            const int width = it.value().find("width")->get<int>();
            const int height = it.value().find("height")->get<int>();
            if (wFactor / hFactor == aspectRatio) {
                drawableAreaSize.x = width;
                drawableAreaSize.y = height;
            } else if (hFactor / wFactor == aspectRatio) {
                drawableAreaSize.y = height;
                drawableAreaSize.x = width;
            }
        }
    } catch (const std::exception & ex) {
        throw std::runtime_error("JSON error: " + std::string(ex.what()));
    }
    return drawableAreaSize;
}

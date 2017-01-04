#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <exception>
#include <json.hpp>

inline sf::Vector2f getDrawableArea(const nlohmann::json & configJSON) {
    sf::Vector2f drawableAreaSize = {};
    try {
	auto screenSize = sf::VideoMode::getDesktopMode();
	const float aspect = static_cast<float>(screenSize.width)
	    / static_cast<float>(screenSize.height);
	auto aspectsArrayIter = configJSON.find("aspect-ratios");
	if (aspectsArrayIter != configJSON.end()) {
	    for (const auto & entry : *aspectsArrayIter) {
		auto aspectString = entry.find("aspect")->get<std::string>();
		static const std::string delimiter(":");
		size_t splitPos = aspectString.find(":");
		const float wFactor = std::atoi(aspectString.substr(0, splitPos).c_str());
		const float hFactor = std::atoi(aspectString.substr(splitPos + 1, aspectString.length()).c_str());
		const int width = entry.find("width")->get<int>();
		const int height = entry.find("height")->get<int>();
		if (wFactor / hFactor == aspect) {
		    drawableAreaSize.x = width;
		    drawableAreaSize.y = height;
		} else if (hFactor / wFactor == aspect) {
		    drawableAreaSize.y = height;
		    drawableAreaSize.x = width;
		}
	    }
	}
    } catch (const std::exception & ex) {
	throw std::runtime_error("JSON error: " + std::string(ex.what()));
    }
    return drawableAreaSize;
}

#pragma once
#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include "ResourcePath.hpp"

class TextureManager {	
public:
	enum class Texture {
		vignette,
			vignetteShadow,
			lamplight,
			introLevel
	};
	
	TextureManager();

	bool load();
	
	sf::Texture * getTexture(TextureManager::Texture);
		
private:
	std::map<int, sf::Texture> textures;
};

#endif

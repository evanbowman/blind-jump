#pragma once
#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include "ResourcePath.hpp"

class TextureManager {	
public:	
	#include "textureEnum.hpp"
	
	TextureManager();

	bool load();
	
	sf::Texture * getTexture(TextureManager::Texture);

	sf::Texture * getTexture(int);
	
private:
	std::map<int, sf::Texture> textures;
};

#endif

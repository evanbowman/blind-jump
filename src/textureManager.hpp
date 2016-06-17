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
	
	const sf::Texture & getTexture(TextureManager::Texture) const;

	const sf::Texture & getTexture(int) const;
	
private:
	mutable std::map<int, sf::Texture> textures;
};

#endif

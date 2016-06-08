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
			introLevel,
			playerShadow,
			playerUp1,
			playerUp2,
			playerUp3,
			playerUp4,
			playerUp5,
			playerUp6,
			playerDown1,
			playerDown2,
			playerDown3,
			playerDown4,
			playerDown5,
			playerDown6,
			playerRight1,
			playerRight2,
			playerRight3,
			playerRight4,
			playerRight5,
			playerRight6,
			playerRight7,
			playerLeft1,
			playerLeft2,
			playerLeft3,
			playerLeft4,
			playerLeft5,
			playerLeft6,
			playerLeft7
	};
	
	TextureManager();

	bool load();
	
	sf::Texture * getTexture(TextureManager::Texture);

	sf::Texture * getTexture(int);
	
private:
	std::map<int, sf::Texture> textures;
};

#endif

//
//  Created by Evan Bowman 2016
//

#pragma once
#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <utility>
#include <array>
#include "ResourcePath.hpp"

class ResourceHandler {	
public:	
    enum class Texture {
		gameObjects,
		vignette,
		vignetteShadow,
		lamplight,
		introLevel,
		teleporterGlow,
		introWall,
		redglow,
		blueglow,
		fireExplosionGlow,
		whiteGlow,
		scootShadow
	};
	enum class Shader {
		color,
		blur,
		desaturate
	};
	enum class Font {
		cornerstone
	};
    
	bool load();
	
	const sf::Texture & getTexture(ResourceHandler::Texture) const;
	const sf::Texture & getTexture(int) const;
	const sf::Font & getFont(ResourceHandler::Font) const;
	sf::Shader & getShader(ResourceHandler::Shader) const; // Exception: shader cannot be a constant reference
	
private:
	mutable std::map<int, sf::Texture> textures;
	mutable std::array<sf::Shader, 3> shaders;
	mutable std::array<sf::Font, 1> fonts;
};

// Many classes need to access the resource handler, and its accessors return only const references
extern ResourceHandler globalResourceHandler;

#endif

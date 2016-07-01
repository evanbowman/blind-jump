//
//  Created by Evan Bowman 2016
//

#pragma once
#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
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

	ResourceHandler();

	bool load();
	
	const sf::Texture & getTexture(ResourceHandler::Texture) const;

	const sf::Texture & getTexture(int) const;
	
private:
	mutable std::map<int, sf::Texture> textures;
	mutable std::map<int, sf::Shader> shaders;
};

#endif

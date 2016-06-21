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
	#include "textureEnum.hpp"
	
	ResourceHandler();

	bool load();
	
	const sf::Texture & getTexture(ResourceHandler::Texture) const;

	const sf::Texture & getTexture(int) const;
	
private:
	mutable std::map<int, sf::Texture> textures;
};

#endif

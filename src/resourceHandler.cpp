//
//  Created by Evan Bowman 2016
//

#include "resourceHandler.hpp"

bool loadTexture(const char * fname, ResourceHandler::Texture id, std::map<int, sf::Texture> & textures) {
	sf::Texture temp;
	if (!temp.loadFromFile(resourcePath() + fname)) {
		return false;
	}
	textures[static_cast<int>(id)] = temp;
	return true;
}

bool loadShader(const char * fname, ResourceHandler::Shader id, std::array<sf::Shader, 3> & shaders) {
	std::size_t index = static_cast<int>(id);
	if (!shaders[index].loadFromFile(resourcePath() + fname, sf::Shader::Fragment)) {
		return false;
	}
	shaders[index].setParameter("texture", sf::Shader::CurrentTexture);
	return true;
}

bool loadFont(const char * fname, ResourceHandler::Font id, std::array<sf::Font, 1> & fonts) {
	std::size_t index = static_cast<int>(id);
	if (!fonts[index].loadFromFile(resourcePath() + fname)) {
		return false;
	}
	return true;
}

bool ResourceHandler::load() {
	if (!loadTexture("gameObjects.png", Texture::gameObjects, textures)) {
		return false;
	}

	if (!loadTexture("vignetteMask.png", Texture::vignette, textures)) {
		return false;
	}

	if (!loadTexture("vignetteShadow.png", Texture::vignetteShadow, textures)) {
		return false;
	}

	if (!loadTexture("lampLight.png", Texture::lamplight, textures)) {
		return false;
	}

	if (!loadTexture("introLevel.png", Texture::introLevel, textures)) {
		return false;
	}

	if (!loadTexture("teleporterGlow.png", Texture::teleporterGlow, textures)) {
		return false;
	}

	if (!loadTexture("introWall.png", Texture::introWall, textures)) {
		return false;
	}

	if (!loadTexture("redFloorGlow.png", Texture::redglow, textures)) {
		return false;
	}

	if (!loadTexture("blueFloorGlow.png", Texture::blueglow, textures)) {
		return false;
	}
	
	if (!loadTexture("fireExplosionGlow.png", Texture::fireExplosionGlow, textures)) {
		return false;
	}

	if (!loadTexture("whiteFloorGlow.png", Texture::whiteGlow, textures)) {
		return false;
	}

	if (!loadTexture("charger_enemy_shadow.png", Texture::scootShadow, textures)) {
		return false;
	}

	if (!loadShader("color.frag", Shader::color, shaders)) {
		return false;
	}

	if (!loadShader("blur.frag", Shader::blur, shaders)) {
		return false;
	}

	if (!loadShader("desaturate.frag", Shader::desaturate, shaders)) {
		return false;
	}

	if (!loadFont("Cornerstone.ttf", Font::cornerstone, fonts)) {
		return false;
	}
	
	return true;
}

const sf::Texture & ResourceHandler::getTexture(Texture id) const {
	return textures[static_cast<int>(id)];
}

const sf::Texture & ResourceHandler::getTexture(int id) const {
	return textures[id];
}

const sf::Font & ResourceHandler::getFont(Font id) const {
	return fonts[static_cast<int>(id)];
}

sf::Shader & ResourceHandler::getShader(Shader id) const {
	return shaders[static_cast<int>(id)];
}

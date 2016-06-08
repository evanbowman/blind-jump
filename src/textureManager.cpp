#include "textureManager.hpp"

TextureManager::TextureManager() {}

bool TextureManager::load() {
	sf::Texture vignetteTexture;
	if (!vignetteTexture.loadFromFile(resourcePath() + "vignetteMask.png")) {
		return false;
	}
	vignetteTexture.setSmooth(true);
	textures[static_cast<int>(Texture::vignette)] = vignetteTexture;

	sf::Texture vignetteShadow;
	if (!vignetteShadow.loadFromFile(resourcePath() + "vignetteShadow.png")) {
		return false;
	}
	textures[static_cast<int>(Texture::vignetteShadow)] = vignetteShadow;

	sf::Texture lampLight;
	if (!lampLight.loadFromFile(resourcePath() + "lampLight.png")) {
		return false;
	}
	textures[static_cast<int>(Texture::lamplight)] = lampLight;

	sf::Texture introLevel;
	if (!introLevel.loadFromFile(resourcePath() + "introLevel.png")) {
		return false;
	}
	textures[static_cast<int>(Texture::introLevel)] = introLevel;
	
	return true;
}

sf::Texture * TextureManager::getTexture(Texture id) {
	return &textures[static_cast<int>(id)];
}

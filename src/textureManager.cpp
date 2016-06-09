#include "textureManager.hpp"
#include <utility>

TextureManager::TextureManager() {}

bool loadTexture(const char * fname, TextureManager::Texture id, std::map<int, sf::Texture> & textures) {
	sf::Texture temp;
	if (!temp.loadFromFile(resourcePath() + fname)) {
		return false;
	}
	textures[static_cast<int>(id)] = temp;
	return true;
}

bool TextureManager::load() {
	if (!loadTexture("vignetteMask.png", Texture::vignette, textures))
		return false;

	if (!loadTexture("vignetteShadow.png", Texture::vignetteShadow, textures))
		return false;

	if (!loadTexture("lampLight.png", Texture::lamplight, textures))
		return false;

	if (!loadTexture("introLevel.png", Texture::introLevel, textures))
		return false;

	if (!loadTexture("player_shadow.png", Texture::playerShadow, textures))
		return false;

	if (!loadTexture("playerWalkDown.png", Texture::playerDown, textures))
		return false;

	if (!loadTexture("playerWalkUp.png", Texture::playerUp, textures))
		return false;

	if (!loadTexture("playerWalkLeft.png", Texture::playerLeft, textures))
		return false;

	if (!loadTexture("playerWalkRight.png", Texture::playerRight, textures))
		return false;

	if (!loadTexture("playerDashsheet.png", Texture::playerDash, textures))
		return false;

	if (!loadTexture("player_death_animation.png", Texture::playerDeath, textures))
		return false;

	return true;
}

sf::Texture * TextureManager::getTexture(Texture id) {
	return &textures[static_cast<int>(id)];
}

sf::Texture * TextureManager::getTexture(int id) {
	return &textures[id];
}

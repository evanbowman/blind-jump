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

bool loadTextures(const char * fname, TextureManager::Texture id, std::map<int, sf::Texture> & textures, int8_t iters, const std::pair<int, int> & size) {
	for (int i = 0; i < iters; i++) {
		sf::Texture temp;
		if (!temp.loadFromFile(resourcePath() + fname, sf::IntRect(size.first * i, 0, size.first, size.second))) {
			return false;
		}
		textures[static_cast<int>(id) + i] = temp;
	}
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

	if (!loadTextures("playerWalk.png", Texture::playerDown, textures, 26, std::make_pair(32, 32)))
		return false;

	if (!loadTextures("playerDashsheet.png", Texture::playerDash, textures, 12, std::make_pair(32, 33)))
		return false;

	if (!loadTextures("player_death_animation.png", Texture::playerDeath, textures, 11, std::make_pair(40, 38)))
		return false;

	return true;
}

sf::Texture * TextureManager::getTexture(Texture id) {
	return &textures[static_cast<int>(id)];
}

sf::Texture * TextureManager::getTexture(int id) {
	return &textures[id];
}

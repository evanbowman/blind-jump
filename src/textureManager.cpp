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
	if (!loadTexture("gameObjects.png", Texture::gameObjects, textures))
		return false;

	if (!loadTexture("vignetteMask.png", Texture::vignette, textures))
		return false;

	if (!loadTexture("vignetteShadow.png", Texture::vignetteShadow, textures))
		return false;

	if (!loadTexture("lampLight.png", Texture::lamplight, textures))
		return false;

	if (!loadTexture("introLevel.png", Texture::introLevel, textures))
		return false;

	if (!loadTexture("lampLight.png", Texture::lamplight, textures))
		return false;

	if (!loadTexture("lamp.png", Texture::lamp, textures))
		return false;

	if (!loadTexture("pod.png", Texture::pod, textures))
		return false;

	if (!loadTexture("warpImpact.png", Texture::warpImpact, textures))
		return false;

	if (!loadTexture("enemyScraps.png", Texture::enemyScrap, textures))
		return false;

	if (!loadTexture("teleporterGlow.png", Texture::teleporterGlow, textures))
		return false;

	if (!loadTexture("introWall.png", Texture::introWall, textures))
		return false; // 200 x 95, four kinds

	if (!loadTexture("redFloorGlow.png", Texture::redglow, textures))
		return false;

	if (!loadTexture("blueFloorGlow.png", Texture::blueglow, textures))
		return false;
	
	if (!loadTexture("orbShot.png", Texture::orbShot, textures))
		return false;

	if (!loadTexture("dasherShot.png", Texture::dasherShot, textures))
		return false;

	if (!loadTexture("fireExplosionGlow.png", Texture::fireExplosionGlow, textures))
		return false;

	if (!loadTexture("smallExplosion.png", Texture::smallExplosion, textures))
		return false;

	if (!loadTexture("whiteFloorGlow.png", Texture::whiteGlow, textures))
		return false;

	if (!loadTexture("bullet.png", Texture::bullet, textures))
		return false;

	if (!loadTexture("charger_enemy_shadow.png", Texture::scootShadow, textures))
		return false;
	
	return true;
}

const sf::Texture & TextureManager::getTexture(Texture id) const {
	return textures[static_cast<int>(id)];
}

const sf::Texture & TextureManager::getTexture(int id) const {
	return textures[id];
}

//
//  Created by Evan Bowman 2016
//

#include "resourceHandler.hpp"
#include <utility>

ResourceHandler::ResourceHandler() {}

bool loadTexture(const char * fname, ResourceHandler::Texture id, std::map<int, sf::Texture> & textures) {
	sf::Texture temp;
	if (!temp.loadFromFile(resourcePath() + fname)) {
		return false;
	}
	textures[static_cast<int>(id)] = temp;
	return true;
}

bool ResourceHandler::load() {
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

	if (!loadTexture("teleporterGlow.png", Texture::teleporterGlow, textures))
		return false;

	if (!loadTexture("introWall.png", Texture::introWall, textures))
		return false; // 200 x 95, four kinds

	if (!loadTexture("redFloorGlow.png", Texture::redglow, textures))
		return false;

	if (!loadTexture("blueFloorGlow.png", Texture::blueglow, textures))
		return false;
	
	if (!loadTexture("fireExplosionGlow.png", Texture::fireExplosionGlow, textures))
		return false;

	if (!loadTexture("whiteFloorGlow.png", Texture::whiteGlow, textures))
		return false;

	if (!loadTexture("charger_enemy_shadow.png", Texture::scootShadow, textures))
		return false;
	
	return true;
}

const sf::Texture & ResourceHandler::getTexture(Texture id) const {
	return textures[static_cast<int>(id)];
}

const sf::Texture & ResourceHandler::getTexture(int id) const {
	return textures[id];
}

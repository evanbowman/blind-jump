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

	if (!loadTexture("lampLight.png", Texture::lamplight, textures))
		return false;

	if (!loadTexture("lamp.png", Texture::lamp, textures))
		return false;

	if (!loadTexture("bouldersheet.png", Texture::rock, textures))
		return false; // 32 x 64, two kinds

	if (!loadTexture("damagedRobotSheet.png", Texture::damagedRobot, textures))
		return false; // 40 x 43, two kinds

	if (!loadTexture("pod.png", Texture::pod, textures))
		return false;

	if (!loadTexture("treasureChest.png", Texture::treasureChest, textures))
		return false; // 16 x 30, six kinds
	
	if (!loadTexture("dasherDead.png", Texture::dasherDead, textures))
		return false;

	if (!loadTexture("teleporter.png", Texture::teleporter, textures))
		return false;

	if (!loadTexture("teleporterShadow.png", Texture::teleporterShadow, textures))
		return false;

	if (!loadTexture("chestShadow.png", Texture::chestShadow, textures))
		return false;

	if (!loadTexture("warpImpact.png", Texture::warpImpact, textures))
		return false;

	if (!loadTexture("enemyScraps.png", Texture::enemyScrap, textures))
		return false;

	if (!loadTexture("teleporterGlow.png", Texture::teleporterGlow, textures))
		return false;

	if (!loadTexture("introWall.png", Texture::introWall, textures))
		return false; // 200 x 95, four kinds

	if (!loadTexture("powerups.png", Texture::powerup, textures))
		return false; // 13 x 13, two kinds

	if (!loadTexture("redFloorGlow.png", Texture::redglow, textures))
		return false;

	if (!loadTexture("blueFloorGlow.png", Texture::blueglow, textures))
		return false;

	if (!loadTexture("turretShot.png", Texture::turretShot, textures))
		return false;

	if (!loadTexture("orbShot.png", Texture::orbShot, textures))
		return false;

	if (!loadTexture("dasherShot.png", Texture::dasherShot, textures))
		return false;

	if (!loadTexture("fireExplosionSheet.png", Texture::fireExplosion, textures))
		return false;

	if (!loadTexture("fireExplosionGlow.png", Texture::fireExplosionGlow, textures))
		return false;

	if (!loadTexture("smallExplosion.png", Texture::smallExplosion, textures))
		return false;
	
	return true;
}

sf::Texture * TextureManager::getTexture(Texture id) {
	return &textures[static_cast<int>(id)];
}

sf::Texture * TextureManager::getTexture(int id) {
	return &textures[id];
}

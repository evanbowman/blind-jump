//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "resourceHandler.hpp"

static const char * failurePrefix = "[Failed to load ";

template<typename T, typename E>
void loadResource(const char * fname, E id, T & array) {
	int idx = static_cast<int>(id);
	if (!array[idx].loadFromFile(resourcePath() + fname)) {
		throw std::runtime_error(std::string(failurePrefix) + fname + "]");
	}
}

template<>
void loadResource(const char * fname, ResHandler::Shader id, std::array<sf::Shader, 3> & shaders) {
	std::size_t index = static_cast<int>(id);
	if (!shaders[index].loadFromFile(resourcePath() + fname, sf::Shader::Fragment)) {
		throw std::runtime_error(std::string(failurePrefix) + fname + "]");
	}
	shaders[index].setParameter("texture", sf::Shader::CurrentTexture);
}

void ResHandler::load() {
	loadResource("teleporterBeamGlow.png", Texture::teleporterBeamGlow, textures);
	loadResource("fireExplosionGlow.png", Texture::fireExplosionGlow, textures);
	loadResource("charger_enemy_shadow.png", Texture::scootShadow, textures);
	loadResource("vignetteShadow.png", Texture::vignetteShadow, textures);
	loadResource("teleporterGlow.png", Texture::teleporterGlow, textures);
	loadResource("bkg_stars_distant.png", Texture::bkgStarsFar, textures);
	loadResource("introLevelMask.png", Texture::introLevelMask, textures);
	loadResource("powerupSheet.png", Texture::powerupSheet, textures);
	loadResource("whiteFloorGlow.png", Texture::whiteGlow, textures);
	loadResource("gameObjects.png", Texture::gameObjects, textures);
	loadResource("blueFloorGlow.png", Texture::blueglow, textures);
	loadResource("bkg_stars.png", Texture::bkgStarsNear, textures);
	loadResource("vignetteMask.png", Texture::vignette, textures);
	loadResource("introLevel.png", Texture::introLevel, textures);
	loadResource("redFloorGlow.png", Texture::redglow, textures);
	loadResource("lampLight.png", Texture::lamplight, textures);
	loadResource("introWall.png", Texture::introWall, textures);
	loadResource("bkg_orbit2.png", Texture::bkgOrbit, textures);
	loadResource("desaturate.frag", Shader::desaturate, shaders);
	loadResource("color.frag", Shader::color, shaders);
	loadResource("blur.frag", Shader::blur, shaders);
	loadResource("Cornerstone.ttf", Font::cornerstone, fonts);
	loadResource("soilTileset.png", Image::soilTileset, images);
	loadResource("grassSetEdge.png", Image::grassSet2, images);
	loadResource("grassSet.png", Image::grassSet1, images);
	loadResource("gameIcon.png", Image::icon, images);
    loadResource("gunshot.ogg", Sound::gunShot, sounds);
}

const sf::Image & ResHandler::getImage(Image id) const {
	return images[static_cast<int>(id)];
}

const sf::Texture & ResHandler::getTexture(Texture id) const {
	return textures[static_cast<int>(id)];
}

const sf::Texture & ResHandler::getTexture(int id) const {
	return textures[id];
}

const sf::Font & ResHandler::getFont(Font id) const {
	return fonts[static_cast<int>(id)];
}

sf::Shader & ResHandler::getShader(Shader id) const {
	return shaders[static_cast<int>(id)];
}

const sf::SoundBuffer & ResHandler::getSound(Sound id) const {
	return sounds[static_cast<int>(id)];
}

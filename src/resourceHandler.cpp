//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
//                                                                        //
// This program is free software: you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or      //
// (at your option) any later version.                                    //
//                                                                        //
// This program is distributed in the hope that it will be useful,        //
// but WITHOUT ANY WARRANTY; without even the implied warranty of         //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
// GNU General Public License for more details.                           //
//                                                                        //
// You should have received a copy of the GNU General Public License      //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
//========================================================================//

#include "resourceHandler.hpp"

static const char * failurePrefix = "[Failed to load ";

void loadTexture(const char * fname, ResourceHandler::Texture id, std::map<int, sf::Texture> & textures) {
	sf::Texture temp;
	if (!temp.loadFromFile(resourcePath() + fname)) {
		throw std::runtime_error(std::string(failurePrefix) + fname + "]");
	}
	textures[static_cast<int>(id)] = temp;
}

void loadShader(const char * fname, ResourceHandler::Shader id, std::array<sf::Shader, 3> & shaders) {
	std::size_t index = static_cast<int>(id);
	if (!shaders[index].loadFromFile(resourcePath() + fname, sf::Shader::Fragment)) {
		throw std::runtime_error(std::string(failurePrefix) + fname + "]");
	}
	shaders[index].setParameter("texture", sf::Shader::CurrentTexture);
}

void loadImage(const char * fname, ResourceHandler::Image id, std::array<sf::Image, 4> & images) {
	std::size_t index = static_cast<int>(id);
	if (!images[index].loadFromFile(resourcePath() + fname)) {
		throw std::runtime_error(std::string(failurePrefix) + fname + "]");
	}
}

void loadFont(const char * fname, ResourceHandler::Font id, std::array<sf::Font, 1> & fonts) {
	std::size_t index = static_cast<int>(id);
	if (!fonts[index].loadFromFile(resourcePath() + fname)) {
		throw std::runtime_error(std::string(failurePrefix) + fname + "]");
	}
}

void loadSound(const char * fname, ResourceHandler::Sound id, std::array<sf::SoundBuffer, 1> & sounds) {
	std::size_t index = static_cast<int>(id);
	if (!sounds[index].loadFromFile(resourcePath() + fname)) {
		throw std::runtime_error(std::string(failurePrefix) + fname + "]");
	}
}

void ResourceHandler::load() {
	loadTexture("gameObjects.png", Texture::gameObjects, textures);
	loadTexture("vignetteMask.png", Texture::vignette, textures);
	loadTexture("vignetteShadow.png", Texture::vignetteShadow, textures);
	loadTexture("lampLight.png", Texture::lamplight, textures);
	loadTexture("introLevel.png", Texture::introLevel, textures);
	loadTexture("teleporterGlow.png", Texture::teleporterGlow, textures);
	loadTexture("introWall.png", Texture::introWall, textures);
	loadTexture("redFloorGlow.png", Texture::redglow, textures);
	loadTexture("blueFloorGlow.png", Texture::blueglow, textures);
	loadTexture("fireExplosionGlow.png", Texture::fireExplosionGlow, textures);
	loadTexture("whiteFloorGlow.png", Texture::whiteGlow, textures);
	loadTexture("charger_enemy_shadow.png", Texture::scootShadow, textures);
	loadTexture("teleporterBeamGlow.png", Texture::teleporterBeamGlow, textures);
	loadTexture("bkg_stars.png", Texture::bkgStarsNear, textures);
	loadTexture("bkg_stars_distant.png", Texture::bkgStarsFar, textures);
	loadTexture("introLevelMask.png", Texture::introLevelMask, textures);
	loadTexture("bkg_orbit2.png", Texture::bkgOrbit, textures);
	loadShader("color.frag", Shader::color, shaders);
	loadShader("blur.frag", Shader::blur, shaders);
	loadShader("desaturate.frag", Shader::desaturate, shaders);
	loadFont("Cornerstone.ttf", Font::cornerstone, fonts);
	loadImage("soilTileset.png", Image::soilTileset, images);
	loadImage("grassSet.png", Image::grassSet1, images);
	loadImage("grassSetEdge.png", Image::grassSet2, images);
	loadImage("gameIcon.png", Image::icon, images);
	loadSound("gunshot.ogg", Sound::gunShot, sounds);
}

const sf::Image & ResourceHandler::getImage(Image id) const {
	return images[static_cast<int>(id)];
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

const sf::SoundBuffer & ResourceHandler::getSound(Sound id) const {
	return sounds[static_cast<int>(id)];
}

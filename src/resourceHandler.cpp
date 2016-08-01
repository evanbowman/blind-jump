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

int loadTexture(const char * fname, ResourceHandler::Texture id, std::map<int, sf::Texture> & textures) {
	sf::Texture temp;
	if (!temp.loadFromFile(resourcePath() + fname)) {
		return 1;
	}
	textures[static_cast<int>(id)] = temp;
	return 0;
}

int loadShader(const char * fname, ResourceHandler::Shader id, std::array<sf::Shader, 3> & shaders) {
	std::size_t index = static_cast<int>(id);
	if (!shaders[index].loadFromFile(resourcePath() + fname, sf::Shader::Fragment)) {
		return 1;
	}
	shaders[index].setParameter("texture", sf::Shader::CurrentTexture);
	return 0;
}

int loadImage(const char * fname, ResourceHandler::Image id, std::array<sf::Image, 3> & images) {
	std::size_t index = static_cast<int>(id);
	if (!images[index].loadFromFile(resourcePath() + fname)) {
		return 1;
	}
	return 0;
}

int loadFont(const char * fname, ResourceHandler::Font id, std::array<sf::Font, 1> & fonts) {
	std::size_t index = static_cast<int>(id);
	if (!fonts[index].loadFromFile(resourcePath() + fname)) {
		return 1;
	}
	return 0;
}

int ResourceHandler::load() {
	int errs = 0;
	errs += loadTexture("gameObjects.png", Texture::gameObjects, textures);
	errs += loadTexture("vignetteMask.png", Texture::vignette, textures);
	errs += loadTexture("vignetteShadow.png", Texture::vignetteShadow, textures);
	errs += loadTexture("lampLight.png", Texture::lamplight, textures);
	errs += loadTexture("introLevel.png", Texture::introLevel, textures);
	errs += loadTexture("teleporterGlow.png", Texture::teleporterGlow, textures);
	errs += loadTexture("introWall.png", Texture::introWall, textures);
	errs += loadTexture("redFloorGlow.png", Texture::redglow, textures);
	errs += loadTexture("blueFloorGlow.png", Texture::blueglow, textures);
	errs += loadTexture("fireExplosionGlow.png", Texture::fireExplosionGlow, textures);
	errs += loadTexture("whiteFloorGlow.png", Texture::whiteGlow, textures);
	errs += loadTexture("charger_enemy_shadow.png", Texture::scootShadow, textures);
	errs += loadShader("color.frag", Shader::color, shaders);
	errs += loadShader("blur.frag", Shader::blur, shaders);
	errs += loadShader("desaturate.frag", Shader::desaturate, shaders);
	errs += loadFont("Cornerstone.ttf", Font::cornerstone, fonts);
	errs += loadImage("soilTileset.png", Image::soilTileset, images);
	errs += loadImage("grassSet.png", Image::grassSet1, images);
	errs += loadImage("grassSetEdge.png", Image::grassSet2, images);
	return errs;
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

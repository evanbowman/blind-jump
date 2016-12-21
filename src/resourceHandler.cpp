//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "resourceHandler.hpp"

static const char * LOAD_FAILURE_MSG = "blindjump [crash]: missing resource";

template <typename T, typename E>
void loadResource(const std::string & str, E id, T & array) {
    int idx = static_cast<int>(id);
    if (!array[idx].loadFromFile(str)) {
        throw std::runtime_error(LOAD_FAILURE_MSG);
    }
}

template <typename T>
void loadResource(const std::string & str, T & map) {
    if (!map[str].loadFromFile(resourcePath() + str)) {
        throw std::runtime_error(LOAD_FAILURE_MSG);
    }
}

template <>
void loadResource(
    const std::string & str, ResHandler::Shader id,
    std::array<sf::Shader, static_cast<int>(ResHandler::Shader::count)> &
        shaders) {
    size_t index = static_cast<int>(id);
    if (!shaders[index].loadFromFile(str, sf::Shader::Fragment)) {
        throw std::runtime_error(LOAD_FAILURE_MSG);
    }
    shaders[index].setUniform("texture", sf::Shader::CurrentTexture);
}

static bool hasResources;

void ResHandler::load() {
    assert(!hasResources);
    hasResources = true;
    const std::string resPath = resourcePath();
    loadShaders(resPath);
    loadFonts(resPath);
    loadImages(resPath);
}

void ResHandler::loadShaders(const std::string & resPath) {
    loadResource(resPath + "shaders/desaturate.frag", Shader::desaturate,
                 shaders);
    loadResource(resPath + "shaders/color.frag", Shader::color, shaders);
    loadResource(resPath + "shaders/blur.frag", Shader::blur, shaders);
}

void ResHandler::loadTexture(const std::string & path) {
    loadResource(path, textures);
}

void ResHandler::loadFonts(const std::string & resPath) {
    loadResource(resPath + "fonts/Cornerstone.ttf", Font::cornerstone, fonts);
}

void ResHandler::loadImages(const std::string & resPath) {
    loadResource(resPath + "textures/soilTileset.png", Image::soilTileset,
                 images);
    loadResource(resPath + "textures/grassSetEdge.png", Image::grassSet2,
                 images);
    loadResource(resPath + "textures/grassSet.png", Image::grassSet1, images);
    loadResource(resPath + "textures/gameIcon.png", Image::icon, images);
}

void ResHandler::loadSound(const std::string & path) {
    loadResource(path, sounds);
}

const sf::Image & ResHandler::getImage(Image id) const {
    return images[static_cast<int>(id)];
}

const sf::Texture & ResHandler::getTexture(const std::string & path) {
    if (textures.find(path) == textures.end()) {
	const std::string err = "Error: path " + path + "hasn't been loaded.";
	throw std::runtime_error(err);
    }
    return textures[path];
}

const sf::Font & ResHandler::getFont(Font id) const {
    return fonts[static_cast<int>(id)];
}

sf::Shader & ResHandler::getShader(Shader id) {
    return shaders[static_cast<int>(id)];
}

const sf::SoundBuffer & ResHandler::getSound(const std::string & path) {
    if (sounds.find(path) == sounds.end()) {
	const std::string err = "Error: path " + path + "hasn't been loaded.";
	throw std::runtime_error(err);
    }
    return sounds[path];
}

static ResHandler * resHandlerPtr;

void setgResHandlerPtr(ResHandler * addr) {
    assert(!::resHandlerPtr);
    ::resHandlerPtr = addr;
}

ResHandler * getgResHandlerPtr() noexcept { return ::resHandlerPtr; }

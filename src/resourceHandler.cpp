//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "resourceHandler.hpp"

static const char * LOAD_FAILURE_MSG = "blindjump [crash]: missing resource";

template <typename T>
void loadResource(const std::string & str, T & map) {
    if (!map[str].loadFromFile(resourcePath() + str)) {
        throw std::runtime_error(LOAD_FAILURE_MSG);
    }
}

template <>
void loadResource(const std::string & str, std::map<std::string, sf::Shader> & shaders) {
    if (!shaders[str].loadFromFile(resourcePath() + str, sf::Shader::Fragment)) {
        throw std::runtime_error(LOAD_FAILURE_MSG);
    }
    shaders[str].setUniform("texture", sf::Shader::CurrentTexture);
}

void ResHandler::loadFromJSON(json & JSON) {
    auto it = JSON.find("textures");
    if (it != JSON.end()) {
	for (const auto & entry : *it) {
	    this->loadTexture(entry);
	}
    }
    it = JSON.find("sounds");
    if (it != JSON.end()) {
	for (const auto & entry : *it) {
	    this->loadSound(entry);
	}
    }
    it = JSON.find("fonts");
    if (it != JSON.end()) {
	for (const auto & entry : *it) {
	    this->loadFont(entry);
	}
    }
    it = JSON.find("images");
    if (it != JSON.end()) {
	for (const auto & entry : *it) {
	    this->loadImage(entry);
	}
    }
    it = JSON.find("shaders");
    if (it != JSON.end()) {
	for (const auto & entry : *it) {
	    this->loadShader(entry);
	}
    }
    it = JSON.find("sprites");
    if (it != JSON.end()) {
	for (auto sheet = it->begin(); sheet != it->end(); ++sheet) {
	    auto textureTag = sheet->find("texture");
	    auto boxObj = sheet->find("box");
	    int x = boxObj->find("x")->get<int>();
	    int y = boxObj->find("y")->get<int>();
	    int w = boxObj->find("w")->get<int>();
	    int h = boxObj->find("h")->get<int>();
	    auto & texture = this->getTexture(*textureTag);
	    this->addSheet(sheet.key(), SpriteSheet(texture,
						    sf::IntRect(x, y, w, h)));
	    // FIXME: sprites should be centered on origin, but this results in offsets
	    // that I don't understand yet...
	    // auto added = sheets.find(sheet.key());
	    // added->second.getSprite().setOrigin(x / 2, y / 2);
	}
    }
}

void ResHandler::addSheet(const std::string & name, const SpriteSheet & sheet) {
    sheets.insert(std::map<std::string, SpriteSheet>::value_type(name, sheet));
}

void ResHandler::loadTexture(const std::string & path) {
    loadResource(path, textures);
}

void ResHandler::loadSound(const std::string & path) {
    loadResource(path, sounds);
}

void ResHandler::loadShader(const std::string & path) {
    loadResource(path, shaders);
}

void ResHandler::loadFont(const std::string & path) {
    loadResource(path, fonts);
}

void ResHandler::loadImage(const std::string & path) {
    loadResource(path, images);
}

SpriteSheet & ResHandler::getSheet(const std::string & name) {
    return sheets.find(name)->second;
}

const sf::Texture & ResHandler::getTexture(const std::string & path) {
    if (textures.find(path) == textures.end()) {
	const std::string err = "Error: path " + path + "hasn't been loaded.";
	throw std::runtime_error(err);
    }
    return textures[path];
}

const sf::SoundBuffer & ResHandler::getSound(const std::string & path) {
    if (sounds.find(path) == sounds.end()) {
	const std::string err = "Error: path " + path + "hasn't been loaded.";
	throw std::runtime_error(err);
    }
    return sounds[path];
}


const sf::Image & ResHandler::getImage(const std::string & path) {
    if (images.find(path) == images.end()) {
	const std::string err = "Error: path " + path + "hasn't been loaded.";
	throw std::runtime_error(err);
    }
    return images[path];
}

const sf::Font & ResHandler::getFont(const std::string & path) {
    if (fonts.find(path) == fonts.end()) {
	const std::string err = "Error: path " + path + "hasn't been loaded.";
	throw std::runtime_error(err);
    }
    return fonts[path];
}

sf::Shader & ResHandler::getShader(const std::string & path) {
    if (shaders.find(path) == shaders.end()) {
	const std::string err = "Error: path " + path + "hasn't been loaded.";
	throw std::runtime_error(err);
    }
    return shaders[path];
}

static ResHandler * resHandlerPtr;

void setgResHandlerPtr(ResHandler * addr) {
    assert(!::resHandlerPtr);
    ::resHandlerPtr = addr;
}

ResHandler * getgResHandlerPtr() noexcept { return ::resHandlerPtr; }

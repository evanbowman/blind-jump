#include "resourceHandler.hpp"

static const char * LOAD_FAILURE_MSG = "blindjump [crash]: missing resource";

template <typename T> void loadResource(const std::string & str, T & map) {
    if (!map[str].loadFromFile(resourcePath() + str)) {
        throw std::runtime_error(LOAD_FAILURE_MSG);
    }
}

template <>
void loadResource(const std::string & str,
                  std::map<std::string, sf::Shader> & shaders) {
    if (!shaders[str].loadFromFile(resourcePath() + str,
                                   sf::Shader::Fragment)) {
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
            this->addSheet(sheet.key(),
                           SpriteSheet(texture, sf::IntRect(x, y, w, h)));
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
    auto it = sheets.find(name);
    if (it != sheets.end()) {
        return it->second;
    }
    const std::string err = "Error: sprite " + name + "does not exist.";
    throw std::runtime_error(err);
}

const sf::Texture & ResHandler::getTexture(const std::string & path) {
    auto it = textures.find(path);
    if (it == textures.end()) {
        const std::string err = "Error: path " + path + "hasn't been loaded.";
        throw std::runtime_error(err);
    }
    return it->second;
}

const sf::SoundBuffer & ResHandler::getSound(const std::string & path) {
    auto it = sounds.find(path);
    if (it == sounds.end()) {
        const std::string err = "Error: path " + path + "hasn't been loaded.";
        throw std::runtime_error(err);
    }
    return it->second;
}

const sf::Image & ResHandler::getImage(const std::string & path) {
    auto it = images.find(path);
    if (it == images.end()) {
        const std::string err = "Error: path " + path + "hasn't been loaded.";
        throw std::runtime_error(err);
    }
    return it->second;
}

const sf::Font & ResHandler::getFont(const std::string & path) {
    auto it = fonts.find(path);
    if (it == fonts.end()) {
        const std::string err = "Error: path " + path + "hasn't been loaded.";
        throw std::runtime_error(err);
    }
    return it->second;
}

sf::Shader & ResHandler::getShader(const std::string & path) {
    auto it = shaders.find(path);
    if (it == shaders.end()) {
        const std::string err = "Error: path " + path + "hasn't been loaded.";
        throw std::runtime_error(err);
    }
    return it->second;
}

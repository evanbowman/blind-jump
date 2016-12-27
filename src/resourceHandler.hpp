#pragma once

#include "ResourcePath.hpp"
#include "json.hpp"
#include "spriteSheet.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <assert.h>
#include <stdexcept>
#include <utility>

using json = nlohmann::json;

class ResHandler {
public:
    void loadFromJSON(json & manifest);
    const sf::Texture & getTexture(const std::string &);
    const sf::Font & getFont(const std::string &);
    const sf::Image & getImage(const std::string &);
    const sf::SoundBuffer & getSound(const std::string &);
    sf::Shader & getShader(const std::string &);
    void loadSound(const std::string &);
    void loadTexture(const std::string &);
    void loadShader(const std::string &);
    void loadFont(const std::string &);
    void loadImage(const std::string &);
    void addSheet(const std::string &, const SpriteSheet &);
    SpriteSheet & getSheet(const std::string &);

private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, SpriteSheet> sheets;
    std::map<std::string, sf::SoundBuffer> sounds;
    std::map<std::string, sf::Shader> shaders;
    std::map<std::string, sf::Font> fonts;
    std::map<std::string, sf::Image> images;
};

void setgResHandlerPtr(ResHandler *);

ResHandler * getgResHandlerPtr() noexcept;

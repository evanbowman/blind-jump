//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <assert.h>
#include <stdexcept>
#include <utility>
#include "json.hpp"
#include "ResourcePath.hpp"
#include "spriteSheet.hpp"

class ResHandler {
public:
    enum class Shader { color, blur, desaturate, count };
    enum class Font { cornerstone, count };
    enum class Image { soilTileset, grassSet1, grassSet2, icon, count };
    const sf::Texture & getTexture(const std::string &);
    const sf::Font & getFont(ResHandler::Font) const;
    const sf::Image & getImage(ResHandler::Image) const;
    const sf::SoundBuffer & getSound(const std::string &);
    sf::Shader & getShader(ResHandler::Shader);
    void load();
    void loadSound(const std::string &);
    void loadTexture(const std::string &);
    void addSheet(const std::string &, const SpriteSheet &);
    SpriteSheet & getSheet(const std::string &);

private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, SpriteSheet> sheets;
    std::map<std::string, sf::SoundBuffer> sounds;
    std::array<sf::Shader, static_cast<int>(Shader::count)> shaders;
    std::array<sf::Font, static_cast<int>(Font::count)> fonts;
    std::array<sf::Image, static_cast<int>(Image::count)> images;
    void loadShaders(const std::string &);
    void loadFonts(const std::string &);
    void loadImages(const std::string &);
};

void setgResHandlerPtr(ResHandler *);

ResHandler * getgResHandlerPtr() noexcept;

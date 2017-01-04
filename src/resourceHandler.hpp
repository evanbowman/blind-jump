#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <assert.h>
#include <stdexcept>
#include <utility>

#include "ResourcePath.hpp"

class ResHandler {
public:
    enum class Texture {
        gameObjects,
        vignette,
        vignetteShadow,
        lamplight,
        introLevel,
        teleporterGlow,
        introWall,
        redglow,
        blueglow,
        fireExplosionGlow,
        whiteGlow,
        scootShadow,
        teleporterBeamGlow,
        bkgStarsNear,
        bkgStarsFar,
        bkgOrbit,
        introLevelMask,
        powerupSheet,
        count
    };
    enum class Shader { color, blur, desaturate, count };
    enum class Font { cornerstone, count };
    enum class Image { soilTileset, grassSet1, grassSet2, icon, count };
    enum class Sound {
        gunShot,
        creak,
        bite1,
        bite2,
        woosh,
        wooshMono,
        espark,
        silenced,
        laser,
        blast1,
        electricHum,
        footstepDirt1,
        footstepDirt2,
        footstepDirt3,
        footstepDirt4,
        footstepDirt5,
        count
    };
    const sf::Texture & getTexture(ResHandler::Texture) const;
    const sf::Texture & getTexture(int) const;
    const sf::Font & getFont(ResHandler::Font) const;
    const sf::Image & getImage(ResHandler::Image) const;
    const sf::SoundBuffer & getSound(ResHandler::Sound) const;
    sf::Shader & getShader(ResHandler::Shader)
        const; // Exception: shader cannot be a constant reference
    void load();

private:
    mutable std::array<sf::Shader, static_cast<int>(Shader::count)> shaders;
    std::array<sf::Texture, static_cast<int>(Texture::count)> textures;
    std::array<sf::Font, static_cast<int>(Font::count)> fonts;
    std::array<sf::Image, static_cast<int>(Image::count)> images;
    std::array<sf::SoundBuffer, static_cast<int>(Sound::count)> sounds;
    void loadShaders(const std::string &);
    void loadTextures(const std::string &);
    void loadFonts(const std::string &);
    void loadImages(const std::string &);
    void loadSounds(const std::string &);
};

void setgResHandlerPtr(ResHandler *);

ResHandler * getgResHandlerPtr() noexcept;

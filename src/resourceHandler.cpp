//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "resourceHandler.hpp"

static const char * LOAD_FAILURE_MSG = "blindjump [crash]: missing resource";

template<typename T, typename E>
void loadResource(const std::string & str, E id, T & array) {
    int idx = static_cast<int>(id);
    if (!array[idx].loadFromFile(str)) {
        throw std::runtime_error(LOAD_FAILURE_MSG);
    }
}

template<>
void loadResource(const std::string & str, ResHandler::Shader id, std::array<sf::Shader, 3> & shaders) {
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
    loadResource(resPath + "teleporterBeamGlow.png", Texture::teleporterBeamGlow, textures);
    loadResource(resPath + "fireExplosionGlow.png", Texture::fireExplosionGlow, textures);
    loadResource(resPath + "charger_enemy_shadow.png", Texture::scootShadow, textures);
    loadResource(resPath + "vignetteShadow.png", Texture::vignetteShadow, textures);
    loadResource(resPath + "teleporterGlow.png", Texture::teleporterGlow, textures);
    loadResource(resPath + "bkg_stars_distant.png", Texture::bkgStarsFar, textures);
    loadResource(resPath + "introLevelMask.png", Texture::introLevelMask, textures);
    loadResource(resPath + "powerupSheet.png", Texture::powerupSheet, textures);
    loadResource(resPath + "whiteFloorGlow.png", Texture::whiteGlow, textures);
    loadResource(resPath + "gameObjects.png", Texture::gameObjects, textures);
    loadResource(resPath + "blueFloorGlow.png", Texture::blueglow, textures);
    loadResource(resPath + "bkg_stars.png", Texture::bkgStarsNear, textures);
    loadResource(resPath + "vignetteMask.png", Texture::vignette, textures);
    loadResource(resPath + "introLevel.png", Texture::introLevel, textures);
    loadResource(resPath + "redFloorGlow.png", Texture::redglow, textures);
    loadResource(resPath + "lampLight.png", Texture::lamplight, textures);
    loadResource(resPath + "introWall.png", Texture::introWall, textures);
    loadResource(resPath + "bkg_orbit2.png", Texture::bkgOrbit, textures);
    loadResource(resPath + "desaturate.frag", Shader::desaturate, shaders);
    loadResource(resPath + "color.frag", Shader::color, shaders);
    loadResource(resPath + "blur.frag", Shader::blur, shaders);
    loadResource(resPath + "Cornerstone.ttf", Font::cornerstone, fonts);
    loadResource(resPath + "soilTileset.png", Image::soilTileset, images);
    loadResource(resPath + "grassSetEdge.png", Image::grassSet2, images);
    loadResource(resPath + "grassSet.png", Image::grassSet1, images);
    loadResource(resPath + "gameIcon.png", Image::icon, images);
    loadResource(resPath + "gunshot.ogg", Sound::gunShot, sounds);
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

#include "resourceHandler.hpp"

static const char * LOAD_FAILURE_MSG = "blindjump [crash]: missing resource";

template <typename T, typename E>
void loadResource(const std::string & str, E id, T & array) {
    int idx = static_cast<int>(id);
    if (!array[idx].loadFromFile(str)) {
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
    loadTextures(resPath);
    loadFonts(resPath);
    loadImages(resPath);
    loadSounds(resPath);
}

void ResHandler::loadShaders(const std::string & resPath) {
    loadResource(resPath + "shaders/desaturate.frag", Shader::desaturate,
                 shaders);
    loadResource(resPath + "shaders/color.frag", Shader::color, shaders);
    loadResource(resPath + "shaders/blur.frag", Shader::blur, shaders);
}

void ResHandler::loadTextures(const std::string & resPath) {
    loadResource(resPath + "textures/teleporterBeamGlow.png",
                 Texture::teleporterBeamGlow, textures);
    loadResource(resPath + "textures/fireExplosionGlow.png",
                 Texture::fireExplosionGlow, textures);
    loadResource(resPath + "textures/charger_enemy_shadow.png",
                 Texture::scootShadow, textures);
    loadResource(resPath + "textures/vignetteShadow.png",
                 Texture::vignetteShadow, textures);
    loadResource(resPath + "textures/teleporterGlow.png",
                 Texture::teleporterGlow, textures);
    loadResource(resPath + "textures/bkg_stars_distant.png",
                 Texture::bkgStarsFar, textures);
    loadResource(resPath + "textures/introLevelMask.png",
                 Texture::introLevelMask, textures);
    loadResource(resPath + "textures/powerupSheet.png", Texture::powerupSheet,
                 textures);
    loadResource(resPath + "textures/whiteFloorGlow.png", Texture::whiteGlow,
                 textures);
    loadResource(resPath + "textures/gameObjects.png", Texture::gameObjects,
                 textures);
    loadResource(resPath + "textures/blueFloorGlow.png", Texture::blueglow,
                 textures);
    loadResource(resPath + "textures/bkg_stars.png", Texture::bkgStarsNear,
                 textures);
    loadResource(resPath + "textures/vignetteMask.png", Texture::vignette,
                 textures);
    loadResource(resPath + "textures/introLevel.png", Texture::introLevel,
                 textures);
    loadResource(resPath + "textures/redFloorGlow.png", Texture::redglow,
                 textures);
    loadResource(resPath + "textures/lampLight.png", Texture::lamplight,
                 textures);
    loadResource(resPath + "textures/introWall.png", Texture::introWall,
                 textures);
    loadResource(resPath + "textures/bkg_orbit2.png", Texture::bkgOrbit,
                 textures);
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

void ResHandler::loadSounds(const std::string & resPath) {
    loadResource(resPath + "sounds/gunshot.ogg", Sound::gunShot, sounds);
    loadResource(resPath + "sounds/creak.ogg", Sound::creak, sounds);
    loadResource(resPath + "sounds/bite-small.wav", Sound::bite1, sounds);
    loadResource(resPath + "sounds/bite-small3.wav", Sound::bite2, sounds);
    loadResource(resPath + "sounds/woosh.ogg", Sound::woosh, sounds);
    loadResource(resPath + "sounds/wooshMono.ogg", Sound::wooshMono, sounds);
    loadResource(resPath + "sounds/espark.ogg", Sound::espark, sounds);
    loadResource(resPath + "sounds/silenced.ogg", Sound::silenced, sounds);
    loadResource(resPath + "sounds/laser.ogg", Sound::laser, sounds);
    loadResource(resPath + "sounds/blast1.ogg", Sound::blast1, sounds);
    loadResource(resPath + "sounds/electricHum.ogg", Sound::electricHum,
                 sounds);
    loadResource(resPath + "sounds/footstepDirt1.ogg", Sound::footstepDirt1, sounds);
    loadResource(resPath + "sounds/footstepDirt2.ogg", Sound::footstepDirt2, sounds);
    loadResource(resPath + "sounds/footstepDirt3.ogg", Sound::footstepDirt3, sounds);
    loadResource(resPath + "sounds/footstepDirt4.ogg", Sound::footstepDirt4, sounds);
    loadResource(resPath + "sounds/footstepDirt5.ogg", Sound::footstepDirt5, sounds);
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

static ResHandler * resHandlerPtr;

void setgResHandlerPtr(ResHandler * addr) {
    assert(!::resHandlerPtr);
    ::resHandlerPtr = addr;
}

ResHandler * getgResHandlerPtr() noexcept { return ::resHandlerPtr; }

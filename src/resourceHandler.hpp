//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <utility>
#include <array>
#include <stdexcept>
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
		powerupSheet
	};
	enum class Shader {
		color,
		blur,
		desaturate
	};
	enum class Font {
		cornerstone
	};
	enum class Image {
		soilTileset, grassSet1, grassSet2, icon
	};
	enum class Sound {
		gunShot
	};
	enum class Music {
		// TODO...
	};
	const sf::Texture & getTexture(ResHandler::Texture) const;
	const sf::Texture & getTexture(int) const;
	const sf::Font & getFont(ResHandler::Font) const;
	const sf::Image & getImage(ResHandler::Image) const;
	const sf::SoundBuffer & getSound(ResHandler::Sound) const;
	sf::Shader & getShader(ResHandler::Shader) const; // Exception: shader cannot be a constant reference
	void load();
	
private:
	enum resrcCnts {
		numTextures = 18,
		numShaders = 3,
		numFonts = 1,
		numImages = 4,
		numSounds = 1
	};
	mutable std::array<sf::Shader, numShaders> shaders;
	std::array<sf::Texture, numTextures> textures;
	std::array<sf::Font, numFonts> fonts;
	std::array<sf::Image, numImages> images;
	std::array<sf::SoundBuffer, numSounds> sounds;
};

extern ResHandler * resHandlerPtr;

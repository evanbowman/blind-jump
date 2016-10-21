//========================================================================//
// Copyright (C) 2016 Evan Bowman										  //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.			  //
//========================================================================//

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <atomic>
#include <cmath>
#include <mutex>
#include "backgroundHandler.hpp"
#include "effectsController.hpp"
#include "detailController.hpp"
#include "framework/option.hpp"
#include "enemyController.hpp"
#include "soundController.hpp"
#include "inputController.hpp"
#include "resourceHandler.hpp"
#include "tileController.hpp"
#include "userInterface.hpp"
#include "RenderType.hpp"
#include "camera.hpp"
#include "player.hpp"
#include "colors.hpp"
#include "alias.hpp"

class Game {
public:
	enum class TransitionState {
		None,
		ExitBeamEnter,
		ExitBeamInflate,
		ExitBeamDeflate,
		TransitionOut,
		TransitionIn,
		EntryBeamDrop,
		EntryBeamFade
	};
	Game(const sf::Vector2f & viewPort, const sf::Vector2u &, InputController *, ui::Frontend *);
	void update(const sf::Time &);
	void draw(sf::RenderWindow &);
	void nextLevel();
	int getLevel();
	DetailGroup & getDetails();
	enemyController & getEnemyController();
	tileController & getTileController();
	Player & getPlayer();
	EffectGroup & getEffects();
	InputController * getPInput();
	ui::Backend & getUI();
	ui::Frontend * getPUIFrontend();
	Camera & getCamera();
	float windowW;
	float windowH;
	TransitionState transitionState;

private:
	void init();
	InputController * pInput;
	SoundController sounds;
	Player player;
	Camera camera;
	ui::Backend UI;
	tileController tiles;
	EffectGroup effectGroup;
	DetailGroup details;
	enemyController en;
	ui::Frontend * pUiFrontend;
	int level;
	// Stash static rendered frames for efficiency. Preload is for recovery from stash
	bool stashed, preload;
	framework::Sprite vignetteSprite;
	backgroundHandler bkg;
	framework::Sprite vignetteShadowSpr;
	tileController::Tileset set;
	std::vector<framework::Sprite> glowSprs1, glowSprs2;
	sf::Texture beamGlowTxr;
	framework::Sprite beamGlowSpr;
	sf::View worldView, hudView;
	sf::RenderTexture lightingMap;
	sf::RenderTexture target, secondPass, thirdPass, stash;
	sf::RectangleShape transitionShape, beamShape;
	sf::Texture titleTxtr;
	framework::Sprite titleSpr;
	std::vector<std::tuple<framework::Sprite, float, Rendertype, float>> gameObjects;
	std::vector<std::tuple<framework::Sprite, float, Rendertype, float>> gameShadows;
	void updateTransitions(const sf::Time &);
	void drawTransitions(sf::RenderWindow &);
	int_fast64_t timer;
};

// The first room is not procedurally generated so the positions of the walls need to be hard coded
// There may be a more efficient way to store this, but at O2 optimization clang and gcc convert the whole thing to an array of ints
extern const std::array<std::pair<float, float>, 59> levelZeroWalls;

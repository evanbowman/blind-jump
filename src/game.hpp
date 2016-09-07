//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <atomic>
#include <mutex>
#include "backgroundHandler.hpp"
#include "effectsController.hpp"
#include "detailController.hpp"
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
	Game(const sf::Vector2f & viewPort, InputController *, ui::Frontend *);
	void update(sf::Time &);
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
	sf::Sprite vignetteSprite;
	backgroundHandler bkg;
    sf::Sprite vignetteShadowSpr;
	tileController::Tileset set;
	std::vector<sf::Sprite> glowSprs1, glowSprs2;
	sf::Texture beamGlowTxr;
	sf::Sprite beamGlowSpr;
	sf::View worldView, hudView;
	sf::RenderTexture lightingMap;
	sf::RenderTexture target, secondPass, thirdPass, stash;
	sf::RectangleShape transitionShape, beamShape;
	sf::Texture titleTxtr;
	sf::Sprite titleSpr;
	std::vector<std::tuple<sf::Sprite, float, Rendertype, float>> gameObjects;
	std::vector<std::tuple<sf::Sprite, float, Rendertype, float>> gameShadows;
	void updateTransitions(const sf::Time &);
	void drawTransitions(sf::RenderWindow &);
	int_fast64_t timer;
};

// The first room is not procedurally generated so the positions of the walls need to be hard coded
// There may be a more efficient way to store this, but at O2 optimization clang and gcc convert the whole thing to an array of ints
static const std::array<std::pair<float, float>, 59> global_levelZeroWalls {
	{ std::make_pair(-20, 500),
			std::make_pair(-20, 526),
			std::make_pair(-20, 474),
			std::make_pair(-20, 448),
			std::make_pair(-20, 422),
			std::make_pair(-20, 396),
			std::make_pair(-20, 370),
			std::make_pair(-20, 552),
			std::make_pair(-20, 578),
		
			std::make_pair(196, 500),
			std::make_pair(196, 526),
			std::make_pair(196, 474),
			std::make_pair(196, 448),
			std::make_pair(196, 422),
			std::make_pair(196, 396),
			std::make_pair(196, 370),
			std::make_pair(196, 552),
			std::make_pair(196, 578),
		
			std::make_pair(12, 604),
			std::make_pair(44, 604),
			std::make_pair(76, 604),
			std::make_pair(108, 604),
			std::make_pair(140, 604),
			std::make_pair(172, 604),
		
			std::make_pair(12, 370),
			std::make_pair(34, 370),
			std::make_pair(120, 370),
			std::make_pair(152, 370),
			std::make_pair(184, 370),
		
			std::make_pair(34, 344),
			std::make_pair(120, 344),
			std::make_pair(34, 318),
			std::make_pair(120, 318),
			std::make_pair(34, 292),
			std::make_pair(120, 292),
			std::make_pair(34, 266),
			std::make_pair(120, 266),
		
			std::make_pair(12, 266),
			std::make_pair(-20, 266),
			std::make_pair(152, 266),
			std::make_pair(-20, 240),
			std::make_pair(172, 240),
			std::make_pair(-20, 214),
			std::make_pair(172, 214),
			std::make_pair(-20, 188),
			std::make_pair(172, 188),
			std::make_pair(-20, 162),
			std::make_pair(172, 162),
			std::make_pair(-20, 136),
			std::make_pair(172, 136),
			std::make_pair(-20, 110),
			std::make_pair(172, 110),
			std::make_pair(-20, 84),
			std::make_pair(172, 84),
		
			std::make_pair(12, 58),
			std::make_pair(44, 58),
			std::make_pair(76, 58),
			std::make_pair(108, 58),
			std::make_pair(140, 58)}
};

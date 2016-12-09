//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once
#include "RenderType.hpp"
#include "alias.hpp"
#include "backgroundHandler.hpp"
#include "camera.hpp"
#include "colors.hpp"
#include "detailGroup.hpp"
#include "effectsController.hpp"
#include "enemyController.hpp"
#include "framework/option.hpp"
#include "inputController.hpp"
#include "player.hpp"
#include "resourceHandler.hpp"
#include "soundController.hpp"
#include "tileController.hpp"
#include "userInterface.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GfxContext.hpp"
#include <atomic>
#include <cmath>
#include <mutex>

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
    Game(const sf::Vector2f & viewPort, InputController *, ui::Frontend *, sf::RenderWindow *);
    void update(const sf::Time &);
    void draw(sf::RenderWindow &);
    void nextLevel();
    int getLevel();
    DetailGroup & getDetails();
    enemyController & getEnemyController();
    tileController & getTileController();
    Player & getPlayer();
    EffectGroup & getEffects();
    SoundController & getSounds();
    InputController * getPInput();
    ui::Backend & getUI();
    ui::Frontend * getPUIFrontend();
    Camera & getCamera();
    sf::Vector2f viewPort;
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
    DetailGroup detailGroup;
    enemyController en;
    ui::Frontend * pUiFrontend;
    std::mutex overworldMutex, UIMutex, transitionMutex;
    int level;
    bool stashed, preload;
    sf::Sprite vignetteSprite;
    backgroundHandler bkg;
    sf::Sprite vignetteShadowSpr;
    tileController::Tileset set;
    GfxContext gfxContext;
    sf::Sprite beamGlowSpr;
    sf::View worldView, hudView;
    sf::RenderTexture lightingMap;
    sf::RenderTexture target, secondPass, thirdPass, stash;
    sf::RectangleShape transitionShape, beamShape;
    void updateTransitions(const sf::Time &);
    void drawTransitions(sf::RenderWindow &);
    int_fast64_t timer;
};

// The first room is not procedurally generated so the positions of the walls
// need to be hard coded
// There may be a more efficient way to store this, but at O2 optimization clang
// and gcc convert the whole thing to an array of longs
extern const std::array<std::pair<float, float>, 59> levelZeroWalls;

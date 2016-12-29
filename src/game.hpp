#pragma once
#include "Entity.hpp"
#include "GfxContext.hpp"
#include "LightSource.hpp"
#include "LuaProvider.hpp"
#include "RenderType.hpp"
#include "alias.hpp"
#include "background.hpp"
#include "camera.hpp"
#include "framework/option.hpp"
#include "inputController.hpp"
#include "resourceHandler.hpp"
#include "soundController.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <atomic>
#include <cmath>
#include <mutex>
#include <thread>

using EntityTable = std::map<std::string, std::list<EntityRef>>;

struct ConfigData {
    sf::Vector2f drawableArea;
    bool enableVsync;
    bool showMouse;
    int framerateLimit;
};

class Game {
public:
    Game(const ConfigData &);
    void updateLogic(LuaProvider &);
    void updateGraphics();
    void eventLoop();
    SoundController & getSounds();
    InputController & getInputController();
    Camera & getCamera();
    BackgroundController & getBackground();
    EntityTable & getEntityTable();
    ResHandler & getResHandler();
    sf::RenderWindow & getWindow();
    const sf::Time & getElapsedTime();
    void setElapsedTime(const sf::Time &);
    void init();
    bool hasSlept() const;
    void clearSleptFlag();
    void setSleep(const std::chrono::microseconds & time);
    std::vector<Light> & getLights();
    void setNaturalLight(const sf::Color &);

private:
    sf::Vector2f m_drawableArea;
    EntityTable m_entityTable;
    std::vector<Light> m_lights;
    ResHandler m_resHandler;
    bool m_slept;
    sf::RenderWindow m_window;
    sf::Time m_elapsedTime;
    BackgroundController m_background;
    InputController m_input;
    SoundController m_sounds;
    Camera m_camera;
    bool m_hasFocus;
    std::mutex m_mutex;
    sf::Sprite m_vignetteSprite;
    sf::Sprite m_vignetteShadowSpr;
    GfxContext m_gfxContext;
    sf::View m_worldView, m_hudView;
    sf::RenderTexture m_lightingMap, m_target;
    sf::Color m_naturalLight;
};

// The first room is not procedurally generated so the positions of the walls
// need to be hard coded
// There may be a more efficient way to store this, but at O2 optimization clang
// and gcc convert the whole thing to an array of longs
extern const std::array<std::pair<float, float>, 59> levelZeroWalls;

// Foreign function interface for lua requires a pointer
// to an instance of the game to be accessible...
void setgGamePtr(Game *);
Game * getgGamePtr();

inline ConfigData getConfig(lua_State * state) {
    lua_getglobal(state, "getConf");
    if (lua_pcall(state, 0, 1, 0) != 0) {
        throw std::runtime_error(lua_tostring(state, -1));
    }
    lua_pushstring(state, "width");
    lua_gettable(state, -2);
    float width = lua_tonumber(state, -1);
    lua_pop(state, 1);
    lua_pushstring(state, "height");
    lua_gettable(state, -2);
    float height = lua_tonumber(state, -1);
    lua_pop(state, 2);
    return ConfigData{{width, height}};
}

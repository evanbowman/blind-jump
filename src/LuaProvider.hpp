#include <cassert>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

struct ConfigResults {
    sf::Vector2f drawableArea;
    bool enableVsync;
    bool showMouse;
    int framerateLimit;
};

class LuaProvider {
public:
    LuaProvider();
    ~LuaProvider();
    void runFromFile(const std::string & path);
    ConfigResults getConf();
    LuaProvider(const LuaProvider &) = delete;
    LuaProvider & operator=(const LuaProvider &) = delete;
private:
    lua_State * m_state;
};

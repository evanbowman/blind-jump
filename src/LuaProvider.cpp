#include "LuaProvider.hpp"
#include "game.hpp"

// FOREIGN FUNCTION INTERFACE:
//     Provides access to Game data from lua scripts.
extern "C" {
static int getScreenSize(lua_State * state) {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    lua_pushnumber(state, desktop.width);
    lua_pushnumber(state, desktop.height);
    return 2;
}
    
static int registerEnemy(lua_State * state) {
    std::string classname = lua_tostring(state, 1);
    // TODO: create enemy registry entry for classname...
    // Entries:
    //     std::map<std::string, std::vector<Enemy>>
    Game * pGame = getgGamePtr();
    std::cout << classname << std::endl;
    return 0;
}
}

LuaProvider::LuaProvider() : m_state(luaL_newstate()) {
    luaopen_base(m_state);
    luaopen_table(m_state);
    luaopen_io(m_state);
    luaopen_string(m_state);
    luaopen_math(m_state);
    lua_pushcfunction(m_state, getScreenSize);
    lua_setglobal(m_state, "getScreenSize");
    lua_pushcfunction(m_state, registerEnemy);
    lua_setglobal(m_state, "registerEnemy");
}

LuaProvider::~LuaProvider() { lua_close(m_state); }

void LuaProvider::runFromFile(const std::string & path) {
    std::cout << "Compiling script " << path << std::endl;
    if (luaL_loadfile(m_state, path.c_str()) || lua_pcall(m_state, 0, 0, 0)) {
        throw std::runtime_error(lua_tostring(m_state, -1));
    }
}

ConfigData LuaProvider::getConf() {
    const std::string path = resourcePath() + "scripts/conf.lua";
    this->runFromFile(path);
    lua_getglobal(m_state, "getConf");
    if (lua_pcall(m_state, 0, 1, 0) != 0) {
        throw std::runtime_error(lua_tostring(m_state, -1));
    }
    lua_pushstring(m_state, "width");
    lua_gettable(m_state, -2);
    float width = lua_tonumber(m_state, -1);
    lua_pop(m_state, 1);
    lua_pushstring(m_state, "height");
    lua_gettable(m_state, -2);
    float height = lua_tonumber(m_state, -1);
    lua_pop(m_state, 1);
    lua_pushstring(m_state, "vsync");
    lua_gettable(m_state, -2);
    bool vsync = lua_toboolean(m_state, -1);
    lua_pop(m_state, 1);
    lua_pushstring(m_state, "showCursor");
    lua_gettable(m_state, -2);
    bool showCursor = lua_toboolean(m_state, -1);
    lua_pop(m_state, 1);
    lua_pushstring(m_state, "framerateLimit");
    lua_gettable(m_state, -2);
    int framerateLimit = lua_tointeger(m_state, -1);
    lua_pop(m_state, 2);
    return ConfigData{{width, height}, vsync, showCursor, framerateLimit};
}

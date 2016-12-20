#include "LuaProvider.hpp"
#include "game.hpp"

// GAME API
//     Provides access to Game data from lua scripts.
extern "C" {
static const luaL_Reg gameModFuncs[] = {
    {"getScreenSize",
     [](lua_State * state) -> int {
         auto desktop = sf::VideoMode::getDesktopMode();
         lua_pushnumber(state, desktop.width);
         lua_pushnumber(state, desktop.height);
         return 2;
     }},
    {"registerClass",
     [](lua_State * state) -> int {
         const std::string classname = lua_tostring(state, 1);
         Game * pGame = getgGamePtr();
         pGame->getEntityTable()[classname] = {};
         return 0;
     }},
    {"getDeltaTime",
     [](lua_State * state) -> int {
         Game * pGame = getgGamePtr();
         const sf::Time & elapsed = pGame->getElapsedTime();
         lua_pushnumber(state, elapsed.asMicroseconds());
         return 1;
     }},
    {"createInstance", [](lua_State * state) -> int {
         const std::string classname = lua_tostring(state, 1);
         Game * pGame = getgGamePtr();
         auto & entityTable = pGame->getEntityTable();
         if (entityTable.find(classname) == entityTable.end()) {
             std::string errorMsg =
                 "Error: unregistered classname " + classname;
             throw std::runtime_error(errorMsg);
         }
         auto & vec = pGame->getEntityTable()[classname];
         vec.emplace_back();
         lua_pushlightuserdata(state, (void *)(&(*vec.end())));
         return 1;
     }}};

static int luaopen_game(lua_State * state) {
    lua_newtable(state);
    luaL_setfuncs(state, gameModFuncs, 0);
    lua_setglobal(state, "game");
    return 1;
}
}

LuaProvider::LuaProvider() : m_state(luaL_newstate()) {
    luaopen_base(m_state);
    luaopen_table(m_state);
    luaopen_io(m_state);
    luaopen_string(m_state);
    luaopen_math(m_state);
    luaopen_game(m_state);
}

LuaProvider::~LuaProvider() { lua_close(m_state); }

void LuaProvider::runScriptFromFile(const std::string & path) {
    if (luaL_loadfile(m_state, path.c_str()) || lua_pcall(m_state, 0, 0, 0)) {
        throw std::runtime_error(lua_tostring(m_state, -1));
    }
}

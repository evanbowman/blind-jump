#include "LuaProvider.hpp"
#include "game.hpp"

// GAME API
//     Provides access to Game data from lua scripts.
extern "C" {
    static int getScreenSize(lua_State * state) {
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	lua_pushnumber(state, desktop.width);
	lua_pushnumber(state, desktop.height);
	return 2;
    }
    
    static int registerEnemyClass(lua_State * state) {
	std::string classname = lua_tostring(state, 1);
	Game * pGame = getgGamePtr();
	pGame->getEnemyTable()[classname] = {};
	return 0;
    }

    static int getDeltaTime(lua_State * state) {
	Game * pGame = getgGamePtr();
	const sf::Time & elapsed = pGame->getElapsedTime();
	lua_pushnumber(state, elapsed.asMicroseconds());
	return 1;
    }

    static const luaL_Reg gameModFuncs[] = {
	{"getScreenSize", getScreenSize},
	{"registerEnemyClass", registerEnemyClass},
	{"getDeltaTime", getDeltaTime}
    };

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

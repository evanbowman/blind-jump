#include "LuaProvider.hpp"
#include "game.hpp"

// GAME API
//     Provides access to Game data from lua scripts.
//     TODO: create nested tables, e.g.: entity.create, entity.getPosition
extern "C" {
    static const luaL_Reg systemModFuncs[] = {
	{"getScreenSize",
	 [](lua_State * state) -> int {
	     auto desktop = sf::VideoMode::getDesktopMode();
	     lua_pushnumber(state, desktop.width);
	     lua_pushnumber(state, desktop.height);
	     return 2;
	 }},
	{"getDeltaTime",
	 [](lua_State * state) -> int {
	     Game * pGame = getgGamePtr();
	     const sf::Time & elapsed = pGame->getElapsedTime();
	     lua_pushnumber(state, elapsed.asMicroseconds());
	     return 1;
	 }},
	{"registerClass",
	 [](lua_State * state) -> int {
	     const std::string classname = lua_tostring(state, 1);
	     Game * pGame = getgGamePtr();
	     pGame->getEntityTable()[classname] = {};
	     return 0;
	 }}
    };

    static const luaL_Reg entityModFuncs[] = {
	{"create",
	 [](lua_State * state) -> int {
	     const std::string classname = lua_tostring(state, 1);
	     Game * pGame = getgGamePtr();
	     auto & entityTable = pGame->getEntityTable();
	     if (entityTable.find(classname) == entityTable.end()) {
		 std::string errorMsg =
		     "Error: unregistered classname " + classname;
		 throw std::runtime_error(errorMsg);
	     }
	     auto & vec = pGame->getEntityTable()[classname];
	     vec.push_back(std::make_shared<Entity>());
	     lua_getglobal(state, "classes");
	     if (!lua_istable(state, -1)) {
		 throw std::runtime_error("Error: missing classtable");
	     }
	     lua_getfield(state, -1, classname.c_str());
	     if (!lua_istable(state, -1)) {
		 const std::string err = "Error: classtable field " +
		     classname + " is not a table";
		 throw std::runtime_error(err);
	     }
	     lua_getfield(state, -1, "OnCreate");
	     if (!lua_isfunction(state, -1)) {
		 const std::string err = 
		     "Error: missing or malformed OnUpdate for class " +
		     classname;
	     }
	     lua_pushlightuserdata(state, (void *)(&vec.back()));
	     if (lua_pcall(state, 1, 0, 0)) {
		 throw std::runtime_error(lua_tostring(state, -1));
	     }
	     lua_pushlightuserdata(state, (void *)(&vec.back()));
	     return 1;
	 }},
	{"getPosition",
	 [](lua_State * state) -> int {
	     void * entity = lua_touserdata(state, 1);
	     auto & pos = (*static_cast<std::shared_ptr<Entity> *>(entity))
		 ->getPosition();
	     lua_pushnumber(state, pos.x);
	     lua_pushnumber(state, pos.y);
	     return 2;
	 }},
	{"setPosition",
	 [](lua_State * state) -> int {
	     void * entity = lua_touserdata(state, 1);
	     float x = lua_tonumber(state, 2);
	     float y = lua_tonumber(state, 3);
	     (*static_cast<std::shared_ptr<Entity> *>(entity))->
		 setPosition(sf::Vector2f(x, y));
	     return 0;
	 }},
	{"setKillFlag",
	 [](lua_State * state) -> int {
	     void * entity = lua_touserdata(state, 1);
	     (*static_cast<std::shared_ptr<Entity> *>(entity))->setKillFlag(true);
	     return 0;
	 }},
	{"getKillFlag",
	 [](lua_State * state) -> int {
	     void * entity = lua_touserdata(state, 1);
	     bool flag = (*static_cast<std::shared_ptr<Entity> *>(entity))->getKillFlag();
	     lua_pushboolean(state, flag);
	     return 1;
	 }},
	{"emitSound",
	 [](lua_State * state) -> int {
	     auto entity = static_cast<std::shared_ptr<Entity> *>(lua_touserdata(state, 1));
	     const char * soundName = lua_tostring(state, 2);
	     const float minDist = lua_tonumber(state, 3);
	     const float attenuation = lua_tonumber(state, 4);
	     const bool loop = lua_toboolean(state, 5);
	     Game * pGame = getgGamePtr();
	     auto & sounds = pGame->getSounds();
	     //  TODO: sounds.play(...) <-- needs new def to work with strings...
	     return 0;
	 }},
	{"setState",
	 [](lua_State * state) -> int {
	     auto entity = (*static_cast<std::shared_ptr<Entity> *>(lua_touserdata(state, 1)));
	     entity->setState(lua_tostring(state, 2));
	     return 0;
	 }},
	{"getState",
	 [](lua_State * state) -> int {
	     auto entity = (*static_cast<std::shared_ptr<Entity> *>(lua_touserdata(state, 1)));
	     lua_pushstring(state, entity->getState().c_str());
	     return 1;
	 }},
	{"getTimer",
	 [](lua_State * state) -> int {
	     auto entity = (*static_cast<std::shared_ptr<Entity> *>(lua_touserdata(state, 1)));
	     const uint64_t val = entity->getTimer(lua_tointeger(state, 2));
	     lua_pushinteger(state, val);
	     return 1;
	 }},
	{"setTimer",
	 [](lua_State * state) -> int {
	     auto entity = (*static_cast<std::shared_ptr<Entity> *>(lua_touserdata(state, 1)));
	     entity->setTimer(lua_tointeger(state, 2), lua_tointeger(state, 3));
	     return 0;
	 }}
    };

    static int luaopen_system(lua_State * state) {
	lua_newtable(state);
	luaL_setfuncs(state, systemModFuncs, 0);
	lua_setglobal(state, "system");
	return 1;
    }

    static int luaopen_entity(lua_State * state) {
	lua_newtable(state);
	luaL_setfuncs(state, entityModFuncs, 0);
	lua_setglobal(state, "entity");
	return 1;
    }
}

LuaProvider::LuaProvider() : m_state(luaL_newstate()) {
    luaopen_base(m_state);
    luaopen_table(m_state);
    luaopen_io(m_state);
    luaopen_string(m_state);
    luaopen_math(m_state);
    luaopen_system(m_state);
    luaopen_entity(m_state);
    lua_newtable(m_state);
    lua_setglobal(m_state, "classes");
}

LuaProvider::~LuaProvider() { lua_close(m_state); }

void LuaProvider::runScriptFromFile(const std::string & path) {
    if (luaL_loadfile(m_state, path.c_str()) || lua_pcall(m_state, 0, 0, 0)) {
        throw std::runtime_error(lua_tostring(m_state, -1));
    }
}

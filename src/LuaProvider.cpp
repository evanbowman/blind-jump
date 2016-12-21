#include "LuaProvider.hpp"
#include "game.hpp"

// GAME API
//     Provides access to Game data from lua scripts.
//     TODO: create nested tables, e.g.: instance.create, instance.getPosition
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
	 }},
	{"loadSound",
	 [](lua_State * state) -> int {
	     auto resources = getgResHandlerPtr();
	     resources->loadSound(lua_tostring(state, 1));
	     return 0;
	 }},
	{"loadTexture",
	 [](lua_State * state) -> int {
	     auto resources = getgResHandlerPtr();
	     resources->loadTexture(lua_tostring(state, 1));
	     return 0;
	 }}
    };

    static EntityRef * createEntity(lua_State * state,
				    const std::string & classname) {
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
	return &vec.back();
    }
    
    static const luaL_Reg instanceModFuncs[] = {
	{"new",
	 [](lua_State * state) -> int {
	     const std::string classname = lua_tostring(state, 1);
	     EntityRef * created = createEntity(state, classname);
	     lua_pushlightuserdata(state, (void *)created);
	     return 1;
	 }},
	{"getPosition",
	 [](lua_State * state) -> int {
	     void * entity = lua_touserdata(state, 1);
	     auto & pos = (*static_cast<EntityRef *>(entity))
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
	     (*static_cast<EntityRef *>(entity))->
		 setPosition(sf::Vector2f(x, y));
	     return 0;
	 }},
	{"setKillFlag",
	 [](lua_State * state) -> int {
	     void * entity = lua_touserdata(state, 1);
	     (*static_cast<EntityRef *>(entity))->setKillFlag(true);
	     return 0;
	 }},
	{"getKillFlag",
	 [](lua_State * state) -> int {
	     void * entity = lua_touserdata(state, 1);
	     bool flag = (*static_cast<EntityRef *>(entity))->getKillFlag();
	     lua_pushboolean(state, flag);
	     return 1;
	 }},
	{"emitSound",
	 [](lua_State * state) -> int {
	     auto entity = static_cast<EntityRef *>(lua_touserdata(state, 1));
	     const char * soundName = lua_tostring(state, 2);
	     const float minDist = lua_tonumber(state, 3);
	     const float attenuation = lua_tonumber(state, 4);
	     Game * pGame = getgGamePtr();
	     auto & sounds = pGame->getSounds();
	     sounds.play(soundName, *entity, minDist, attenuation, false);
	     return 0;
	 }},
	{"setState",
	 [](lua_State * state) -> int {
	     auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
	     entity->setState(lua_tostring(state, 2));
	     return 0;
	 }},
	{"getState",
	 [](lua_State * state) -> int {
	     auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
	     lua_pushstring(state, entity->getState().c_str());
	     return 1;
	 }},
	{"getCounter",
	 [](lua_State * state) -> int {
	     auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
	     const uint64_t val = entity->getCounter(lua_tointeger(state, 2));
	     lua_pushinteger(state, val);
	     return 1;
	 }},
	{"setCounter",
	 [](lua_State * state) -> int {
	     auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
	     entity->setCounter(lua_tointeger(state, 2), lua_tointeger(state, 3));
	     return 0;
	 }},
	{"setFrame",
	 [](lua_State * state) -> int {
	     auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
	     const int frameno = lua_tointeger(state, 2);
	     entity->setFrameIndex(frameno);
	     return 0;
	 }},
	{"getFrame",
	 [](lua_State * state) -> int {
	     auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
	     const int frameno = entity->getFrameIndex();
	     lua_pushinteger(state, frameno);
	     return 1;
	 }}
    };

    static int luaopen_system(lua_State * state) {
	lua_newtable(state);
	luaL_setfuncs(state, systemModFuncs, 0);
	lua_setglobal(state, "system");
	return 1;
    }

    static int luaopen_instance(lua_State * state) {
	lua_newtable(state);
	luaL_setfuncs(state, instanceModFuncs, 0);
	lua_setglobal(state, "instance");
	return 1;
    }
}

LuaProvider::LuaProvider() : m_state(luaL_newstate()) {
    luaL_openlibs(m_state);
    luaopen_system(m_state);
    luaopen_instance(m_state);
    lua_newtable(m_state);
    lua_setglobal(m_state, "classes");
    lua_getglobal(m_state, "package");
    lua_getfield(m_state, -1, "path");
    std::string currentPath = lua_tostring(m_state, -1);
    currentPath.append(";");
    currentPath += resourcePath() + "scripts/?.lua";
    lua_pop(m_state, 1);
    lua_pushstring(m_state, currentPath.c_str());
    lua_setfield(m_state, -2, "path");
    lua_pop(m_state, 1);
}

LuaProvider::~LuaProvider() { lua_close(m_state); }

void LuaProvider::runScriptFromFile(const std::string & path) {
    if (luaL_loadfile(m_state, path.c_str()) || lua_pcall(m_state, 0, 0, 0)) {
        throw std::runtime_error(lua_tostring(m_state, -1));
    }
}

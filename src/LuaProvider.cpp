#include "LuaProvider.hpp"
#include "game.hpp"

// GAME API
//     Provides access to Game data from lua scripts.
extern "C" {
    static const std::string paramErr =
	"Error: wrong number of parameters for function ";
    
    static const luaL_Reg systemLibFuncs[] = {
	{"getScreenSize",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 0) {
		 throw std::runtime_error(paramErr + "system.getScreenSize");
	     }
	     auto desktop = sf::VideoMode::getDesktopMode();
	     lua_pushnumber(state, desktop.width);
	     lua_pushnumber(state, desktop.height);
	     return 2;
	 }},
	{"getDeltaTime",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 0) {
		 throw std::runtime_error(paramErr + "system.getDeltaTime");
	     }
	     Game * pGame = getgGamePtr();
	     const sf::Time & elapsed = pGame->getElapsedTime();
	     lua_pushnumber(state, elapsed.asMicroseconds());
	     return 1;
	 }},
	{"random",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 2) {
		 throw std::runtime_error(paramErr + "system.random");
	     }
	     int upper = lua_tointeger(state, 1);
	     int lower = lua_tointeger(state, 2);
	     int result = rng::random(upper, lower);
	     lua_pushinteger(state, result);
	     return 1;
	 }},
	{"sleep",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 1) {
		 throw std::runtime_error(paramErr + "system.sleep");
	     }
	     getgGamePtr()->setSleep(
				     std::chrono::microseconds(lua_tointeger(state, 1)));
	     return 0;
	 }},
	{"quit",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 0) {
		 throw std::runtime_error(paramErr + "system.quit");
	     }
	     // The engine code is multithreaded with a lots of locks, threads,
	     // and other resources (e.g. the Lua state) that need to be
	     // deallocated correctly. The codebase uses RAII for ALL resources,
	     // so letting an exception hit the top level is actually a clean
	     // way to quit a game.
	     throw ShutdownSignal();
	     return 0;
	 }},
	{}};
    
    static const luaL_Reg cameraLibFuncs[] = {
	{"setTarget",
	 [](lua_State * state) {
	     if (lua_gettop(state) != 1) {
		 throw std::runtime_error(paramErr + "camera.setTarget");
	     }
	     auto entity = static_cast<EntityRef *>(lua_touserdata(state, 1));
	     getgGamePtr()->getCamera().setTarget(*entity);
	     return 0;
	 }},
	{"displaceFromTarget",
	 [](lua_State * state) {
	     if (lua_gettop(state) != 2) {
		 throw std::runtime_error(paramErr + "camera.displaceFromTarget");
	     }
	     const float x = lua_tonumber(state, 1);
	     const float y = lua_tonumber(state, 2);
	     getgGamePtr()->getCamera().setOffset({x, y});
	     return 0;
	 }},
	{"getViewportSize",
	 [](lua_State * state) {
	     if (lua_gettop(state) != 0) {
		 throw std::runtime_error(paramErr + "camera.getViewportSize");
	     }
	     auto viewsize =
		 getgGamePtr()->getCamera().getOverworldView().getSize();
	     lua_pushnumber(state, viewsize.x);
	     lua_pushnumber(state, viewsize.y);
	     return 2;
	 }},
	{}};

    static const luaL_Reg lightLibFuncs[] = {
	{"create",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 3) {
		 throw std::runtime_error(paramErr + "light.create");
	     }
	     const std::string sheetName = lua_tostring(state, 1);
	     const float x = lua_tonumber(state, 2);
	     const float y = lua_tonumber(state, 3);
	     Game * pGame = getgGamePtr();
	     ResHandler & resources = pGame->getResHandler();
	     auto & lights = pGame->getLights();
	     lights.emplace_back();
	     lights.back().setSheet(&resources.getSheet(sheetName));
	     lights.back().setPosition({x, y});
	     lua_pushlightuserdata(state, (void *)&lights.back());
	     return 1;
	 }},
	{"setOrigin",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 3) {
		 throw std::runtime_error(paramErr + "light.setOrigin");
	     }
	     Light * light = reinterpret_cast<Light *>(lua_touserdata(state, 1));
	     const float xOrigin = lua_tonumber(state, 2);
	     const float yOrigin = lua_tonumber(state, 3);
	     light->setOrigin({xOrigin, yOrigin});
	     return 0;
	 }},
	{"destroy",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 1) {
		 throw std::runtime_error(paramErr + "light.destroy");
	     }
	     Light * light = reinterpret_cast<Light *>(lua_touserdata(state, 1));
	     light->setKillFlag();
	     return 0;
	 }},
	{"listAll",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 0) {
		 throw std::runtime_error(paramErr + "light.listAll");
	     }
	     Game * pGame = getgGamePtr();
	     auto & lights = pGame->getLights();
	     lua_newtable(state);
	     for (int i = 0; i < lights.size(); ++i) {
		 lua_pushnumber(state, i);
		 lua_pushlightuserdata(state, &lights[i]);
		 lua_settable(state, -3);
	     }
	     return 1;
	 }},
	{}
    };

    static const luaL_Reg inputLibFuncs[] = {
	{"keyPressed",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 1) {
		 throw std::runtime_error(paramErr + "input.keyPressed");
	     }
	     int keyCode = lua_tointeger(state, 1);
	     Game * pGame = getgGamePtr();
	     InputController & input = pGame->getInputController();
	     lua_pushboolean(state, input.getKeyState(keyCode) == 1);
	     return 1;
	 }},
	{}};

    static const luaL_Reg entityLibFuncs[] = {
	{"create",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 3) {
		 throw std::runtime_error(paramErr + "entity.create");
	     }
	     const std::string classname = lua_tostring(state, 1);
	     const float x = lua_tonumber(state, 2);
	     const float y = lua_tonumber(state, 3);
	     Game * pGame = getgGamePtr();
	     auto & entityTable = pGame->getEntityTable();
	     auto & vec = pGame->getEntityTable()[classname];
	     vec.push_back(std::make_shared<Entity>());
	     vec.back()->setPosition(sf::Vector2f(x, y));
	     lua_getglobal(state, "classes");
	     if (!lua_istable(state, -1)) {
		 throw std::runtime_error("Error: missing classtable");
	     }
	     lua_getfield(state, -1, classname.c_str());
	     if (!lua_istable(state, -1)) {
		 const std::string err =
		     "Error: classtable field " + classname + " is not a table";
		 throw std::runtime_error(err);
	     }
	     lua_getfield(state, -1, "onCreate");
	     if (!lua_isfunction(state, -1)) {
		 const std::string err =
		     "Error: missing or malformed OnUpdate for class " + classname;
	     }
	     lua_pushlightuserdata(state, (void *)(&vec.back()));
	     if (lua_pcall(state, 1, 0, 0)) {
		 throw std::runtime_error(lua_tostring(state, -1));
	     }
	     lua_pushlightuserdata(state, (void *)&vec.back());
	     return 1;
	 }},
	{"getPosition",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 1) {
		 throw std::runtime_error(paramErr + "entity.getPosition");
	     }
	     void * entity = lua_touserdata(state, 1);
	     auto & pos = (*static_cast<EntityRef *>(entity))->getPosition();
	     lua_pushnumber(state, pos.x);
	     lua_pushnumber(state, pos.y);
	     return 2;
	 }},
	{"setPosition",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 3) {
		 throw std::runtime_error(paramErr + "entity.setPosition");
	     }
	     void * entity = lua_touserdata(state, 1);
	     float x = lua_tonumber(state, 2);
	     float y = lua_tonumber(state, 3);
	     (*static_cast<EntityRef *>(entity))->setPosition(sf::Vector2f(x, y));
	     return 0;
	 }},
	{"destroy",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 1) {
		 throw std::runtime_error(paramErr + "entity.destroy");
	     }
	     auto entity = static_cast<EntityRef *>(lua_touserdata(state, 1));
	     (*entity)->setKillFlag();
	     return 0;
	 }},
	{"setField",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 3) {
		 throw std::runtime_error(paramErr + "entity.setField");
	     }
	     auto entity = static_cast<EntityRef *>(lua_touserdata(state, 1));
	     const int varIndex = lua_tointeger(state, 2);
	     auto & members = (*entity)->getMemberTable();
	     if (members.find(varIndex) != members.end()) {
		 luaL_unref(state, LUA_REGISTRYINDEX, members[varIndex]);
	     }
	     lua_pushvalue(state, 3);
	     members[varIndex] = luaL_ref(state, LUA_REGISTRYINDEX);
	     return 0;
	 }},
	{"getField",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 2) {
		 throw std::runtime_error(paramErr + "entity.getField");
	     }
	     auto entity = static_cast<EntityRef *>(lua_touserdata(state, 1));
	     const int varIndex = lua_tointeger(state, 2);
	     auto & members = (*entity)->getMemberTable();
	     if (members.find(varIndex) == members.end()) {
		 const std::string err =
		     "Error: member " + std::to_string(varIndex) + " lookup failed";
		 throw std::runtime_error(err);
	     }
	     int ref = members[varIndex];
	     lua_rawgeti(state, LUA_REGISTRYINDEX, ref);
	     return 1;
	 }},
	{"emitSound",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 4) {
		 throw std::runtime_error(paramErr + "entity.emitSound");
	     }
	     auto entity = static_cast<EntityRef *>(lua_touserdata(state, 1));
	     const char * soundName = lua_tostring(state, 2);
	     const float minDist = lua_tonumber(state, 3);
	     const float attenuation = lua_tonumber(state, 4);
	     Game * pGame = getgGamePtr();
	     auto & sounds = pGame->getSounds();
	     sounds.play(soundName, *entity, minDist, attenuation, false);
	     return 0;
	 }},
	{"setKeyframe",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 2) {
		 throw std::runtime_error(paramErr + "entity.setKeyframe");
	     }
	     auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
	     const int frameno = lua_tointeger(state, 2);
	     entity->setKeyframe(frameno);
	     return 0;
	 }},
	{"getKeyframe",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 1) {
		 throw std::runtime_error(paramErr + "entity.getKeyframe");
	     }
	     auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
	     const int frameno = entity->getKeyframe();
	     lua_pushinteger(state, frameno);
	     return 1;
	 }},
	{"setSprite",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 2) {
		 throw std::runtime_error(paramErr + "entity.setSprite");
	     }
	     auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
	     const std::string sheetName = lua_tostring(state, 2);
	     auto resources = getgResHandlerPtr();
	     entity->setSheet(&resources->getSheet(sheetName));
	     return 0;
	 }},
	{"setZOrder",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 2) {
		 throw std::runtime_error(paramErr + "entity.setZOrder");
	     }
	     auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
	     const float z = lua_tonumber(state, 2);
	     entity->setZOrder(z);
	     return 0;
	 }},
	{"getZOrder",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 1) {
		 throw std::runtime_error(paramErr + "entity.getZOrder");
	     }
	     auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
	     lua_pushnumber(state, entity->getZOrder());
	     return 1;
	 }},
	{"listAll",
	 [](lua_State * state) -> int {
	     if (lua_gettop(state) != 1) {
		 throw std::runtime_error(paramErr + "entity.listAll");
	     }
	     Game * pGame = getgGamePtr();
	     EntityTable & tab = pGame->getEntityTable();
	     // FIXME: this code is unsafe, map entry may not exist...
	     auto & entityVec = tab[lua_tostring(state, 1)];
	     lua_newtable(state);
	     int i = 0;
	     for (auto & ent : entityVec) {
		 lua_pushnumber(state, i);
		 lua_pushlightuserdata(state, &ent);
		 lua_settable(state, -3);
		 ++i;
	     }
	     return 1;
	 }},
	{}};
}

template <typename M>
static void registerLib(lua_State * state, M * lib, const char * name) {
    lua_newtable(state);
    luaL_setfuncs(state, lib, 0);
    lua_setglobal(state, name);
}

static void registerInputLib(lua_State * state) {
    lua_newtable(state);
    luaL_setfuncs(state, inputLibFuncs, 0);
    lua_newtable(state);
    const auto createBinding =
	[state](const char * keyName, sf::Keyboard::Key code) {
	    lua_pushinteger(state, code);
	    lua_setfield(state, -2, keyName);
	};
    createBinding("left", sf::Keyboard::Left);
    createBinding("right", sf::Keyboard::Right);
    createBinding("up", sf::Keyboard::Up);
    createBinding("down", sf::Keyboard::Down);
    createBinding("a", sf::Keyboard::A);
    createBinding("b", sf::Keyboard::B);
    createBinding("c", sf::Keyboard::C);
    createBinding("d", sf::Keyboard::D);
    createBinding("e", sf::Keyboard::E);
    createBinding("f", sf::Keyboard::F);
    createBinding("g", sf::Keyboard::G);
    createBinding("h", sf::Keyboard::H);
    createBinding("i", sf::Keyboard::I);
    createBinding("j", sf::Keyboard::J);
    createBinding("k", sf::Keyboard::K);
    createBinding("l", sf::Keyboard::L);
    createBinding("m", sf::Keyboard::M);
    createBinding("n", sf::Keyboard::N);
    createBinding("o", sf::Keyboard::O);
    createBinding("p", sf::Keyboard::P);
    createBinding("q", sf::Keyboard::Q);
    createBinding("r", sf::Keyboard::R);
    createBinding("s", sf::Keyboard::S);
    createBinding("t", sf::Keyboard::T);
    createBinding("u", sf::Keyboard::U);
    createBinding("v", sf::Keyboard::V);
    createBinding("w", sf::Keyboard::W);
    createBinding("x", sf::Keyboard::X);
    createBinding("y", sf::Keyboard::Y);
    createBinding("z", sf::Keyboard::Z);
    createBinding("num0", sf::Keyboard::Num0);
    createBinding("num1", sf::Keyboard::Num1);
    createBinding("num2", sf::Keyboard::Num2);
    createBinding("num3", sf::Keyboard::Num3);
    createBinding("num4", sf::Keyboard::Num4);
    createBinding("num5", sf::Keyboard::Num5);
    createBinding("num6", sf::Keyboard::Num6);
    createBinding("num7", sf::Keyboard::Num7);
    createBinding("num8", sf::Keyboard::Num8);
    createBinding("num9", sf::Keyboard::Num9);
    createBinding("esc", sf::Keyboard::Escape);
    createBinding("lctrl", sf::Keyboard::LControl);
    createBinding("lshift", sf::Keyboard::LShift);
    createBinding("lalt", sf::Keyboard::LAlt);
    createBinding("lsuper", sf::Keyboard::LSystem);
    createBinding("rctrl", sf::Keyboard::RControl);
    createBinding("rshift", sf::Keyboard::RShift);
    createBinding("ralt", sf::Keyboard::RAlt);
    createBinding("rsuper", sf::Keyboard::RSystem);
    lua_setfield(state, -2, "key");
    lua_setglobal(state, "input");
}

// ::sandbox contains a safe version of luaL_openlibs
// with the io and os libraries disabled
namespace sandbox {
    static const luaL_Reg loadedlibs[] = {
	{"_G", luaopen_base},
	{LUA_LOADLIBNAME, luaopen_package},
	{LUA_COLIBNAME, luaopen_coroutine},
	{LUA_TABLIBNAME, luaopen_table},
	{LUA_STRLIBNAME, luaopen_string},
	{LUA_MATHLIBNAME, luaopen_math},
	{LUA_UTF8LIBNAME, luaopen_utf8},
	{LUA_DBLIBNAME, luaopen_debug},
	{}
    };

    static void luaL_openlibs(lua_State *L) {
	const luaL_Reg *lib;
	for (lib = loadedlibs; lib->func; lib++) {
	    luaL_requiref(L, lib->name, lib->func, 1);
	    lua_pop(L, 1);
	}
    }
}

LuaProvider::LuaProvider() : m_state(luaL_newstate()) {
    sandbox::luaL_openlibs(m_state);
    registerLib(m_state, systemLibFuncs, "system");
    registerLib(m_state, entityLibFuncs, "entity");
    registerLib(m_state, cameraLibFuncs, "camera");
    registerLib(m_state, lightLibFuncs, "light");
    registerInputLib(m_state);
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
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
    {"random",
     [](lua_State * state) -> int {
         if (lua_gettop(state) != 2) {
             throw std::runtime_error(paramErr + "random");
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
             throw std::runtime_error(paramErr + "sleep");
         }
         getgGamePtr()->setSleep(
             std::chrono::microseconds(lua_tointeger(state, 1)));
         return 0;
     }},
    {"quit",
     [](lua_State * state) -> int {
	 if (lua_gettop(state) != 0) {
	     throw std::runtime_error(paramErr + "quit");
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

static EntityRef * createEntity(lua_State * state,
                                const std::string & classname, const float x,
                                const float y) {
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
    return &vec.back();
}

static const luaL_Reg cameraLibFuncs[] = {
    {"setTarget",
     [](lua_State * state) {
         if (lua_gettop(state) != 1) {
             throw std::runtime_error(paramErr + "setTarget");
         }
         auto entity = static_cast<EntityRef *>(lua_touserdata(state, 1));
         getgGamePtr()->getCamera().setTarget(*entity);
         return 0;
     }},
    {"displaceFromTarget",
     [](lua_State * state) {
         if (lua_gettop(state) != 2) {
             throw std::runtime_error(paramErr + "displaceFromTarget");
         }
         const float x = lua_tonumber(state, 1);
         const float y = lua_tonumber(state, 2);
         getgGamePtr()->getCamera().setOffset({x, y});
         return 0;
     }},
    {"getViewportSize",
     [](lua_State * state) {
         if (lua_gettop(state) != 0) {
             throw std::runtime_error(paramErr + "getViewportSize");
         }
         auto viewsize =
             getgGamePtr()->getCamera().getOverworldView().getSize();
         lua_pushnumber(state, viewsize.x);
         lua_pushnumber(state, viewsize.y);
         return 2;
     }},
    {}};

static const luaL_Reg cameraTransitionLibFuncs[] = {{}};

static const luaL_Reg inputLibFuncs[] = {
    {"left",
     [](lua_State * state) {
         if (lua_gettop(state) != 0) {
             throw std::runtime_error(paramErr + "left");
         }
         InputController & input = getgGamePtr()->getInputController();
         lua_pushboolean(state, input.leftPressed());
         return 1;
     }},
    {"right",
     [](lua_State * state) {
         if (lua_gettop(state) != 0) {
             throw std::runtime_error(paramErr + "left");
         }
         InputController & input = getgGamePtr()->getInputController();
         lua_pushboolean(state, input.rightPressed());
         return 1;
     }},
    {"up",
     [](lua_State * state) {
         if (lua_gettop(state) != 0) {
             throw std::runtime_error(paramErr + "left");
         }
         InputController & input = getgGamePtr()->getInputController();
         lua_pushboolean(state, input.upPressed());
         return 1;
     }},
    {"down",
     [](lua_State * state) {
         if (lua_gettop(state) != 0) {
             throw std::runtime_error(paramErr + "left");
         }
         InputController & input = getgGamePtr()->getInputController();
         lua_pushboolean(state, input.downPressed());
         return 1;
     }},
    {}};

static const luaL_Reg entityLibFuncs[] = {
    {"new",
     [](lua_State * state) -> int {
         if (lua_gettop(state) != 3) {
             throw std::runtime_error(paramErr + "spawn");
         }
         const std::string classname = lua_tostring(state, 1);
         const float x = lua_tonumber(state, 2);
         const float y = lua_tonumber(state, 3);
         EntityRef * created = createEntity(state, classname, x, y);
         lua_pushlightuserdata(state, (void *)created);
         return 1;
     }},
    {"getPosition",
     [](lua_State * state) -> int {
         if (lua_gettop(state) != 1) {
             throw std::runtime_error(paramErr + "getPosition");
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
             throw std::runtime_error(paramErr + "setPosition");
         }
         void * entity = lua_touserdata(state, 1);
         float x = lua_tonumber(state, 2);
         float y = lua_tonumber(state, 3);
         (*static_cast<EntityRef *>(entity))->setPosition(sf::Vector2f(x, y));
         return 0;
     }},
    {"dispose",
     [](lua_State * state) -> int {
         if (lua_gettop(state) != 1) {
             throw std::runtime_error(paramErr + "destroy");
         }
         auto entity = static_cast<EntityRef *>(lua_touserdata(state, 1));
         (*entity)->setKillFlag();
         return 0;
     }},
    {"setField",
     [](lua_State * state) -> int {
         if (lua_gettop(state) != 3) {
             throw std::runtime_error(paramErr + "setField");
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
             throw std::runtime_error(paramErr + "getField");
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
             throw std::runtime_error(paramErr + "emitSound");
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
             throw std::runtime_error(paramErr + "setKeyframe");
         }
         auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
         const int frameno = lua_tointeger(state, 2);
         entity->setKeyframe(frameno);
         return 0;
     }},
    {"getKeyframe",
     [](lua_State * state) -> int {
         if (lua_gettop(state) != 1) {
             throw std::runtime_error(paramErr + "getKeyframe");
         }
         auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
         const int frameno = entity->getKeyframe();
         lua_pushinteger(state, frameno);
         return 1;
     }},
    {"setSprite",
     [](lua_State * state) -> int {
         if (lua_gettop(state) != 2) {
             throw std::runtime_error(paramErr + "setSprite");
         }
         auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
         const std::string sheetName = lua_tostring(state, 2);
         auto resources = getgResHandlerPtr();
         entity->setSheet(&resources->getSheet(sheetName));
         return 0;
     }},
    {"setShadow",
     [](lua_State * state) -> int {
         if (lua_gettop(state) != 2) {
             throw std::runtime_error(paramErr + "setShadow");
         }
         auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
         const std::string sheetName = lua_tostring(state, 2);
         auto resources = getgResHandlerPtr();
         entity->setShadowSheet(&resources->getSheet(sheetName));
         return 0;
     }},
    {"setShadowOffset",
     [](lua_State * state) -> int {
         if (lua_gettop(state) != 3) {
             throw std::runtime_error(paramErr + "setShadowOffset");
         }
         auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
         const float offsetX = lua_tonumber(state, 2);
         const float offsetY = lua_tonumber(state, 3);
         entity->setShadowOffset({offsetX, offsetY});
         return 0;
     }},
    {"setZOrder",
     [](lua_State * state) -> int {
         if (lua_gettop(state) != 2) {
             throw std::runtime_error(paramErr + "setZOrder");
         }
         auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
         const float z = lua_tonumber(state, 2);
         entity->setZOrder(z);
         return 0;
     }},
    {"getZOrder",
     [](lua_State * state) -> int {
         if (lua_gettop(state) != 1) {
             throw std::runtime_error(paramErr + "getZOrder");
         }
         auto entity = (*static_cast<EntityRef *>(lua_touserdata(state, 1)));
         lua_pushnumber(state, entity->getZOrder());
         return 1;
     }},
    {"listAll",
     [](lua_State * state) -> int {
         if (lua_gettop(state) != 1) {
             throw std::runtime_error(paramErr + "listAll");
         }
         Game * pGame = getgGamePtr();
         EntityTable & tab = pGame->getEntityTable();
         // FIXME: this code is unsafe, map entry may not exist...
         auto & entityVec = tab[lua_tostring(state, 1)];
         lua_newtable(state);
         for (int i = 0; i < entityVec.size(); ++i) {
             lua_pushnumber(state, i);
             lua_pushlightuserdata(state, &entityVec[i]);
             lua_settable(state, -3);
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

LuaProvider::LuaProvider() : m_state(luaL_newstate()) {
    luaL_openlibs(m_state);
    registerLib(m_state, systemLibFuncs, "system");
    registerLib(m_state, inputLibFuncs, "input");
    registerLib(m_state, entityLibFuncs, "entity");
    registerLib(m_state, cameraLibFuncs, "camera");
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

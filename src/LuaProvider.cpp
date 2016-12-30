#include "LuaProvider.hpp"
#include "Engine.hpp"

extern microseconds logicUpdateThrottle;

static unsigned long long eid;

// Translates from a eid to the shared pointer to the actual entity object.
// Unique ids are slightly better more secure than exposing pointers used by the
// engine to lua scripts.
static std::map<unsigned long long, EntityRef> translationTable;

static inline EntityRef getEntityFromEid(const size_t id) {
    auto it = translationTable.find(id);
    if (it != translationTable.end()) {
	return it->second;
    }
    throw std::runtime_error("Error: attempt to access nonexsistent entity at EID: " +
			     std::to_string(id));
}

// ENGINE API
//     Provides access to Engine data from lua scripts.
extern "C" {
static const std::string paramErr =
    "Error: wrong number of parameters for function ";

static const luaL_Reg systemLibFuncs[] = {
    {"getScreenSize",
     [](lua_State * state) {
         auto desktop = sf::VideoMode::getDesktopMode();
         lua_pushnumber(state, desktop.width);
         lua_pushnumber(state, desktop.height);
         return 2;
     }},
    {"sleep",
     [](lua_State * state) {
         getgEnginePtr()->setSleep(
             std::chrono::microseconds(lua_tointeger(state, 1)));
         return 0;
     }},
    {"quit",
     [](lua_State * state) {
         // The engine code is multithreaded with a lots of locks, threads,
         // and other resources (e.g. the Lua state) that need to be
         // deallocated correctly. The codebase uses RAII for ALL resources,
         // so letting an exception hit the top level is actually a clean
         // way to quit a game.
         throw ShutdownSignal();
         return 0;
     }},
    {"setVerticalSyncEnabled",
     [](lua_State * state) {
         sf::RenderWindow & window = getgEnginePtr()->getWindow();
         window.setVerticalSyncEnabled(lua_toboolean(state, 1));
         return 0;
     }},
    {"setFramerateLimit",
     [](lua_State * state) {
         sf::RenderWindow & window = getgEnginePtr()->getWindow();
         window.setFramerateLimit(lua_tointeger(state, 1));
         return 0;
     }},
    {"setCursorVisible",
     [](lua_State * state) {
         sf::RenderWindow & window = getgEnginePtr()->getWindow();
         window.setMouseCursorVisible(lua_toboolean(state, 1));
         return 0;
     }},
    {"setLogicUpdateLimit",
     [](lua_State * state) {
         const int throttleAmount = lua_tointeger(state, 1);
         ::logicUpdateThrottle = microseconds(throttleAmount);
         return 0;
     }},
    {}};

static const luaL_Reg foregroundLibFuncs[] = {
    {"createFromSprite",
     [](lua_State * state) {
         BackgroundController & bkg = getgEnginePtr()->getBackground();
         ResHandler & resources = getgEnginePtr()->getResHandler();
         const std::string name(lua_tostring(state, 2));
         bkg.addFgLayer(lua_tointeger(state, 1),
                        {&resources.getSheet(name), 0.f, 0.f, false, 1.f, 1.f,
                         0.f, nullptr, sf::BlendAlpha});
         return 0;
     }},
    {"setPosition",
     [](lua_State * state) {
         BackgroundController & bkg = getgEnginePtr()->getBackground();
         auto layers = bkg.getFgLayers();
         const float x = lua_tonumber(state, 2);
         const float y = lua_tonumber(state, 3);
         Layer & layer = layers.resource.get()[lua_tointeger(state, 1)];
         layer.x = x;
         layer.y = y;
         return 0;
     }},
    {"setFixedEnabled",
     [](lua_State * state) {
         BackgroundController & bkg = getgEnginePtr()->getBackground();
         auto layers = bkg.getFgLayers();
         Layer & layer = layers.resource.get()[lua_tointeger(state, 1)];
         layer.fixed = lua_toboolean(state, 2);
         return 0;
     }},
    {"setScale",
     [](lua_State * state) {
         BackgroundController & bkg = getgEnginePtr()->getBackground();
         auto layers = bkg.getFgLayers();
         Layer & layer = layers.resource.get()[lua_tointeger(state, 1)];
         layer.xScale = lua_tonumber(state, 2);
         layer.yScale = lua_tonumber(state, 3);
         return 0;
     }},
    {"setBlending",
     [](lua_State * state) {
         BackgroundController & bkg = getgEnginePtr()->getBackground();
         auto layers = bkg.getFgLayers();
         Layer & layer = layers.resource.get()[lua_tointeger(state, 1)];
         switch (lua_tointeger(state, 2)) {
         case 0:
             layer.blending = sf::BlendAlpha;
             break;
         case 1:
             layer.blending = sf::BlendAdd;
             break;
         case 2:
             layer.blending = sf::BlendMultiply;
             break;
         case 3:
             layer.blending = sf::BlendNone;
             break;
         default:
             throw std::runtime_error("Error: invalid blendmode");
         }
         return 0;
     }},
    {"setLightingFactor",
     [](lua_State * state) {
         BackgroundController & bkg = getgEnginePtr()->getBackground();
         auto layers = bkg.getFgLayers();
         const float a = lua_tonumber(state, 2);
         layers.resource.get()[lua_tointeger(state, 1)].lightingFactor = a;
         return 0;
     }},
    {"destroy",
     [](lua_State * state) {
	 BackgroundController & bkg = getgEnginePtr()->getBackground();
	 auto layers = bkg.getFgLayers();
	 layers.resource.get().erase(layers.resource.get().find(lua_tointeger(state, 1)));
	 return 0;
     }},
    {}};

static const luaL_Reg backgroundLibFuncs[] = {
    {"createFromSprite",
     [](lua_State * state) {
         BackgroundController & bkg = getgEnginePtr()->getBackground();
         ResHandler & resources = getgEnginePtr()->getResHandler();
         const std::string name(lua_tostring(state, 2));
         bkg.addBkgLayer(lua_tointeger(state, 1),
                         {&resources.getSheet(name), 0.f, 0.f, false, 1.f, 1.f,
                          0.f, nullptr, sf::BlendAlpha});
         return 0;
     }},
    {"setBlending",
     [](lua_State * state) {
         BackgroundController & bkg = getgEnginePtr()->getBackground();
         auto layers = bkg.getBkgLayers();
         Layer & layer = layers.resource.get()[lua_tointeger(state, 1)];
         switch (lua_tointeger(state, 2)) {
         case 0:
             layer.blending = sf::BlendAlpha;
             break;
         case 1:
             layer.blending = sf::BlendAdd;
             break;
         case 2:
             layer.blending = sf::BlendMultiply;
             break;
         case 3:
             layer.blending = sf::BlendNone;
             break;
         default:
             throw std::runtime_error("Error: invalid blendmode");
         }
         return 0;
     }},
    {"setScale",
     [](lua_State * state) {
         BackgroundController & bkg = getgEnginePtr()->getBackground();
         auto layers = bkg.getBkgLayers();
         Layer & layer = layers.resource.get()[lua_tointeger(state, 1)];
         layer.xScale = lua_tonumber(state, 2);
         layer.yScale = lua_tonumber(state, 3);
         return 0;
     }},
    {"setFixedEnabled",
     [](lua_State * state) {
         BackgroundController & bkg = getgEnginePtr()->getBackground();
         auto layers = bkg.getBkgLayers();
         Layer & layer = layers.resource.get()[lua_tointeger(state, 1)];
         layer.fixed = lua_toboolean(state, 2);
         return 0;
     }},
    {"setPosition",
     [](lua_State * state) {
         BackgroundController & bkg = getgEnginePtr()->getBackground();
         auto layers = bkg.getBkgLayers();
         const float x = lua_tonumber(state, 2);
         const float y = lua_tonumber(state, 3);
         Layer & layer = layers.resource.get()[lua_tointeger(state, 1)];
         layer.x = x;
         layer.y = y;
         return 0;
     }},
    {"setLightingFactor",
     [](lua_State * state) {
         BackgroundController & bkg = getgEnginePtr()->getBackground();
         auto layers = bkg.getBkgLayers();
         const float a = lua_tonumber(state, 2);
         layers.resource.get()[lua_tointeger(state, 1)].lightingFactor = a;
         return 0;
     }},
    {"destroy",
     [](lua_State * state) {
	 BackgroundController & bkg = getgEnginePtr()->getBackground();
	 auto layers = bkg.getBkgLayers();
	 layers.resource.get().erase(layers.resource.get().find(lua_tointeger(state, 1)));
	 return 0;
     }},
    {}};

static const luaL_Reg envLibFuncs[] = {
    {"setNaturalLight",
     [](lua_State * state) {
         const uint8_t r = lua_tointeger(state, 1);
         const uint8_t g = lua_tointeger(state, 2);
         const uint8_t b = lua_tointeger(state, 3);
         getgEnginePtr()->setNaturalLight({r, g, b});
         return 0;
     }},
    {}};

static const luaL_Reg cameraLibFuncs[] = {
    {"setTarget",
     [](lua_State * state) {
         auto entity = getEntityFromEid(lua_tointeger(state, 1));
	 getgEnginePtr()->getCamera().setTarget(entity);
	 return 0;
     }},
    {"displaceFromTarget",
     [](lua_State * state) {
         const float x = lua_tonumber(state, 1);
         const float y = lua_tonumber(state, 2);
         getgEnginePtr()->getCamera().setOffset({x, y});
         return 0;
     }},
    {"getViewportSize",
     [](lua_State * state) {
         auto viewsize =
             getgEnginePtr()->getCamera().getOverworldView().getSize();
         lua_pushnumber(state, viewsize.x);
         lua_pushnumber(state, viewsize.y);
         return 2;
     }},
    {"snapToTarget",
     [](lua_State * state) {
         getgEnginePtr()->getCamera().snapToTarget();
         return 0;
     }},
    {}};

static const luaL_Reg lightLibFuncs[] = {
    {"create",
     [](lua_State * state) {
         const std::string sheetName = lua_tostring(state, 1);
         const float x = lua_tonumber(state, 2);
         const float y = lua_tonumber(state, 3);
         Engine * pEngine = getgEnginePtr();
         ResHandler & resources = pEngine->getResHandler();
         auto & lights = pEngine->getLights();
         lights.emplace_back();
         lights.back().setSheet(&resources.getSheet(sheetName));
         lights.back().setPosition({x, y});
         lua_pushlightuserdata(state, (void *)&lights.back());
         return 1;
     }},
    {"setOrigin",
     [](lua_State * state) {
         Light * light = reinterpret_cast<Light *>(lua_touserdata(state, 1));
         const float xOrigin = lua_tonumber(state, 2);
         const float yOrigin = lua_tonumber(state, 3);
         light->setOrigin({xOrigin, yOrigin});
         return 0;
     }},
    {"destroy",
     [](lua_State * state) {
         Light * light = reinterpret_cast<Light *>(lua_touserdata(state, 1));
         light->setKillFlag();
         return 0;
     }},
    {"listAll",
     [](lua_State * state) {
         Engine * pEngine = getgEnginePtr();
         auto & lights = pEngine->getLights();
         lua_newtable(state);
	 int i = 0;
	 for (auto it = lights.begin(); it != lights.end(); ++it) {
	     lua_pushlightuserdata(state, &(*it));
             lua_rawseti(state, -2, ++i);
	 }
         return 1;
     }},
    {}};

static const luaL_Reg inputLibFuncs[] = {
    {"keyPressed",
     [](lua_State * state) {
         int keyCode = lua_tointeger(state, 1);
         Engine * pEngine = getgEnginePtr();
         InputController & input = pEngine->getInputController();
         lua_pushboolean(state, input.getKeyState(keyCode) == 1);
         return 1;
     }},
    {}};

static const luaL_Reg calcLibFuncs[] = {
    {"distance",
     [](lua_State * state) {
         const float x1 = lua_tonumber(state, 1);
         const float x2 = lua_tonumber(state, 3);
         const float y1 = lua_tonumber(state, 2);
         const float y2 = lua_tonumber(state, 4);
         lua_pushnumber(
             state, std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
         return 1;
     }},
    {"random",
     [](lua_State * state) {
         const int upper = lua_tointeger(state, 1);
         const int lower = lua_tointeger(state, 2);
         const int result = calc::rng::random(upper, lower);
         lua_pushinteger(state, result);
         return 1;
     }},
    {"clamp",
     [](lua_State * state) {
         const float x = lua_tonumber(state, 1);
         const float floor = lua_tonumber(state, 2);
         const float ceil = lua_tonumber(state, 3);
         lua_pushnumber(state, calc::clamp(x, floor, ceil));
         return 1;
     }},
    {"lerp",
     [](lua_State * state) {
         const float t = lua_tonumber(state, 3);
         const float A = lua_tonumber(state, 1);
         const float B = lua_tonumber(state, 2);
         lua_pushnumber(state, calc::lerp(A, B, t));
         return 1;
     }},
    {"smoothstep",
     [](lua_State * state) {
         const float edge0 = lua_tonumber(state, 1);
         const float edge1 = lua_tonumber(state, 2);
         const float x = lua_tonumber(state, 3);
         lua_pushnumber(state, calc::smoothstep(edge0, edge1, x));
         return 1;
     }},
    {"smootherstep",
     [](lua_State * state) {
         const float edge0 = lua_tonumber(state, 1);
         const float edge1 = lua_tonumber(state, 2);
         const float x = lua_tonumber(state, 3);
         lua_pushnumber(state, calc::smootherstep(edge0, edge1, x));
         return 1;
     }},
    {}};

static const luaL_Reg entityLibFuncs[] = {
    {"create",
     [](lua_State * state) {
         const std::string classname = lua_tostring(state, 1);
         const float x = lua_tonumber(state, 2);
         const float y = lua_tonumber(state, 3);
         Engine * pEngine = getgEnginePtr();
         auto & entityTable = pEngine->getEntityTable();
         auto & list = pEngine->getEntityTable()[classname];
         list.push_back(std::make_shared<Entity>());
         list.back()->setPosition(sf::Vector2f(x, y));
	 ::eid += 1;
	 ::translationTable[::eid] = list.back();
	 list.back()->setEid(::eid);
	 list.back()->setClassContainerIter(entityTable.find(classname));
	 auto listBackIter = list.end();
	 list.back()->setListContainerIter(--listBackIter);
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
	     throw std::runtime_error(err);
         }
         lua_pushinteger(state, ::eid);
         if (lua_pcall(state, 1, 0, 0)) {
             throw std::runtime_error(lua_tostring(state, -1));
         }
	 lua_pushinteger(state, list.back()->getEid());
         return 1;
     }},
    {"getPosition",
     [](lua_State * state) {
	 auto entity = getEntityFromEid(lua_tointeger(state, 1));
	 auto & pos = entity->getPosition();
	 lua_pushnumber(state, pos.x);
	 lua_pushnumber(state, pos.y);
         return 2;
     }},
    {"setPosition",
     [](lua_State * state) {
	 auto entity = getEntityFromEid(lua_tointeger(state, 1));
	 float x = lua_tonumber(state, 2);
	 float y = lua_tonumber(state, 3);
	 entity->setPosition(sf::Vector2f(x, y));
         return 0;
     }},
    {"destroy",
     [](lua_State * state) {
	 const size_t id = lua_tointeger(state, 1);
	 auto it = ::translationTable.find(id);
	 if (it != translationTable.end()) {
	     auto & className = it->second->getClassName();
	     EntityTable & tab = getgEnginePtr()->getEntityTable();
	     auto & entityList = tab[className];
	     lua_getglobal(state, "classes");
	     lua_getfield(state, -1, className.c_str());
	     lua_getfield(state, -1, "onDestroy");
	     if (lua_isnil(state, -1)) {
		 lua_pop(state, 1);
	     } else {
		 lua_pushinteger(state, it->second->getEid());
		 lua_pcall(state, 1, 0, 0);
	     }
	     for (auto & member : it->second->getMemberTable()) {
		 luaL_unref(state, LUA_REGISTRYINDEX, member.second);
	     }
	     lua_pop(state, 2);
	     entityList.erase(it->second->getListIterToSelf());
	     translationTable.erase(it);
	 }
         return 0;
     }},
    {"checkExists",
     [](lua_State * state) {
	 const size_t id = lua_tointeger(state, 1);
	 auto it = ::translationTable.find(id);
	 lua_pushboolean(state, it != ::translationTable.end());
	 return 1;
     }},
    {"setField",
     [](lua_State * state) {
	 auto entity = getEntityFromEid(lua_tointeger(state, 1));
	 const int varIndex = lua_tointeger(state, 2);
	 auto & members = entity->getMemberTable();
	 if (members.find(varIndex) != members.end()) {
	     luaL_unref(state, LUA_REGISTRYINDEX, members[varIndex]);
	 }
	 lua_pushvalue(state, 3);
	 members[varIndex] = luaL_ref(state, LUA_REGISTRYINDEX);
         return 0;
     }},
    {"getField",
     [](lua_State * state) {
	 auto entity = getEntityFromEid(lua_tointeger(state, 1));
	 const int varIndex = lua_tointeger(state, 2);
	 auto & members = entity->getMemberTable();
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
     [](lua_State * state) {
	 auto entity = getEntityFromEid(lua_tointeger(state, 1));
	 const char * soundName = lua_tostring(state, 2);
	 const float minDist = lua_tonumber(state, 3);
	 const float attenuation = lua_tonumber(state, 4);
	 Engine * pEngine = getgEnginePtr();
	 auto & sounds = pEngine->getSounds();
	 sounds.play(soundName, entity, minDist, attenuation, false);
         return 0;
     }},
    {"setKeyframe",
     [](lua_State * state) {
	 auto entity = getEntityFromEid(lua_tointeger(state, 1));
	 const int frameno = lua_tointeger(state, 2);
	 entity->setKeyframe(frameno);
         return 0;
     }},
    {"getKeyframe",
     [](lua_State * state) {
	 auto entity = getEntityFromEid(lua_tointeger(state, 1));
	 const int frameno = entity->getKeyframe();
	 lua_pushinteger(state, frameno);
         return 1;
     }},
    {"setSprite",
     [](lua_State * state) {
	 auto entity = getEntityFromEid(lua_tointeger(state, 1));
	 const std::string sheetName = lua_tostring(state, 2);
	 auto & resources = getgEnginePtr()->getResHandler();
	 entity->setSheet(&resources.getSheet(sheetName));
         return 0;
     }},
    {"setZOrder",
     [](lua_State * state) {
	 auto entity = getEntityFromEid(lua_tointeger(state, 1));
	 const float z = lua_tonumber(state, 2);
	 entity->setZOrder(z);
         return 0;
     }},
    {"getZOrder",
     [](lua_State * state) {
	 auto entity = getEntityFromEid(lua_tointeger(state, 1));
         lua_pushnumber(state, entity->getZOrder());
         return 1;
     }},
    {"listAll",
     [](lua_State * state) {
         Engine * pEngine = getgEnginePtr();
         EntityTable & tab = pEngine->getEntityTable();
         // FIXME: this code is unsafe, map entry may not exist...
	 const char * strParam = lua_tostring(state, 1);
         auto & entityList = tab[strParam];
         lua_newtable(state);
         int i = 0;
         for (auto it = entityList.begin(); it != entityList.end();) {
	     lua_pushinteger(state, (*it)->getEid());
	     lua_rawseti(state, -2, ++i);
	     ++it;
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
    const auto createBinding = [state](const char * keyName,
                                       sf::Keyboard::Key code) {
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
static const luaL_Reg loadedlibs[] = {{"_G", luaopen_base},
                                      {LUA_LOADLIBNAME, luaopen_package},
                                      {LUA_COLIBNAME, luaopen_coroutine},
                                      {LUA_TABLIBNAME, luaopen_table},
                                      {LUA_STRLIBNAME, luaopen_string},
                                      {LUA_MATHLIBNAME, luaopen_math},
                                      {LUA_UTF8LIBNAME, luaopen_utf8},
                                      {LUA_DBLIBNAME, luaopen_debug},
                                      {}};

static void luaL_openlibs(lua_State * L) {
    const luaL_Reg * lib;
    for (lib = loadedlibs; lib->func; lib++) {
        luaL_requiref(L, lib->name, lib->func, 1);
        lua_pop(L, 1);
    }
}
}

extern const char * heartBeatFn;

LuaProvider::LuaProvider() : m_state(luaL_newstate()) {
    sandbox::luaL_openlibs(m_state);
    registerLib(m_state, systemLibFuncs, "system");
    registerLib(m_state, entityLibFuncs, "entity");
    registerLib(m_state, cameraLibFuncs, "camera");
    registerLib(m_state, lightLibFuncs, "light");
    registerLib(m_state, calcLibFuncs, "calc");
    registerLib(m_state, envLibFuncs, "environment");
    registerLib(m_state, backgroundLibFuncs, "background");
    registerLib(m_state, foregroundLibFuncs, "foreground");
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
    luaL_dostring(m_state, heartBeatFn);
}

LuaProvider::~LuaProvider() { lua_close(m_state); }

void LuaProvider::runScriptFromFile(const std::string & path) {
    if (luaL_loadfile(m_state, path.c_str()) || lua_pcall(m_state, 0, 0, 0)) {
        throw std::runtime_error(lua_tostring(m_state, -1));
    }
}

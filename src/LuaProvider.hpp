#pragma once

#include <cassert>
extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}
#include "ResourcePath.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

struct ConfigData {
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
    ConfigData getConf();
    LuaProvider(const LuaProvider &) = delete;
    LuaProvider & operator=(const LuaProvider &) = delete;

private:
    lua_State * m_state;
};

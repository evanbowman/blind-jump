#pragma once

#include <cassert>
extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}
#include "ResourcePath.hpp"
#include "rng.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class LuaProvider {
public:
    LuaProvider();
    ~LuaProvider();
    void runScriptFromFile(const std::string & path);
    template <typename F> decltype(auto) applyHook(F && functor) {
        return functor(m_state);
    }
    LuaProvider(const LuaProvider &) = delete;
    LuaProvider & operator=(const LuaProvider &) = delete;

private:
    lua_State * m_state;
};

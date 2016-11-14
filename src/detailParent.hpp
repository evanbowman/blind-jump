//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "framework/framework.hpp"
#include <SFML/Graphics.hpp>

class Detail : public framework::Object {
  public:
    Detail(float xInit, float yInit) : Object{xInit, yInit} {}
};

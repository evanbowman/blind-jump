//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <cmath>

//A function to calculate the angle between two objects
inline float angleFunction(float x, float y, float fixedX, float fixedY) {
    return atan2(y - fixedY, x - fixedX) * 180 / 3.14;
}

//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "wall.hpp"

wall::wall()
    : xPosInitial{0.f},
      yPosInitial{0.f},
      xPos{0.f},
      yPos{0.f}
{}

float wall::getPosY() const {
    return yPos;
}

float wall::getPosX() const {
    return xPos;
}

void wall::setPosition(float x, float y) {
    xPos = x;
    yPos = y;
}

void wall::setXinit(float x) {
    xPosInitial = x;
}

void wall::setYinit(float y) {
    yPosInitial = y;
}

float wall::getXinit() const {
    return xPosInitial;
}

float wall::getYinit() const {
    return yPosInitial;
}

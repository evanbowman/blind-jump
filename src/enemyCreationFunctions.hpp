//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
//                                                                        //
// This program is free software: you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or      //
// (at your option) any later version.                                    //
//                                                                        //
// This program is distributed in the hope that it will be useful,        //
// but WITHOUT ANY WARRANTY; without even the implied warranty of         //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
// GNU General Public License for more details.                           //
//                                                                        //
// You should have received a copy of the GNU General Public License      //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
//========================================================================//

#pragma once
#ifndef enemyCreationFunctions_hpp
#define enemyCreationFunctions_hpp

#include <stdio.h>
#include "enemyController.hpp"
#include "coordinate.hpp"

void addTurret(uint8_t mapArray[61][61], uint8_t descriptionArray[61][61], enemyController&, float, float, float, float, std::vector<Coordinate>&);

#endif /* enemyCreationFunctions_hpp */

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
#ifndef detailController_hpp
#define detailController_hpp

#include "SFML/Graphics.hpp"
#include "Teleporter.hpp"
#include "treasureChest.hpp"
#include "tileController.hpp"
#include "coordinate.hpp"
#include "generalDetail.hpp"
#include "lampLight.hpp"
#include "userInterface.hpp"
#include "damagedRobot.hpp"
#include "rock.hpp"
#include "IntroDoor.hpp"
#include <array>
#include "RenderType.hpp"
#include "resourceHandler.hpp"

// TODO: Detail update parameters: xoffset, yoffset, elapsedtime, effectgroup, player
// TODO: make screenShakeController global, ie globalScreenShakeController. There isn't any data in there that's vulnerable

using DetailGroup = Framework::Group<Teleporter, // ----- 0
									 TreasureChest, // -- 1
									 LampLight, // ------ 2
									 Rock, // ----------- 3
									 IntroDoor, // ------ 4
									 DamagedRobot, // --- 5
									 GeneralDetail>; // - 6

using drawableVec = std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>;
using glowVec = std::vector<Sprite>;

template<std::size_t indx, int8_t yOffset = 0>
void drawVec(DetailGroup & dg, drawableVec & gameObjects) {
	for (auto & element : dg.get<indx>()) {
		gameObjects.emplace_back(element.getSprite(), element.getPosition().y + yOffset, Rendertype::shadeDefault, 0.f);
	}
}

template<std::size_t indx, int8_t yOffset = 0>
void drawVecShadowed(DetailGroup & dg, drawableVec & gameObjects, drawableVec & gameShadows) {
	for (auto & element : dg.get<indx>()) {
		gameObjects.emplace_back(element.getSprite(), element.getPosition().y + yOffset, Rendertype::shadeDefault, 0.f);
		gameShadows.emplace_back(element.getShadow(), 0.f, Rendertype::shadeNone, 0.f);
	}
}

inline void drawGroup(DetailGroup & dg, drawableVec & gameObjects, drawableVec & gameShadows, glowVec & glowSprs1, glowVec & glowSprs2, sf::RenderTexture & target) {
	drawVecShadowed<1, -8>(dg, gameObjects, gameShadows);
	drawVec<3, 24>(dg, gameObjects);
	drawVec<4, 60>(dg, gameObjects);
	drawVec<5>(dg, gameObjects);
	drawVec<6>(dg, gameObjects);
	for (auto & element : dg.get<2>()) {
		target.draw(element.getSprite());
		glowSprs1.push_back(element.getGlow());
		glowSprs2.push_back(element.getGlow());
	}
	for (auto & element : dg.get<0>()) {
		target.draw(element.getShadow());
		target.draw(element.getSprite());
		glowSprs1.push_back(element.getGlow());
		glowSprs2.push_back(element.getGlow());
	}
}

#endif /* detailController_hpp */

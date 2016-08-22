//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

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
	drawVecShadowed<1, -16>(dg, gameObjects, gameShadows);
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

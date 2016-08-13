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

#include <SFML/Graphics.hpp>
#include "turretFlashEffect.hpp"
#include "bulletType1.hpp"
#include "shotPuff.hpp"
#include "FireExplosion.hpp"
#include "smallExplosion.hpp"
#include "Item.hpp"
#include "resourceHandler.hpp"
#include "RenderType.hpp"
#include "Framework/framework.hpp"
#include "enemyShot.hpp"
#include "dasherShot.hpp"
#include "turretShot.hpp"

using EffectGroup = Framework::Group<TurretFlashEffect, // - 0
									 SmallExplosion, // ---- 1
									 FireExplosion, // ----- 2
									 ShotPuff, // ---------- 3 
									 Item, // ----------- 4
									 Item, // ----------- 5
									 EnemyShot, // --------- 6
									 DasherShot, // -------- 7
									 TurretShot, // -------- 8
									 PlayerShot>; // ------- 9
	

using drawableVec = std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>;

template<std::size_t indx, int8_t yOffset = 0>
void drawVec(EffectGroup & eg, drawableVec & vec) {
	for (auto & element : eg.get<indx>()) {
		vec.emplace_back(element.getSprite(), element.getPosition().y + yOffset, Rendertype::shadeNone, 0.f);
	}
}

template<std::size_t indx, int8_t yOffset = 0>
void drawVecGlow(EffectGroup & eg, drawableVec & vec, std::vector<Sprite> & glowSprs) {
	for (auto & element : eg.get<indx>()) {
		glowSprs.push_back(element.getGlow());
		vec.emplace_back(element.getSprite(), element.getPosition().y + yOffset, Rendertype::shadeNone, 0.f);
	}
}

inline void drawGroup(EffectGroup & eg, drawableVec & vec, std::vector<Sprite> & glowSprs) {
	drawVec<0, 11>(eg, vec);
	drawVec<3>(eg, vec);
	drawVecGlow<1>(eg, vec, glowSprs);
	drawVecGlow<2>(eg, vec, glowSprs);
	drawVecGlow<4, -16>(eg, vec, glowSprs);
	drawVecGlow<5, -16>(eg, vec, glowSprs);
	drawVecGlow<6, 11>(eg, vec, glowSprs);
	drawVecGlow<7, 11>(eg, vec, glowSprs);
	drawVecGlow<8, 11>(eg, vec, glowSprs);
	drawVecGlow<9>(eg, vec, glowSprs);
}

//  Created by Evan Bowman on 10/20/15.

#pragma once
#ifndef effectsController_hpp
#define effectsController_hpp

#include <SFML/Graphics.hpp>
#include "turretFlashEffect.hpp"
#include "bulletType1.hpp"
#include "shotPuff.hpp"
#include "FireExplosion.hpp"
#include "smallExplosion.hpp"
#include "Powerup.hpp"
#include "ResourceHandler.hpp"
#include "RenderType.hpp"
#include "Framework/framework.hpp"
#include "enemyShot.hpp"
#include "dasherShot.hpp"
#include "turretShot.hpp"

using EffectGroup = Framework::Group<turretFlashEffect,
									 SmallExplosion,
									 FireExplosion,
									 shotPuff,
									 Powerup,
									 Powerup,
									 EnemyShot,
									 DasherShot,
									 TurretShot>;

using drawableVec = std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>;

template<std::size_t indx, int8_t yOffset = 0>
void drawVec(EffectGroup & eg, drawableVec & vec) {
	for (auto & element : eg.get<indx>()) {
		vec.emplace_back(element.getSprite(), element.getPosition().y + yOffset, Rendertype::shadeNone, 0.f);
	}
}

template<std::size_t indx, int8_t yOffset = 0>
void drawVecGlow(EffectGroup & eg, drawableVec & vec, std::vector<Sprite *> & glowSprs) {
	for (auto & element : eg.get<indx>()) {
		glowSprs.push_back(element.getGlow());
		vec.emplace_back(element.getSprite(), element.getPosition().y + yOffset, Rendertype::shadeNone, 0.f);
	}
}

inline void drawGroup(EffectGroup & eg, drawableVec & vec, std::vector<Sprite *> & glowSprs) {
	drawVec<0, 11>(eg, vec); // Could this be expanded recursively with templates?
	drawVec<3>(eg, vec);
	drawVecGlow<1>(eg, vec, glowSprs);
	drawVecGlow<2>(eg, vec, glowSprs);
	drawVecGlow<4, -16>(eg, vec, glowSprs);
	drawVecGlow<5, -16>(eg, vec, glowSprs);
	drawVecGlow<6, 11>(eg, vec, glowSprs);
	drawVecGlow<7, 11>(eg, vec, glowSprs);
	drawVecGlow<8, 11>(eg, vec, glowSprs);
}

#endif /* effectsController_hpp */

//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "FireExplosion.hpp"
#include "Item.hpp"
#include "RenderType.hpp"
#include "bulletType1.hpp"
#include "dasherShot.hpp"
#include "enemyShot.hpp"
#include "framework/framework.hpp"
#include "resourceHandler.hpp"
#include "shotPuff.hpp"
#include "smallExplosion.hpp"
#include "turretFlashEffect.hpp"
#include "turretShot.hpp"
#include <SFML/Graphics.hpp>

using EffectGroup = framework::Group<TurretFlashEffect, // - 0
                                     SmallExplosion,    // ---- 1
                                     FireExplosion,     // ----- 2
                                     ShotPuff,          // ---------- 3
                                     Item,              // -------------- 4
                                     Item,              // -------------- 5
                                     EnemyShot,         // --------- 6
                                     DasherShot,        // -------- 7
                                     TurretShot,        // -------- 8
                                     PlayerShot>;       // ------- 9

using drawableVec =
    std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>;

template <size_t indx, int8_t yOffset = 0>
void drawVec(EffectGroup & eg, drawableVec & vec, const sf::Vector2f viewCenter,
             const sf::Vector2f viewSize) {
    for (auto & element : eg.get<indx>()) {
        const sf::Vector2f elemPos = element.getPosition();
        if (elemPos.x > viewCenter.x - viewSize.x / 2 &&
            elemPos.x < viewCenter.x + viewSize.x / 2 &&
            elemPos.y > viewCenter.y - viewSize.y / 2 &&
            elemPos.y < viewCenter.y + viewSize.y / 2) {
            vec.emplace_back(element.getSprite(), elemPos.y + yOffset,
                             Rendertype::shadeNone, 0.f);
        }
    }
}

template <size_t indx, int8_t yOffset = 0>
void drawVecGlow(EffectGroup & eg, drawableVec & vec,
                 std::vector<sf::Sprite> & glowSprs,
                 const sf::Vector2f viewCenter, const sf::Vector2f viewSize) {
    for (auto & element : eg.get<indx>()) {
        const sf::Vector2f elemPos = element.getPosition();
        if (elemPos.x > viewCenter.x - viewSize.x / 2 &&
            elemPos.x < viewCenter.x + viewSize.x / 2 &&
            elemPos.y > viewCenter.y - viewSize.y / 2 &&
            elemPos.y < viewCenter.y + viewSize.y / 2) {
            glowSprs.push_back(element.getGlow());
            vec.emplace_back(element.getSprite(), elemPos.y + yOffset,
                             Rendertype::shadeNone, 0.f);
        }
    }
}

inline void drawGroup(EffectGroup & eg, drawableVec & vec,
                      std::vector<sf::Sprite> & glowSprs,
                      const sf::Vector2f viewCenter,
                      const sf::Vector2f viewSize) {
    drawVec<0, 11>(eg, vec, viewCenter, viewSize);
    drawVec<3>(eg, vec, viewCenter, viewSize);
    drawVecGlow<1>(eg, vec, glowSprs, viewCenter, viewSize);
    drawVecGlow<2>(eg, vec, glowSprs, viewCenter, viewSize);
    drawVecGlow<4, -16>(eg, vec, glowSprs, viewCenter, viewSize);
    drawVecGlow<5, -16>(eg, vec, glowSprs, viewCenter, viewSize);
    drawVecGlow<6, 11>(eg, vec, glowSprs, viewCenter, viewSize);
    drawVecGlow<7, 11>(eg, vec, glowSprs, viewCenter, viewSize);
    drawVecGlow<8, 11>(eg, vec, glowSprs, viewCenter, viewSize);
    drawVecGlow<9>(eg, vec, glowSprs, viewCenter, viewSize);
}

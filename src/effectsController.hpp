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

using DefaultEffectPolicy = RenderPolicy<DrawMainRaw, DrawGlowFloor>;
using TurretFlashEffect = effect::TurretFlashEffect<RenderPolicy<DrawMainRaw>>;
using SmallExplosion = effect::SmallExplosion<DefaultEffectPolicy>;
using FireExplosion = effect::FireExplosion<DefaultEffectPolicy>;
using ShotPuff = effect::ShotPuff<RenderPolicy<DrawMainRaw>>;
using Item = effect::Item<DefaultEffectPolicy>;
using EnemyShot = effect::EnemyShot<DefaultEffectPolicy>;
using DasherShot = effect::DasherShot<DefaultEffectPolicy>;
using TurretShot = effect::TurretShot<DefaultEffectPolicy>;
using PlayerShot = effect::PlayerShot<DefaultEffectPolicy>;

struct EffectRef {
    enum {
        TurretFlashEffect,
        SmallExplosion,
        FireExplosion,
        ShotPuff,
        Heart,
        Coin,
        EnemyShot,
        DasherShot,
        TurretShot,
        PlayerShot,
        Count
    };
};

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

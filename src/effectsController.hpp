//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <memory>

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

using EffectGroup =
    framework::Group<TurretFlashEffect, SmallExplosion, FireExplosion, ShotPuff,
                     Item, Item, EnemyShot, DasherShot, TurretShot, PlayerShot>;

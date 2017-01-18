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
using TurretFlashEffect = _TurretFlashEffect<RenderPolicy<DrawMainRaw>>;
using SmallExplosion = _SmallExplosion<DefaultEffectPolicy>;
using FireExplosion = _FireExplosion<DefaultEffectPolicy>;
using ShotPuff = _ShotPuff<RenderPolicy<DrawMainRaw>>;
using Item = _Item<DefaultEffectPolicy>;
using EnemyShot = _EnemyShot<DefaultEffectPolicy>;
using DasherShot = _DasherShot<DefaultEffectPolicy>;
using TurretShot = _TurretShot<DefaultEffectPolicy>;
using PlayerShot = _PlayerShot<DefaultEffectPolicy>;

struct EffectRef {
    enum {
        TurretFlashEffect,
        SmallExplosion,
        FireExplosion,
        ShotPuff,
        Heart,
        Coin,
        GoldHeart,
        EnemyShot,
        DasherShot,
        TurretShot,
        PlayerShot,
        Count
    };
};

using EffectGroup =
    Group<TurretFlashEffect, SmallExplosion, FireExplosion, ShotPuff, Item,
          Item, Item, EnemyShot, DasherShot, TurretShot, PlayerShot>;

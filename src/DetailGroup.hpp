//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include "IntroDoor.hpp"
#include "RenderType.hpp"
#include "Teleporter.hpp"
#include "coordinate.hpp"
#include "generalDetail.hpp"
#include "lampLight.hpp"
#include "resourceHandler.hpp"
#include "rock.hpp"
#include "terminal.hpp"
#include "tileController.hpp"
#include "treasureChest.hpp"
#include "userInterface.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include "GfxContext.hpp"

using TreasureChest = detail::TreasureChest<RenderPolicy<DrawMain, DrawShadow>>;
using Teleporter = detail::Teleporter<RenderPolicy<ForceShadow, ForceMain, DrawGlow>>;
using Lamp = detail::Lamp<RenderPolicy<ForceMain, DrawGlow>>;
using Rock = detail::Rock<RenderPolicy<DrawMain>>;
using IntroDoor = detail::IntroDoor<RenderPolicy<DrawMain>>;
using StaticDrawable = detail::StaticDrawable<RenderPolicy<DrawMain>>;
using Terminal = detail::Terminal<RenderPolicy<DrawMain, DrawShadow>>;

struct DetailRef {
    enum {
        Teleporter,
        TreasureChest,
        Lamp,
        Rock,
        IntroDoor,
        StaticDrawable,
        Terminal
    };
};

using DetailGroup = framework::Group<Teleporter,
                                     TreasureChest,
                                     Lamp,
                                     Rock,
                                     IntroDoor,
                                     StaticDrawable,
                                     Terminal>;

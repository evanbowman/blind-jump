#pragma once

#include "GfxContext.hpp"
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

using TreasureChest = _TreasureChest<RenderPolicy<DrawMain, DrawShadow>>;
using Teleporter =
    _Teleporter<RenderPolicy<ForceShadow, ForceMain, DrawGlowAll>>;
using Lamp = _Lamp<RenderPolicy<ForceMain, DrawGlowAll>>;
using Rock = _Rock<RenderPolicy<DrawMain>>;
using IntroDoor = _IntroDoor<RenderPolicy<DrawMain>>;
using StaticDrawable = _StaticDrawable<RenderPolicy<DrawMain>>;
using Terminal = _Terminal<RenderPolicy<DrawMain, DrawShadow, DrawScreen>>;

struct DetailRef {
    enum {
        Teleporter,
        TreasureChest,
        Lamp,
        Rock,
        IntroDoor,
        StaticDrawable,
        Terminal,
        Count
    };
};

using DetailGroup = framework::Group<Teleporter, TreasureChest, Lamp, Rock,
                                     IntroDoor, StaticDrawable, Terminal>;

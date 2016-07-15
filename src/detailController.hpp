//  Created by Evan Bowman on 10/29/15.

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

using DetailGroup = Framework::Group<Teleporter, // ----- 0
									 TreasureChest, // -- 1
									 LampLight, // ------ 2
									 Rock, // ----------- 3
									 IntroDoor, // ------ 4
									 DamagedRobot, // --- 5
									 GeneralDetail>; // - 6

using drawableVec = std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>;

#endif /* detailController_hpp */

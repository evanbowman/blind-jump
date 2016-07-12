//
//  effectsController.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef effectsController_hpp
#define effectsController_hpp

#include "SFML/Graphics.hpp"
#include "turretFlashEffect.hpp"
#include "bulletType1.hpp"
#include "shotPuff.hpp"
#include "FireExplosion.hpp"
#include "smallExplosion.hpp"
#include "Powerup.hpp"
#include "ResourceHandler.hpp"
#include "RenderType.hpp"
#include "Framework/framework.hpp"

using EffectGroup = Framework::Group<turretFlashEffect,
									 SmallExplosion,
									 FireExplosion,
									 shotPuff,
									 Powerup,
									 Powerup>;

#endif /* effectsController_hpp */

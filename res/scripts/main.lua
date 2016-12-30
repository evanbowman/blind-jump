require("enemies/Turret")
require("enemies/Dasher")
require("details/Pod")
require("details/Door")
require("details/Lamp")
require("details/Transporter")
require("details/IntroFloor")
require("Wall")
require("Player")

system.setVerticalSyncEnabled(true)
system.setCursorVisible(false)
system.setLogicUpdateLimit(2000)

environment.setNaturalLight(190, 190, 210)

local level = -1

camera.setTarget(player)
local _, viewportH = camera.getViewportSize()
camera.displaceFromTarget(0, -viewportH / 6)

local utility = require("utility")

foreground.createFromSprite(0, "vignetteShadowSprite")
utility.setLayerFixedStretched(0, foreground, 450, 450)
foreground.createFromSprite(1, "vignetteSprite")
utility.setLayerFixedStretched(1, foreground, 450, 450)
foreground.setBlending(1, 2)

local clearEntitiesOf = function(classname)
   local entitiesList = entity.listAll(classname)
   for i = 1, #entitiesList do
      entity.destroy(entitiesList[i])
   end
end

local clearLights = function()
   local lightsList = light.listAll()
   for i = 1, #lightsList do
      entity.destroy(lightsList[i])
   end
end

local cleanupLevel = function()
   if level == 0 then
      clearEntitiesOf("Pod")
      clearEntitiesOf("Door")
   elseif level > 0 then
      -- TODO...
   end
   clearEntitiesOf("Lamp")
   clearEntitiesOf("Wall")
   clearEntitiesOf("Transporter")
   clearLights()
end

local setupLevel = function()
   if level == 0 then
      background.createFromSprite(0, "introLevelFloorSprite")
      background.setPosition(0, 305, -231)
      background.setLightingFactor(0, 1)
      background.createFromSprite(1, "grassTileSprite")
      utility.setLayerFixedStretched(1, background, 16, 16)
      foreground.createFromSprite(2, "introLevelMaskSprite")
      foreground.setPosition(2, 284, -250)
      entity.setPosition(player, playerStart.x, playerStart.y)
      entity.create("Transporter", 378, -128)
      entity.create("Pod", 400, 216)
      entity.create("Door", 305, 70)
      local lampPositions = {
         { x = 300, y = 122 },
         { x = 300, y = -34 },
         { x = 492, y = 252 },
         { x = 476, y = -248 }
      }
      for i = 1, #lampPositions do
	 entity.create("Lamp", lampPositions[i].x, lampPositions[i].y)
      end
      local wallPositions = {
	 { x = -20, y = 500 }, { x = -20, y = 526 }, { x = -20, y = 474 },
	 { x = -20, y = 448 }, { x = -20, y = 422 }, { x = -20, y = 396 },
	 { x = -20, y = 370 }, { x = -20, y = 552 }, { x = -20, y = 578 },
	 { x = 196, y = 500 }, { x = 196, y = 526 }, { x = 196, y = 474 },
	 { x = 196, y = 448 }, { x = 196, y = 422 }, { x = 196, y = 396 },
	 { x = 196, y = 370 }, { x = 196, y = 552 }, { x = 196, y = 578 },
	 { x = 108, y = 604 }, { x = 140, y = 604 }, { x = 172, y = 604 },
	 { x = 120, y = 370 }, { x = 152, y = 370 }, { x = 184, y = 370 },
	 { x = 120, y = 344 }, { x = 120, y = 318 }, { x = 120, y = 292 },
	 { x = 120, y = 266 }, { x = -20, y = 266 }, { x = -20, y = 240 },
	 { x = -20, y = 214 }, { x = -20, y = 188 }, { x = -20, y = 162 },
	 { x = -20, y = 136 }, { x = -20, y = 110 }, { x = 152, y = 266 },
	 { x = 172, y = 240 }, { x = 172, y = 214 }, { x = 172, y = 188 },
	 { x = 172, y = 162 }, { x = 172, y = 136 }, { x = 172, y = 110 },
	 { x = 34, y = 344 }, { x = 34, y = 318 }, { x = 34, y = 292 },
	 { x = 34, y = 266 }, { x = 12, y = 266 }, { x = 12, y = 604 },
	 { x = 44, y = 604 }, { x = 76, y = 604 }, { x = 12, y = 370 },
	 { x = 34, y = 370 }, { x = -20, y = 84 }, { x = 172, y = 84 },
	 { x = 108, y = 58 }, { x = 140, y = 58 }, { x = 12, y = 58 },
	 { x = 76, y = 58 }, { x = 44, y = 58 }
      }
      for i = 1, #wallPositions do
 	 entity.create("Wall", wallPositions[i].x, wallPositions[i].y)
      end
   elseif level > 0 then
      -- TODO...
   end
end

function nextLevel()
   cleanupLevel()
   level = level + 1
   setupLevel()
end

nextLevel()

entity.create("Turret", 350, 200)

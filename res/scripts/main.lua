require("enemies/Turret")
require("enemies/Dasher")
require("details/Pod")
require("details/Door")
require("details/Lamp")
require("Wall")
require("Player")

local level = -1

local playerStart = { x = 374, y = 238 }
local player = entity.new("Player", playerStart.x, playerStart.y)

camera.setTarget(player)
local w, h = camera.getViewportSize()
camera.displaceFromTarget(0, -h / 4)

local clearEntitiesOf = function(classname)
   local entitiesList = entity.listAll(classname)
   for i, handle in pairs(entitiesList) do
      entity.dispose(handle)
   end
end

local clearLights = function()
   local lightsList = light.listAll()
   for i, handle in pairs(lightsList) do
      light.dispose(handle)
   end
end

local cleanupLevel = function()
   if level == 0 then
      clearEntitiesOf("Pod")
      clearEntitiesOf("Door")
      clearEntitiesOf("Lamp")
   elseif level > 0 then
      -- TODO...
   end
   clearLights()
end

local setupLevel = function()
   if level == 0 then
      entity.setPosition(player, playerStart.x, playerStart.y)
      entity.new("Pod", 400, 216)
      entity.new("Door", 305, 70)
      local lampPositions = {
         { x = 300, y = 122 },
         { x = 300, y = -34 },
         { x = 492, y = 252 },
         { x = 460, y = -248 }
      }
      for k, coord in pairs(lampPositions) do
	 entity.new("Lamp", coord.x, coord.y)
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

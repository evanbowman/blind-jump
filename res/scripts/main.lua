require("enemies/Turret")
require("enemies/Dasher")
require("details/Pod")
require("details/Door")
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

local cleanupLevel = function()
   if level == 0 then
      clearEntitiesOf("Pod")
      clearEntitiesOf("Door")
   elseif level > 0 then
      -- TODO...
   end
end

local setupLevel = function()
   if level == 0 then
      entity.setPosition(player, playerStart.x, playerStart.y)
      entity.new("Pod", 400, 216)
      entity.new("Door", 305, 70)
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

require("enemies/Turret")
require("enemies/Dasher")
require("details/Pod")
require("details/Door")
require("player")

level = -1
local player = entity.new("Player", 100, 100)
camera.setTarget(player)

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

require("enemies/Turret")
require("enemies/Dasher")
require("details/Pod")
require("details/Door")

level = 0

function setupIntroLevel()
   entity.new("Pod", 400, 216)
   entity.new("Door", 305, 70)
end

setupIntroLevel()

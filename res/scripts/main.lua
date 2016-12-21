require("enemies")
require("details")

local turret = entity.spawn("Turret")
entity.setPosition(turret, 400, 200)

local rock = entity.spawn("Rock")

entity.destroy(rock)

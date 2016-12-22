require("enemies")
require("details")

local turret = entity.spawn("Turret")
entity.setPosition(turret, 400, 200)

local dasher = entity.spawn("Dasher")
entity.setPosition(dasher, 500, 200)

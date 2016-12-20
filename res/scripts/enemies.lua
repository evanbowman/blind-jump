Enemies = {}

--[[=============================================
TURRET
   They are stationary, but shoot
   super fast.
===============================================]]

Enemies["Turret"] = {
   OnCreate = function(this)
      local TODO = true
   end,
   
   OnUpdate = function(this)
      deltaT = game.getDeltaTime()
   end,

   OnDestroy = function(this)
      local TODO = true
   end
}

game.registerEnemyClass("Turret")


--[[=============================================
DASHER
   Fast and pretty deadly, they jump
   all over the place and have a powerful
   laser-shotgun.
===============================================]]

Enemies["Dasher"] = {
   OnCreate = function(this)
      local TODO = true
   end,

   OnUpdate = function(this)
      deltaT = game.getDeltaTime()
   end,

   OnDestroy = function(this)
      local TODO = true
   end
}

game.registerEnemyClass("Dasher")


--[[=============================================
DRONE
   Lightweight easy enemy, but they can
   sneak up on you.
===============================================]]

Enemies["Drone"] = {
   OnCreate = function(this)
      local TODO = true
   end,

   OnUpdate = function(this)
      deltaT = game.getDeltaTime()
   end,

   OnDestroy = function(this)
      local TODO = true
   end
}

game.registerEnemyClass("Drone")


--[[=============================================
CRITTER
   Persistent guys that follow you around,
   can be dangerous in large numbers.
===============================================]]

Enemies["Critter"] = {
   OnCreate = function(this)
      local TODO = true
   end,

   OnUpdate = function(this)
      deltaT = game.getDeltaTime()
   end,

   OnDestroy = function(this)
      local TODO = true
   end
}

game.registerEnemyClass("Critter")

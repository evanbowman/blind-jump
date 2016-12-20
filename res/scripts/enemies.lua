
classes = {}

--[[=============================================
TURRET
   They are stationary, but shoot
   super fast.
===============================================]]

classes["Turret"] = {
   OnCreate = function(this)
      local TODO = true
   end,

   OnUpdate = function(this)
      -- deltaT = game.getDeltaTime()
      -- print(deltaT)
      local TODO = true
   end,

   OnDestroy = function(this)
      local TODO = true
   end
}

game.registerClass("Turret")

local created = game.createInstance("Turret")

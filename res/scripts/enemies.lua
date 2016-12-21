
--[[=============================================
TURRET
   They are stationary, but shoot lotsa bullets
===============================================]]

turretAction = {
   ["closed"] = function(this, timer)
      if timer > 50000 then
	 entity.setState(this, "opening")
	 entity.setTimer(this, 0, 0)
      else
	 entity.setTimer(this, 0, timer)
      end
   end,
   
   ["opening"] = function(this, timer)
      if timer > 50000 then
	 entity.setState(this, "shoot1")
	 entity.setTimer(this, 0, 0)
      else
	 entity.setTimer(this, 0, timer)
      end
   end,
   
   ["shoot1"] = function(this, timer)
      if timer > 50000 then
	 entity.setState(this, "shoot2")
	 entity.setTimer(this, 0, 0)
      else
	 entity.setTimer(this, 0, timer)
      end
   end,
   
   ["shoot2"] = function(this, timer)
      if timer > 50000 then
	 entity.setState(this, "shoot3")
	 entity.setTimer(this, 0, 0)
      else
	 entity.setTimer(this, 0, timer)
      end
   end,
   
   ["shoot3"] = function(this, timer)
      if timer > 50000 then
	 entity.setState(this, "rest")
	 entity.setTimer(this, 0, 0)
      else
	 entity.setTimer(this, 0, timer)
      end
   end,
   
   ["rest"] = function(this, timer)
      if timer > 50000 then
	 entity.setState(this, "closing")
	 entity.setTimer(this, 0, 0)
      else
	 entity.setTimer(this, 0, timer)
      end
   end,
   
   ["closing"] = function(this, timer)
      if timer > 50000 then
	 entity.setState(this, "closed")
	 entity.setTimer(this, 0, 0)
      else
	 entity.setTimer(this, 0, timer)
      end
   end
}

classes["Turret"] = {
   OnCreate = function(this)
      entity.setState(this, "closed")
   end,

   OnUpdate = function(this)
      local dt = system.getDeltaTime()
      local timer = entity.getTimer(this, 0)
      timer = timer + dt
      local state = entity.getState(this)
      turretAction[state](this, timer)
   end
}

system.registerClass("Turret")

entity.create("Turret")

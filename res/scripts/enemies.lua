classes["Turret"] = {
   OnCreate = function(this)
      entity.setField(this, "hp", 6)
      entity.setField(this, "timer", 0)
      entity.setField(this, "state", "closed")
      entity.setSheet(this, "turretSheet")
   end,
   
   OnUpdate = function(this)
      local dt = system.getDeltaTime()
      local timer = entity.getField(this, "timer")
      timer = timer + dt
      entity.setField(this, "timer", timer)
      local state = entity.getField(this, "state")
      classes["Turret"].FSM[state](this, timer)
      local currentHealth = entity.getField(this, "hp")
      if currentHealth == 0 then
	 entity.destroy(this)
      end
   end,
   
   FSM = {
      ["closed"] = function(this, timer)
	 if timer > 50000 then
	    entity.setField(this, "state", "opening")
	    entity.setField(this, "timer", 0)
	 end
      end,
      
      ["opening"] = function(this, timer)
	 if timer > 50000 then
	    entity.setField(this, "timer", 0)
	    local currentFrame = entity.getKeyframe(this)
	    currentFrame = currentFrame + 1
	    if currentFrame <= 4 then
	       entity.setKeyframe(this, currentFrame)
	    else
	       entity.setField(this, "state", "shoot1")
	    end
	 end
      end,
      
      ["shoot1"] = function(this, timer)
	 if timer > 200000 then
	    entity.setField(this, "state", "shoot2")
	    entity.setField(this, "timer", 0)
	    entity.emitSound(this, "sounds/laser.ogg", 220, 30)
	 end
      end,
      
      ["shoot2"] = function(this, timer)
	 if timer > 200000 then
	    entity.setField(this, "state", "shoot3")
	    entity.setField(this, "timer", 0)
	    entity.emitSound(this, "sounds/laser.ogg", 220, 30)
	 end
      end,
      
      ["shoot3"] = function(this, timer)
	 if timer > 200000 then
	    entity.setField(this, "state", "rest")
	    entity.setField(this, "timer", 0)
	    entity.emitSound(this, "sounds/laser.ogg", 220, 30)
	 end
      end,
      
      ["rest"] = function(this, timer)
	 if timer > 1200000 then
	    entity.setField(this, "state", "closing")
	    entity.setField(this, "timer", 0)
	 end
      end,
      
      ["closing"] = function(this, timer)
	 if timer > 50000 then
	    entity.setField(this, "timer", 0)
	    local currentFrame  = entity.getKeyframe(this)
	    currentFrame = currentFrame - 1
	    if currentFrame >= 0 then
	       entity.setKeyframe(this, currentFrame)
	    else
	       entity.setField(this, "state", "closed")
	    end
	 end
      end
   }
}

classes["Dasher"] = {
   OnCreate = function(this)
      entity.setSheet(this, "dasherSheet")
      entity.setField(this, "hp", 5)
      entity.setField(this, "timer", 0)
      entity.setField(this, "state", "idle")
   end,

   OnUpdate = function(this)
      local dt = system.getDeltaTime()
      local timer = entity.getField(this, "timer")
      timer = timer + dt
      entity.setField(this, "timer", timer)
      local state = entity.getField(this, "state")
      classes["Dasher"].FSM[state](this, timer)
      local currentHealth = entity.getField(this, "hp")
      if currentHealth == 0 then
	 entity.destroy(this)
      end
   end,

   FSM = {
      ["idle"] = function(this, timer)
	 if timer > 200000 then
	    entity.setField(this, "timer", 0)
	    if system.random(2, 0) == 1 then
	       entity.setField(this, "state", "dashBegin")
	       entity.setKeyframe(this, 1)
	    else
	       entity.setField(this, "state", "shootBegin")
	       entity.setKeyframe(this, 3)
	    end
	 end
      end,

      ["dashBegin"] = function(this, timer)
	 
      end,

      ["shooting"] = function(this, timer)
	 
      end,
      
      ["shootBegin"] = function(this, timer)
	 
      end,
      
      ["dashing"] = function(this, timer)
	 
      end,
      
      ["dashEnd"] = function(this, timer)
	 
      end,
      
      ["dying"] = function(this, timer)
	 
      end,
      
      ["dead"] = function(this, timer)
	 
      end,
      
      ["pause"] = function(this, timer)
	 
      end
   }
}

classes["Dasher"] = {
   onCreate = function(this)
      entity.setSprite(this, "dasherSheet")
      entity.setField(this, "hp", 5)
      entity.setField(this, "timer", 0)
      entity.setField(this, "state", "idle")
   end,

   onUpdate = function(this)
      local dt = system.getDeltaTime()
      local timer = entity.getField(this, "timer")
      timer = timer + dt
      entity.setField(this, "timer", timer)
      local state = entity.getField(this, "state")
      classes["Dasher"].FSM[state](this, timer)
      local currentHealth = entity.getField(this, "hp")
      if currentHealth == 0 then
	 entity.dispose(this)
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

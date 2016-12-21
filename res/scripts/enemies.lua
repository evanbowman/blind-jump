classes["Turret"] = {
   OnCreate = function(this)
      entity.setField(this, "hp", 6)
      entity.setField(this, "animCounter", 0)
      entity.setField(this, "state", "closed")
      entity.setSheet(this, "turretSheet")
   end,
   
   OnUpdate = function(this)
      local dt = system.getDeltaTime()
      local counter = entity.getField(this, "animCounter")
      counter = counter + dt
      entity.setField(this, "animCounter", counter)
      local state = entity.getField(this, "state")
      classes["Turret"].FSM[state](this, counter)
      local currentHealth = entity.getField(this, "hp")
      if currentHealth == 0 then
	 entity.destroy(this)
      end
   end,
   
   FSM = {
      ["closed"] = function(this, counter)
	 if counter > 50000 then
	    entity.setField(this, "state", "opening")
	    entity.setField(this, "animCounter", 0)
	 end
      end,
      
      ["opening"] = function(this, counter)
	 if counter > 50000 then
	    entity.setField(this, "animCounter", 0)
	    local currentFrame = entity.getKeyframe(this)
	    currentFrame = currentFrame + 1
	    if currentFrame <= 4 then
	       entity.setKeyframe(this, currentFrame)
	    else
	       entity.setField(this, "state", "shoot1")
	    end
	 end
      end,
      
      ["shoot1"] = function(this, counter)
	 if counter > 200000 then
	    entity.setField(this, "state", "shoot2")
	    entity.setField(this, "animCounter", 0)
	    entity.emitSound(this, "sounds/laser.ogg", 220, 30)
	 end
      end,
      
      ["shoot2"] = function(this, counter)
	 if counter > 200000 then
	    entity.setField(this, "state", "shoot3")
	    entity.setField(this, "animCounter", 0)
	    entity.emitSound(this, "sounds/laser.ogg", 220, 30)
	 end
      end,
      
      ["shoot3"] = function(this, counter)
	 if counter > 200000 then
	    entity.setField(this, "state", "rest")
	    entity.setField(this, "animCounter", 0)
	    entity.emitSound(this, "sounds/laser.ogg", 220, 30)
	 end
      end,
      
      ["rest"] = function(this, counter)
	 if counter > 1200000 then
	    entity.setField(this, "state", "closing")
	    entity.setField(this, "animCounter", 0)
	 end
      end,
      
      ["closing"] = function(this, counter)
	 if counter > 50000 then
	    entity.setField(this, "animCounter", 0)
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

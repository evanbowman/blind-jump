local memberIds = {
   state = 0,
   timer = 1,
   hp = 5
}

local fsm = {
   ["idle"] = function(this, timer)
      if timer > 200000 then
	 entity.setField(this, memberIds.timer, 0)
	 if system.random(2, 0) == 1 then
	    entity.setField(this, memberIds.state, "dashBegin")
	    entity.setKeyframe(this, 1)
	 else
	    entity.setField(this, memberIds.state, "shootBegin")
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

classes["Dasher"] = {
   onCreate = function(this)
      entity.setSprite(this, "dasherSheet")
      entity.setField(this, memberIds.hp, 5)
      entity.setField(this, memberIds.timer, 0)
      entity.setField(this, memberIds.state, "idle")
   end,

   onUpdate = function(this)
      local dt = system.getDeltaTime()
      local timer = entity.getField(this, memberIds.timer)
      timer = timer + dt
      entity.setField(this, memberIds.timer, timer)
      local state = entity.getField(this, memberIds.state)
      fsm[state](this, timer)
      local currentHealth = entity.getField(this, memberIds.hp)
      if currentHealth == 0 then
	 entity.dispose(this)
      end
   end
}

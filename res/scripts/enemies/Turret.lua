require("effects/MuzzleFlash")

classes["Turret"] = {
   onCreate = function(this)
      entity.setField(this, "hp", 6)
      entity.setField(this, "timer", 0)
      entity.setField(this, "state", "closed")
      entity.setSprite(this, "turretSprite")
      entity.setShadow(this, "turretShadowSprite")
      entity.setShadowOffset(this, 20)
      local x, y = entity.getPosition(this)
      entity.setZOrder(this, y - 3)
   end,
   
   onUpdate = function(this)
      local dt = system.getDeltaTime()
      local timer = entity.getField(this, "timer")
      timer = timer + dt
      entity.setField(this, "timer", timer)
      local state = entity.getField(this, "state")
      classes["Turret"].FSM[state](this, timer)
      local currentHealth = entity.getField(this, "hp")
      
      if currentHealth == 0 then
	 entity.dispose(this)
      end
   end,

   emitBullet = function(this)
      local x, y = entity.getPosition(this)
      entity.new("MuzzleFlash", x, y + 10)
      entity.emitSound(this, "sounds/laser.ogg", 220, 30)
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
	    classes["Turret"].emitBullet(this)
	 end
      end,
      
      ["shoot2"] = function(this, timer)
	 if timer > 200000 then
	    entity.setField(this, "state", "shoot3")
	    entity.setField(this, "timer", 0)
	    classes["Turret"].emitBullet(this)
	 end
      end,
      
      ["shoot3"] = function(this, timer)
	 if timer > 200000 then
	    entity.setField(this, "state", "rest")
	    entity.setField(this, "timer", 0)
	    classes["Turret"].emitBullet(this)
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

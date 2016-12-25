require("effects/MuzzleFlash")

local emitBullet = function(this)
   local x, y = entity.getPosition(this)
   entity.new("MuzzleFlash", x, y + 10)
   entity.emitSound(this, "sounds/laser.ogg", 220, 30)
end

local memberIds = {
   state = 0,
   hp = 1,
   timer = 2
}

local fsm = {
   ["closed"] = function(this, timer)
      if timer > 50000 then
	 entity.setField(this, memberIds.state, "opening")
	 entity.setField(this, memberIds.timer, 0)
      end
   end,
   
   ["opening"] = function(this, timer)
      if timer > 50000 then
	 entity.setField(this, memberIds.timer, 0)
	 local currentFrame = entity.getKeyframe(this)
	 currentFrame = currentFrame + 1
	 if currentFrame <= 4 then
	    entity.setKeyframe(this, currentFrame)
	 else
	    entity.setField(this, memberIds.state, "shoot1")
	 end
      end
   end,
   
   ["shoot1"] = function(this, timer)
      if timer > 200000 then
	 entity.setField(this, memberIds.state, "shoot2")
	 entity.setField(this, memberIds.timer, 0)
	 emitBullet(this)
      end
   end,
   
   ["shoot2"] = function(this, timer)
      if timer > 200000 then
	 entity.setField(this, memberIds.state, "shoot3")
	 entity.setField(this, memberIds.timer, 0)
	 emitBullet(this)
      end
   end,
   
   ["shoot3"] = function(this, timer)
      if timer > 200000 then
	 entity.setField(this, memberIds.state, "rest")
	 entity.setField(this, memberIds.timer, 0)
	 emitBullet(this)
      end
   end,
   
   ["rest"] = function(this, timer)
      if timer > 1200000 then
	 entity.setField(this, memberIds.state, "closing")
	 entity.setField(this, memberIds.timer, 0)
      end
   end,
   
   ["closing"] = function(this, timer)
      if timer > 50000 then
	 entity.setField(this, memberIds.timer, 0)
	 local currentFrame  = entity.getKeyframe(this)
	 currentFrame = currentFrame - 1
	 if currentFrame >= 0 then
	    entity.setKeyframe(this, currentFrame)
	 else
	    entity.setField(this, memberIds.state, "closed")
	 end
      end
   end
}

classes["Turret"] = {
   onCreate = function(this)
      entity.setField(this, memberIds.hp, 6)
      entity.setField(this, memberIds.timer, 0)
      entity.setField(this, memberIds.state, "closed")
      entity.setSprite(this, "turretSprite")
      entity.setShadow(this, "turretShadowSprite")
      entity.setShadowOffset(this, 20)
      local x, y = entity.getPosition(this)
      entity.setZOrder(this, y - 3)
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

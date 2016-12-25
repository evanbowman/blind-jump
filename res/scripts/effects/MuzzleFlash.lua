classes["MuzzleFlash"] = {
   onCreate = function(this)
      entity.setField(this, "timer", 0)
      entity.setSprite(this, "muzzleFlashSprite")
      local x, y = entity.getPosition(this)
      entity.setZOrder(this, y)
   end,

   onUpdate = function(this)
      local dt = system.getDeltaTime()
      local timer = entity.getField(this, "timer")
      timer = timer + dt
      entity.setField(this, "timer", timer)
      local currentFrame = entity.getKeyframe(this)
      if timer > 40000 then
	 entity.setField(this, "timer", 0)
	 if currentFrame == 4 then
	    entity.dispose(this)
	 else
	    currentFrame = currentFrame + 1
	    entity.setKeyframe(this, currentFrame)
	 end
      end
   end
}

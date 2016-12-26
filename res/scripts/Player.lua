local id = {
   state = 0,
   hp = 1
}

local fsm = {
   deactivated = function(this, dt)
      -- TODO...
   end,

   nominal = function(this, dt)
      local x, y = entity.getPosition(this)
      if input.left() then
	 x = x - 1
      end
      if input.right() then
	 x = x + 1
      end
      if input.up() then
	 y = y - 1
      end
      if input.down() then
	 y = y + 1
	 system.quit()
      end
      entity.setPosition(this, x, y)
   end,

   prepdash = function(this, dt)
      -- TODO...
   end,

   dashing = function(this, dt)
      -- TODO...
   end,

   cooldown = function(this, dt)
      -- TODO...
   end,

   dying = function(this, dt)
      -- TODO...
   end,

   dead = function(this, dt)
      -- TODO...
   end
}

classes["Player"] = {
   onCreate = function(this)
      entity.setSprite(this, "playerWalkDownSprite")
      entity.setShadow(this, "playerShadowSprite")
      entity.setShadowOffset(this, 7, 24)
      entity.setKeyframe(this, 5)
      entity.setField(this, id.hp, 4)
      entity.setField(this, id.state, "nominal")
   end,

   onUpdate = function(this)
      local x, y = entity.getPosition(this)
      entity.setZOrder(this, y)
      fsm[entity.getField(this, id.state)](this, system.getDeltaTime())
      if entity.getField(this, id.hp) == 0 then
	 entity.setField(this, id.state, "dying")
      end
   end
}

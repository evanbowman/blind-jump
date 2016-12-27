local id = {
   state = 0,
   hp = 1,
   shadow = 2,
}

local movementFactor = 0.000054

local keyResponse = function(this, key1, key2, key3, key4, sheet)
   if key1 then
      if not key2 and not key3 and not key4 then
	 --[[ TODO: store sprite id in a variable, and only call
	    setSprite when needed. ]]
	 entity.setSprite(this, sheet)
      end
      if key3 or key4 then
	 return 1.70
      else
	 return 2.20
      end
   else
      return 0.0
   end
end

local keyResponseStrafe = function(this, key1, key2, key3)
   if key1 then
      if key2 or key3 then
	 return 1.40
      else
	 return 1.80
      end
   else
      return 0.0
   end
end

local fsm = {
   deactivated = function(this, dt)
      -- TODO...
   end,

   nominal = function(this, dt)
      local lSpeed, rSpeed, uSpeed, dSpeed = 0, 0, 0, 0
      local left = input.left()
      local right = input.right()
      local up = input.up()
      local down = input.down()
      if not input.x() then
	 uSpeed = keyResponse(this, up, down, left, right, "playerUpSprite")
	 dSpeed = keyResponse(this, down, up, left, right, "playerDownSprite")
	 lSpeed = keyResponse(this, left, right, down, up, "playerLeftSprite")
	 rSpeed = keyResponse(this, right, left, down, up, "playerRightSprite")
      else
	 uSpeed = keyResponseStrafe(this, up, left, right)
	 dSpeed = keyResponseStrafe(this, down, left, right)
	 lSpeed = keyResponseStrafe(this, left, up, down)
	 rSpeed = keyResponseStrafe(this, right, up, down)
      end
      local x, y = entity.getPosition(this)
      x = x - (lSpeed - rSpeed) * (dt * movementFactor)
      y = y - (uSpeed - dSpeed) * (dt * movementFactor)
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
      entity.setSprite(this, "playerDownSprite")
      entity.setKeyframe(this, 5)
      entity.setField(this, id.hp, 4)
      entity.setField(this, id.state, "nominal")
      local x, y = entity.getPosition(this)
      entity.setField(this, id.shadow, entity.create("PlayerShadow", x, y))
   end,

   onUpdate = function(this)
      local x, y = entity.getPosition(this)
      entity.setZOrder(this, y)
      fsm[entity.getField(this, id.state)](this, system.getDeltaTime())
      local shadow = entity.getField(this, id.shadow)
      entity.setPosition(shadow, x + 7, y + 24)
      if entity.getField(this, id.hp) == 0 then
	 entity.setField(this, id.state, "dying")
      end
   end
}

classes["PlayerShadow"] = {
   onCreate = function(this)
      entity.setSprite(this, "playerShadowSprite")
   end
}

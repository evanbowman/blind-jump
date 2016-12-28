--[[ NOTE: this script assumes that only one player will be 
   created, if you want to change it to add more players, refactor
   the some of the local variables into fields in the player entities. ]]

local hp = 4

local state = "nominal"

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
      local left = input.keyPressed(input.key.left)
      local right = input.keyPressed(input.key.right)
      local up = input.keyPressed(input.key.up)
      local down = input.keyPressed(input.key.down)
      if not input.keyPressed(input.key.x) then
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

classes["PlayerShadow"] = {
   onCreate = function(this)
      entity.setSprite(this, "playerShadowSprite")
   end
}

local shadow = entity.create("PlayerShadow", 0, 0)

classes["Player"] = {
   onCreate = function(this)
      entity.setSprite(this, "playerDownSprite")
      entity.setKeyframe(this, 5)
      local x, y = entity.getPosition(this)
   end,

   onUpdate = function(this, dt)
      local x, y = entity.getPosition(this)
      entity.setZOrder(this, y)
      fsm[state](this, dt)
      entity.setPosition(shadow, x + 7, y + 24)
      if hp == 0 then
	 state = dying
      end
   end
}

playerStart = { x = 374, y = 238 }
player = entity.create("Player", playerStart.x, playerStart.y)

--[[ NOTE: this script assumes that only one player will be 
   created, if you want to change it to add more players, refactor
   the some of the local variables (i.e. hp, currentSprite, etc.)
   into fields in the player entities. ]]

local id = {
   state = 1,
   animTimer = 2,
   keyframe = 3
}

local hp = 4

local movementFactor = 0.000054

local currentSprite = nil

--[[ The character's walk cycle spends longer on certain frames,
   this table translates the keyframe counter used by the script
   to an absolute keyframe ]]
local verticalAnimDecoder = {
   1, 2, 2, 1, 0, 3, 4, 4, 3, 0, 0
}

--[[ Horizontal animations spend equal time on each frame, but
   I have defined another table for the sake of symmetry ]]
local horizontalAnimDecoder = {
   0, 1, 2, 3, 4, 5
}

local updateAnimation = function(this, dt, maxFrame, decoder)
   local currentFrame = entity.getField(this, id.keyframe)
   local animationTimer = entity.getField(this, id.animTimer)
   animationTimer = animationTimer + dt
   entity.setField(this, id.animTimer, animationTimer)
   if animationTimer > 100000 then
      animationTimer = 0
      currentFrame = currentFrame + 1
      entity.setField(this, id.animTimer, animationTimer)
      entity.setField(this, id.keyframe, currentFrame)
      -- 'currentFrame + 1' because keyframe indices start from zero
      entity.setKeyframe(this, decoder[currentFrame + 1])
   end
   if currentFrame > maxFrame then
      entity.setField(this, id.keyframe, 0)
      entity.setKeyframe(this, decoder[1])
   end
end

local keyResponse = function(this, key1, key2, key3, key4, sprite)
   if key1 then
      if not key2 and not key3 and not key4 then
	 entity.setSprite(this, sprite)
	 currentSprite = sprite
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

local keyReleased = function(this, key1, key2, key3, key4,
		       keyPrev, x, maxFrame, newSpr)
   if not key1 and keyPrev then
      if not key2 and not key3 and not key4 then
	 if not x then
	    entity.setKeyframe(this, maxFrame)
	    entity.setField(this, id.keyframe, 0)
	    --[[ Setting current sprite to nil results in stopping the
	       walk cycle animations, which is the desired outcome when
	       the user isn't pressing any keys ]]
	    currentSprite = nil
	 else
	    -- TODO...
	 end
      end
   end
end

local updatePosition = function(this, dt, lSpeed, rSpeed, uSpeed, dSpeed)
   local x, y = entity.getPosition(this)
   x = x - (lSpeed - rSpeed) * (dt * movementFactor)
   y = y - (uSpeed - dSpeed) * (dt * movementFactor)
   entity.setPosition(this, x, y)
end

-- TODO: FIXME: could deliver key events to player instead
local prevKeys = { left = false,
		   right = false,
		   up = false,
		   down = false }

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
      local x = input.keyPressed(input.key.x)
      if not x then
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
      local animation = {
	 playerUpSprite = function()
	    updateAnimation(this, dt, 9, verticalAnimDecoder)
	 end,

	 playerDownSprite = function()
	    updateAnimation(this, dt, 9, verticalAnimDecoder)
	 end,

	 playerLeftSprite = function()
	    updateAnimation(this, dt, 5, horizontalAnimDecoder)
	 end,

	 playerRightSprite = function()
	    updateAnimation(this, dt, 5, horizontalAnimDecoder)
	 end
      }
      local action = animation[currentSprite]
      if action then action() end
      keyReleased(this, left, right, up, down, prevKeys.left, x, 6, nil)
      keyReleased(this, right, left, up, down, prevKeys.right, x, 6, nil)
      keyReleased(this, up, left, right, down, prevKeys.up, x, 5, nil)
      keyReleased(this, down, left, right, up, prevKeys.down, x, 5, nil)
      updatePosition(this, dt, lSpeed, rSpeed, uSpeed, dSpeed)
      prevKeys.left = left
      prevKeys.right = right
      prevKeys.up = up
      prevKeys.down = down
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
      entity.setField(this, id.keyframe, 0)
      entity.setField(this, id.animTimer, 0)
      entity.setField(this, id.state, "nominal")
      local x, y = entity.getPosition(this)
   end,

   onUpdate = function(this, dt)
      local x, y = entity.getPosition(this)
      entity.setZOrder(this, y)
      local state = entity.getField(this, id.state)
      fsm[state](this, dt)
      entity.setPosition(shadow, x + 7, y + 24)
      if hp == 0 then
	 state = "dying"
	 entity.setField(this, id.state, state)
      end
   end
}

playerStart = { x = 374, y = 238 }
player = entity.create("Player", playerStart.x, playerStart.y)

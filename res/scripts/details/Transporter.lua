require("Player")

local id = {
   shadow = 0,
   glow = 1
}

classes["TransporterShadow"] = {
   onCreate = function(this)
      entity.setSprite(this, "teleporterShadowSprite")
      local x, y = entity.getPosition(this)
      entity.setZOrder(this, y - 33)
   end
}

classes["Transporter"] = {
   onCreate = function(this)
      entity.setSprite(this, "teleporterSprite")
      local x, y = entity.getPosition(this)
      local shadow = entity.create("TransporterShadow", x, y + 4)
      local glow = light.create("teleporterGlowSprite", x + 16, y)
      entity.setZOrder(this, y - 28)
      light.setOrigin(glow, 200, 200)
      entity.setField(this, id.shadow, shadow)
      entity.setField(this, id.glow, glow)
   end,

   onUpdate = function(this)
      local player = player
      local playerX, playerY = entity.getPosition(player)
      local x, y = entity.getPosition(this)
      if calc.distance(x + 1, y - 16, playerX, playerY) < 16 then
	 entity.setPosition(player, x + 1, y - 16)
	 entity.setField(player, 1, "deactivated")
	 entity.setSprite(player, "playerDownSprite")
	 entity.setKeyframe(player, 5)
	 nextLevel()
      end
   end,
   
   onDestroy = function(this)
      local shadow = entity.getField(this, id.shadow)
      entity.destroy(shadow)
      local glow = entity.getField(this, id.glow)
      light.destroy(glow)
   end
}

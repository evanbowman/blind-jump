classes["Lamp"] = {
   onCreate = function(this)
      entity.setSprite(this, "lampSprite")
      local x, y = entity.getPosition(this)
      local glow = light.create("lampGlowSprite", x, y)
      light.setOrigin(glow, 250, 250)
   end
}

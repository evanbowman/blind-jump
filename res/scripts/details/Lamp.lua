classes["Lamp"] = {
   onCreate = function(this)
      entity.setSprite(this, "lampSprite")
      local x, y = entity.getPosition(this)
      light.new("lampGlowSprite", x, y)
   end
}

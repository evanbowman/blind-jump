local id = {
   shadow = 0,
   glow = 1
}

classes["TransporterShadow"] = {
   onCreate = function(this)
      entity.setSprite(this, "teleporterShadowSprite")
   end
}

classes["Transporter"] = {
   onCreate = function(this)
      entity.setSprite(this, "teleporterSprite")
      local x, y = entity.getPosition(this)
      local shadow = entity.create("TransporterShadow", x, y + 4)
      local glow = light.create("teleporterGlowSprite", x + 16, y)
      light.setOrigin(glow, 200, 200)
      entity.setField(this, id.shadow, shadow)
   end,
   
   onDestroy = function(this)
      local shadow = entity.getField(this, id.shadow)
      entity.destroy(shadow)
      local glow = entity.getField(this, id.glow)
      light.destroy(glow)
   end
}

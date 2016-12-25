classes["Pod"] = {
   onCreate = function(this)
      entity.setSprite(this, "podSprite")
      local x, y = entity.getPosition(this)
      entity.setZOrder(this, y + 5)
   end,

   onUpdate = function(this) end
}

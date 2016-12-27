classes["Door"] = {
   onCreate = function(this)
      entity.setSprite(this, "introDoorSprite")
      entity.setKeyframe(this, 3)
      local x, y = entity.getPosition(this)
      entity.setZOrder(this, y + 58)
   end
}

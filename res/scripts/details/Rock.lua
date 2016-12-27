classes["Rock"] = {
   onCreate = function(this)
      entity.setSprite(this, "rockSprite")
      entity.setKeyframe(this, system.random(4, 0))
      local x, y = entity.getPosition(this)
      entity.setZOrder(this, y + 10)
   end
}

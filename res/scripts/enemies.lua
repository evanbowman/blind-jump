classes["Turret"] = {
   OnCreate = function(this)
      instance.setState(this, "closed")
   end,
   
   OnUpdate = function(this)
      local dt = system.getDeltaTime()
      local counter = instance.getCounter(this, 0)
      counter = counter + dt
      local state = instance.getState(this)
      classes["Turret"].FSM[state](this, counter)
   end,

   FSM = {
      ["closed"] = function(this, counter)
	 if counter > 50000 then
	    instance.setState(this, "opening")
	    instance.setCounter(this, 0, 0)
	 else
	    instance.setCounter(this, 0, counter)
	 end
      end,
      
      ["opening"] = function(this, counter)
	 if counter > 50000 then
	    instance.setState(this, "shoot1")
	    instance.setCounter(this, 0, 0)
	 else
	    instance.setCounter(this, 0, counter)
	 end
      end,
      
      ["shoot1"] = function(this, counter)
	 if counter > 200000 then
	    instance.setState(this, "shoot2")
	    instance.setCounter(this, 0, 0)
	    instance.emitSound(this, "sounds/laser.ogg", 220, 30)
	 else
	    instance.setCounter(this, 0, counter)
	 end
      end,
      
      ["shoot2"] = function(this, counter)
	 if counter > 200000 then
	    instance.setState(this, "shoot3")
	    instance.setCounter(this, 0, 0)
	    instance.emitSound(this, "sounds/laser.ogg", 220, 30)
	 else
	    instance.setCounter(this, 0, counter)
	 end
      end,
      
      ["shoot3"] = function(this, counter)
	 if counter > 200000 then
	    instance.setState(this, "rest")
	    instance.setCounter(this, 0, 0)
	    instance.emitSound(this, "sounds/laser.ogg", 220, 30)
	 else
	    instance.setCounter(this, 0, counter)
	 end
      end,
      
      ["rest"] = function(this, counter)
	 if counter > 1200000 then
	    instance.setState(this, "closing")
	    instance.setCounter(this, 0, 0)
	 else
	    instance.setCounter(this, 0, counter)
	 end
      end,
      
      ["closing"] = function(this, counter)
	 if counter > 50000 then
	    instance.setState(this, "closed")
	    instance.setCounter(this, 0, 0)
	 else
	    instance.setCounter(this, 0, counter)
	 end
      end
   }
}

system.registerClass("Turret")
